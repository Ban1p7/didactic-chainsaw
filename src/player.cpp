#ifndef playerdotcpp
#define playerdotcpp

struct Player {
  int x, y, width, height;
  SDL_Rect posRect;
  SDL_Color color;
};

void updatePlayerRect(Player* player){
  player->posRect.x = player->x;
  player->posRect.y = player->y;
  player->posRect.w = player->width;
  player->posRect.h = player->height;
  return;
}

#endif
