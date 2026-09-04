# ps2-demo-c - version 0.1718.0

A PlayStation 2 homebrew demo written in C17, built on top of **Dodoi-Engine** — a small SDL2-based game engine layer (scenes, camera, input, gfx, sfx, math, loaders) targeting the PS2 via [ps2dev](https://github.com/ps2dev)/PS2SDK.

## Features

- SDL2 + SDL2_image + SDL2_ttf + SDL2_mixer rendering/input/audio pipeline
- Scene state machine (`scene_t`) driving splash → title, with per-scene `load/input/update/render/run/unload` callbacks
- Cached asset loading for textures, fonts, sounds and music (avoids re-decoding the same file from the ISO twice)
- 2D primitive drawing (lines, circles, boxes, triangles), colors, and bitmap text rendering
- Fixed-point-friendly 2D math: `vec2_t`/`vec3_t`/`vec4_t`, lookup-table sin/cos/tan, fast `rsqrtf`/`fsqrtf`
- AABB/circle collision helpers, a generic dynamic `list_t`, and array utility macros
- Dockerized build using the official `ps2dev/ps2dev` image, so no local toolchain install is required
- Helper scripts (`build.sh` / `build.bat`) and a `docker-compose.yaml` for an interactive dev shell

## Project structure

```
src/
  main.c                 Entry point, calls app_start()
  app.c / app.h          Scene state machine (SCENE_SPLASH -> SCENE_TITLE -> ... -> SCENE_EXIT)
  de-ps2/                Dodoi-Engine core
    de.h                 Shared includes, screen size, math constants, typedefs (u8, f32, ...)
    core/
      engine.c/h         engine_init/quit, delta time
      context.c/h        SDL window/renderer lifecycle (ctx_init/quit, ctx_get_window/renderer)
      camera.c/h         camera_t (viewport + background color)
      input.c/h          Game controller init (input_get_controller)
      types.h            Shared structs: vec2/3/4_t, texture_t, font_t, label_t, sound_t, music_t...
      collision.h        AABB / point-in-rect / circle intersection helpers
    gfx/
      gfx.c/h            Texture loading + cache, texture rendering (+rotated)
      draw.c/h           Line/circle/box/triangle primitives
      color.c/h          color_t helpers and named colors
      write.c/h          Cached bitmap text (labels) via SDL_ttf
      scene.c/h          scene_t state machine, begin/end render, running flag
    io/
      loader.c/h         Raw asset loading (texture/sound/music/font) from the ISO
    math/
      math2d.c/h         vec2 ops, sin/cos/tan LUTs, fast sqrt
    sfx/
      sfx.c/h            Music/sound playback + cache
    util/
      list.c/h           Generic dynamic array (list_t)
      arrays.h           Array macros (ARRAY_LENGTH, ARRAY_FOR_EACH, ...) and compare_* functions
  game/                  Game-specific scenes (splash_screen, title_screen)
assets/                  Fonts, images, audio shipped to the ISO (copied into dvdrom/DATA on `iso` build)
dvdrom/                  Staging area for the bootable ISO (BOOT.ELF, SYSTEM.CNF, DATA/)
bin/                     Build output (.elf / .iso)
build/                   Intermediate object files
```

## Requirements

- [Docker](https://www.docker.com/) (all compilation happens inside the `ps2dev/ps2dev` container — no local PS2SDK install needed)
- [PCSX2](https://pcsx2.net/) or real PS2 hardware to run the resulting `.elf`/`.iso`

## Building

A helper script wraps the Docker workflow. Use `build.sh` on macOS/Linux or `build.bat` on Windows.

```powershell
# Build the ps2dev Docker image (only needed once, or after Dockerfile changes)
.\build.bat build

# Compile the game -> bin/ps2game.elf
.\build.bat compile

# Compile and package a bootable ISO -> bin/ps2game.iso
.\build.bat iso

# Open an interactive shell inside the build container
.\build.bat shell

# Remove build artifacts
.\build.bat clean
```

Equivalent commands are available via `./build.sh <command>` on macOS/Linux, or directly with `make`, `make iso`, and `make clean` from inside the container (see `docker-compose.yaml` for an interactive shell alternative).

## Running

Load `bin/ps2game.elf` or `bin/ps2game.iso` in [PCSX2](https://pcsx2.net/), or burn/transfer the ISO to run on real PS2 hardware.

## Using the engine

Everything below lives under `src/de-ps2/` and is pulled in transitively through `de-ps2/de.h`. Asset paths always point at files staged on the ISO, e.g. `"cdrom0:/DATA/LOGO.PNG;1"` (built from `assets/*` by the `iso` Makefile target).

### 1. Adding a scene

A scene is just a `scene_t*` with function pointers wired up in an `_init()` function. `app_start()` (in [app.c](src/app.c)) drives the loop: it calls `load()` once, then `run()`, which is expected to internally loop `input()` → `update()` → `render()` until `scene_set_running(false)` is called, and finally returns the id of the next scene.

```c
// game/my_screen.h
#ifndef MY_SCREEN_H
#define MY_SCREEN_H

#include "../app.h"
#include "../de-ps2/gfx/scene.h"

void my_screen_init(void);
scene_t* my_screen_get_scene(void);

#endif
```

```c
// game/my_screen.c
#include "my_screen.h"
#include "../de-ps2/gfx/gfx.h"
#include "../de-ps2/core/engine.h"

static scene_t* my_screen = NULL;
static texture_t sprite;
static path_t sprite_path[] = "cdrom0:/DATA/SPRITE.PNG;1";

static void my_screen_load(void)   { sprite = gfx_load_texture_cached(sprite_path); scene_set_running(true); }
static void my_screen_input(void)  { /* poll SDL_Event / SDL_GameController here */ }
static void my_screen_update(void) { engine_calculate_delta_time(); }
static void my_screen_render(void) {
    scene_begin_render();
    gfx_render_texture(sprite);
    scene_end_render();
}
static void my_screen_unload(void) { scene_set_running(false); }

static byte my_screen_run(void) {
    while (scene_is_running()) {
        my_screen_input();
        my_screen_update();
        my_screen_render();
    }
    return SCENE_EXIT; // or the next scene_id_e
}

void my_screen_init(void) {
    my_screen = scene_init();
    my_screen->load   = my_screen_load;
    my_screen->input  = my_screen_input;
    my_screen->update = my_screen_update;
    my_screen->render = my_screen_render;
    my_screen->run    = my_screen_run;
    my_screen->unload = my_screen_unload;
}

scene_t* my_screen_get_scene(void) { return my_screen; }
```

Register the new scene in [app.h](src/app.h) (add an id to `scene_id_e`) and wire the case in [app.c](src/app.c)'s `switch (next_scene)`.

### 2. Textures and rendering

```c
#include "de-ps2/gfx/gfx.h"

texture_t logo = gfx_load_texture_cached("cdrom0:/DATA/LOGO.PNG;1"); // cached: loaded from disk once
logo.position.x = (SCREEN_WIDTH  - logo.size.w) / 2;
logo.position.y = (SCREEN_HEIGHT - logo.size.h) / 2;

scene_begin_render();
gfx_render_texture(logo);                 // plain blit at logo.position
gfx_render_texture_rotated(logo, 45.0);    // rotated around its center
scene_end_render();

gfx_clear_texture_cache(); // frees every cached texture, call on shutdown/scene change
```

### 3. Text (bitmap labels)

```c
#include "de-ps2/gfx/write.h"

write_cache_font("cdrom0:/DATA/ALAGARD.TTF;1", 18); // pre-warm the font cache (optional)

label_t text = write_create_text_cached(
    "cdrom0:/DATA/ALAGARD.TTF;1", "PRESS START", 18, color_RGB(255, 0, 0)
);
text.position.x = (SCREEN_WIDTH - text.size.w) / 2;
text.position.y = SCREEN_HEIGHT - 120;

write_render_text(text); // call every frame between scene_begin_render/scene_end_render

write_destroy_text(text); // free the label's SDL_Texture when the scene unloads
```

### 4. Primitive drawing

```c
#include "de-ps2/gfx/draw.h"
#include "de-ps2/gfx/color.h"

draw_line(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color_white());
draw_circle(320, 224, 40, color_yellow());
draw_fill_box((SDL_Rect){10, 10, 100, 40}, color_RGBA(0, 0, 0, 180));
draw_triangle(160, 100, 200, 180, 120, 180, color_red());
```

### 5. Input

```c
#include "de-ps2/core/input.h"

void my_screen_input(void) {
    SDL_GameController* pad = input_get_controller();
    if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_START)) {
        scene_set_running(false); // ends run()'s loop, falls through to unload()
    }

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            scene_set_running(false);
        }
    }
}
```

### 6. Sound effects and music

```c
#include "de-ps2/sfx/sfx.h"

sfx_cache_sound("cdrom0:/DATA/OK.WAV;1");
sfx_cache_music("cdrom0:/DATA/PUZZLE.OGG;1");

sfx_play_sound_cached("cdrom0:/DATA/OK.WAV;1");
sfx_play_music_cached("cdrom0:/DATA/PUZZLE.OGG;1");

sfx_stop_all(); // call from unload()
```

### 7. Math and collision

```c
#include "de-ps2/math/math2d.h"
#include "de-ps2/core/collision.h"

vec2_t pos = vec2_create(10.0f, 20.0f);
vec2_t vel = vec2_mul(vec2_right(), 2.5f);
pos = vec2_add(pos, vel);

int idx = degrees_to_index(90.0f);
float s = de_sinf(idx); // LUT-based sin, faster than sinf() on the EE

if (rect_intersects(px, py, pw, ph, qx, qy, qw, qh)) {
    // AABB overlap
}
```

### 8. Dynamic lists and array utilities

```c
#include "de-ps2/util/list.h"
#include "de-ps2/util/arrays.h"

list_t enemies;
list_init(&enemies, sizeof(enemy_t));
list_push_back(&enemies, &enemy);
enemy_t* first = list_get(&enemies, 0);
list_remove_at(&enemies, 0);
list_quit(&enemies);

int values[] = {5, 3, 9, 1};
ARRAY_FOR_EACH(int, v, values) { printf("%d\n", *v); }
qsort(values, ARRAY_LENGTH(values), sizeof(int), compare_int);
```

## License

Licensed under the [Apache License 2.0](LICENSE).
