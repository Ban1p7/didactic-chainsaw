#ifndef playerdotcpp
#define playerdotcpp

#include "raylib.h"

struct Player {
  int x, y, width, height;
//   SDL_Rect posRect;
  Texture2D sprite;
};

#endif
