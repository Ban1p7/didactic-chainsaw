#ifndef windowdoth
#define windowdoth

#include <SDL.h>
#include "player.cpp"

struct Window {
  // Pointers to the SDL window and SDL surface, not defined here
  // Defined above where SDLWindow and SDLWindowSurface are given values but aren't initialised
  SDL_Window* SDLWindow{nullptr};
  SDL_Surface* SDLWindowSurface{nullptr};
};

void init_window(Window* GameWindow){
  SDL_Init(SDL_INIT_VIDEO);
  GameWindow->SDLWindow = SDL_CreateWindow(
      "Didactic Chainsaw", // Window title
      100,                 // Window x position
      100,                 // Window y position
      800,                 // Window width
      600,                 // Window height
      0                    // No idea, but DON'T CHANGE -- IT BREAKS EVERYTHING
    );
    GameWindow->SDLWindowSurface = SDL_GetWindowSurface(GameWindow->SDLWindow);
    SDL_FillRect(
      GameWindow->SDLWindowSurface,                                        // Window surface
      nullptr,                                                             // Only fill a section of the surface
      SDL_MapRGB(GameWindow->SDLWindowSurface->format, 100, 100, 255)      // The format to fill the screen, then the rgb values
    );
}

// Render function
void RenderFrame(Window* GameWindow, Player* player){
  SDL_FillRect(
      GameWindow->SDLWindowSurface,                                        // Window surface
      nullptr,                                                             // Only fill a section of the surface
      SDL_MapRGB(GameWindow->SDLWindowSurface->format, 100, 100, 255)      // The format to fill the screen, then the rgb values
    );
  SDL_FillRect(
    GameWindow->SDLWindowSurface,
    &player->posRect,
    SDL_MapRGBA(
      GameWindow->SDLWindowSurface->format,
      player->color.r,
      player->color.g,
      player->color.b,
      player->color.a
    )
  );
  SDL_UpdateWindowSurface(GameWindow->SDLWindow);
}

#endif

