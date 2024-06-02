#include <SDL.h>
#include <iostream>

// Window Class
#include "window.hpp"

// Player Class
#include "player.cpp"

// Run this to start the game
int main(){
  // Define the window
  Window GameWindow;
  init_window(&GameWindow);
  SDL_Event event;
  SDL_Color yellow = {255, 204, 0, 255};
  SDL_Rect nullRect = {0, 0, 0, 0};
  Player player = {0, 0, 32, 32, nullRect, yellow};
  player.posRect.w = player.posRect.h = 32;
  bool running = true;
  int start = event.quit.timestamp;
  while (running) {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT){
      running = false;
    }
    RenderFrame(&GameWindow, &player);
  }
  SDL_Quit();
  return 0;
}
