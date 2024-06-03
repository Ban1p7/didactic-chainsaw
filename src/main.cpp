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
  int screenWidth;
  int screenHeight;
  int gravity = 1;
  bool flip = false;
  bool pressed = false;
  SDL_GetWindowSize(GameWindow.SDLWindow, &screenWidth, &screenHeight);
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
    if (event.type == SDL_KEYUP){
//       Debug
//       std::cout << "Key up!" << std::endl;
      pressed = false;
    }
    if (event.type == SDL_KEYDOWN && pressed == false){
//       Debug
//       std::cout << "Key down!" << std::endl;
      flip = true;
      pressed = true;
    }
    if (flip == true){
      gravity *= -1;
      flip = false;
    }
    player.y += gravity;
    if (player.y > screenHeight - player.height){
      player.y = screenHeight - player.height;
    }
    if (player.y < 0){
      player.y = 0;
    }
    updatePlayerRect(&player);
    RenderFrame(&GameWindow, &player);
  }
  SDL_Quit();
  return 0;
}
