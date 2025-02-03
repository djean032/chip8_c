#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"
#include "include/chip8.h"
#include <stdbool.h>

struct platform
{
  char *title;
  int window_width;
  int window_height;
  int texture_width;
  int texture_height;
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
};

struct platform init_platform (char *title, int window_width,
                               int window_height, int texture_width,
                               int texture_height);

void free_sdl (struct platform *platform);

void update_frame (struct platform *platform, struct chip8 *chip8, int pitch);

bool process_input (struct chip8 *chip8);
#endif // !GRAPHICS_H
