# ps2-demo-c - version 0.16.2

A PlayStation 2 homebrew demo written in C17, built on top of **Dodoi-Engine** — a small SDL2-based game engine layer (scenes, camera, input, gfx, sfx, math, loaders) targeting the PS2 via [ps2dev](https://github.com/ps2dev)/PS2SDK.

## Features

- SDL2 + SDL2_image + SDL2_ttf + SDL2_mixer rendering/input/audio pipeline
- Simple scene system (splash screen → title screen) driven by `app_start()`
- Reusable engine modules: camera, context (window/renderer), input, 2D math, colors, sprite/scene rendering, asset loader, sound effects
- Dockerized build using the official `ps2dev/ps2dev` image, so no local toolchain install is required
- Helper scripts (`build.sh` / `build.bat`) and a `docker-compose.yaml` for an interactive dev shell

## Project structure

```
src/
  main.c                 Entry point
  app.c / app.h          Scene loop
  de-ps2/                Dodoi-Engine core
    core/                context, engine, camera, input
    gfx/                  color, scene rendering
    io/                   asset loader
    math/                 2D math helpers
    sfx/                  audio
    util/                 lists, arrays, shared types
  game/                   Game-specific scenes (splash, title)
assets/                   Fonts, images, audio shipped to the ISO
dvdrom/                   Staging area for the bootable ISO (BOOT.ELF, SYSTEM.CNF, DATA/)
bin/                      Build output (.elf / .iso)
build/                    Intermediate object files
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

## License

Licensed under the [Apache License 2.0](LICENSE).
