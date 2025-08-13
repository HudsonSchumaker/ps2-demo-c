/**
* @file gfx.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "pch.h"
#include "de_model.h"

void gfx_init(void);
SDL_Window* gfx_get_window(void);
SDL_Renderer* gfx_get_renderer(void);

SDL_Texture* gfx_load_texture(const char* file_path);
SDL_Rect gfx_get_texture_rect(SDL_Texture* texture);

void gfx_close(void);
