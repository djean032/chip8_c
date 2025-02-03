#include "include/graphics.h"
#include "SDL3/SDL_render.h"

struct platform
init_platform (char *title, int window_width, int window_height,
               int texture_width, int texture_height)
{
  struct platform *platform = malloc (sizeof (struct platform));
  platform->title = title;
  platform->window_width = window_width;
  platform->window_height = window_height;
  platform->texture_width = texture_width;
  platform->texture_height = texture_height;
  platform->window
      = SDL_CreateWindow (title, platform->window_width,
                          platform->window_height, SDL_WINDOW_RESIZABLE);
  platform->renderer = SDL_CreateRenderer (platform->window, NULL);
  platform->texture
      = SDL_CreateTexture (platform->renderer, SDL_PIXELFORMAT_XRGB8888,
                           SDL_TEXTUREACCESS_STREAMING,
                           platform->texture_width, platform->texture_height);
  SDL_SetTextureScaleMode (platform->texture, SDL_SCALEMODE_NEAREST);
  return *platform;
}

void
free_sdl (struct platform *platform)
{
  SDL_DestroyTexture (platform->texture);
  SDL_DestroyRenderer (platform->renderer);
  SDL_DestroyWindow (platform->window);
  SDL_Quit ();
  free (platform);
}

void
update_frame (struct platform *platform, struct chip8 *chip8, int pitch)
{
  SDL_UpdateTexture (platform->texture, nullptr, chip8->video, pitch);
  SDL_RenderClear (platform->renderer);
  SDL_RenderTexture (platform->renderer, platform->texture, nullptr, nullptr);
  SDL_RenderPresent (platform->renderer);
}

bool
process_input (struct chip8 *chip8)
{

  bool quit = false;
  SDL_Event event;

  while (SDL_PollEvent (&event))
    {
      switch (event.type)
        {
        case SDL_EVENT_QUIT:
          {
            quit = true;
          }
          break;
        case SDL_EVENT_KEY_DOWN:
          {
            switch (event.key.key)
              {
              case SDLK_ESCAPE:
                {
                  quit = true;
                }
                break;
              case SDLK_X:
                {
                  chip8->keypad[0] = 1;
                }
                break;
              case SDLK_1:
                {
                  chip8->keypad[1] = 1;
                }
                break;
              case SDLK_2:
                {
                  chip8->keypad[2] = 1;
                }
                break;
              case SDLK_3:
                {
                  chip8->keypad[3] = 1;
                }
                break;
              case SDLK_Q:
                {
                  chip8->keypad[4] = 1;
                }
                break;
              case SDLK_W:
                {
                  chip8->keypad[5] = 1;
                }
                break;
              case SDLK_E:
                {
                  chip8->keypad[6] = 1;
                }
                break;
              case SDLK_A:
                {
                  chip8->keypad[7] = 1;
                }
                break;
              case SDLK_S:
                {
                  chip8->keypad[8] = 1;
                }
                break;
              case SDLK_D:
                {
                  chip8->keypad[9] = 1;
                }
                break;
              case SDLK_Z:
                {
                  chip8->keypad[0xA] = 1;
                }
                break;
              case SDLK_C:
                {
                  chip8->keypad[0xB] = 1;
                }
                break;
              case SDLK_4:
                {
                  chip8->keypad[0xC] = 1;
                }
                break;
              case SDLK_R:
                {
                  chip8->keypad[0xD] = 1;
                }
                break;
              case SDLK_F:
                {
                  chip8->keypad[0xE] = 1;
                }
                break;
              case SDLK_V:
                {
                  chip8->keypad[0xF] = 1;
                }
                break;
              }
          }
          break;
        case SDL_EVENT_KEY_UP:
          {
            switch (event.key.key)
              {
              case SDLK_ESCAPE:
                {
                  quit = true;
                }
                break;
              case SDLK_X:
                {
                  chip8->keypad[0] = 0;
                }
                break;
              case SDLK_1:
                {
                  chip8->keypad[1] = 0;
                }
                break;
              case SDLK_2:
                {
                  chip8->keypad[2] = 0;
                }
                break;
              case SDLK_3:
                {
                  chip8->keypad[3] = 0;
                }
                break;
              case SDLK_Q:
                {
                  chip8->keypad[4] = 0;
                }
                break;
              case SDLK_W:
                {
                  chip8->keypad[5] = 0;
                }
                break;
              case SDLK_E:
                {
                  chip8->keypad[6] = 0;
                }
                break;
              case SDLK_A:
                {
                  chip8->keypad[7] = 0;
                }
                break;
              case SDLK_S:
                {
                  chip8->keypad[8] = 0;
                }
                break;
              case SDLK_D:
                {
                  chip8->keypad[9] = 0;
                }
                break;
              case SDLK_Z:
                {
                  chip8->keypad[0xA] = 0;
                }
                break;
              case SDLK_C:
                {
                  chip8->keypad[0xB] = 0;
                }
                break;
              case SDLK_4:
                {
                  chip8->keypad[0xC] = 0;
                }
                break;
              case SDLK_R:
                {
                  chip8->keypad[0xD] = 0;
                }
                break;
              case SDLK_F:
                {
                  chip8->keypad[0xE] = 0;
                }
                break;
              case SDLK_V:
                {
                  chip8->keypad[0xF] = 0;
                }
                break;
              }
          }
          break;
        }
    }
  return quit;
}
