#ifndef objectdotcpp
#define objectdotcpp

#include "raylib.h"

struct Object {
  double x, y;
  int width, height;
  double xv, yv;
  Texture2D sprite;
};

bool doObjectsCollide(Object *thing1, Object *thing2){
  if(
    thing2->y > thing1->y + thing1->height ||
    thing2->x > thing1->x + thing1->width ||
    thing1->y > thing2->y + thing2->height ||
    thing1->x > thing2->x + thing2->width
  ){
    return false;
  }
  return true;
}

void handleCollision(Object *mover, Object *still){
  double toLeft = mover->x + mover->width - still->x;
//   mover->x -= toLeft;
  double toRight = still->x + still->width - mover->x;
//   mover->x += toRight;
  double toTop = mover->y + mover->height - still->y;
//   mover->y -= toTop;
  double toBottom = still->y + still->height - mover->y;
//   mover->x += toBottom;

  if (
    toLeft <= toRight &&
    toLeft <= toTop &&
    toLeft <= toBottom
  ){
    mover->x -= toLeft;
    mover->xv = 0;
    return;
  }
  if (
    toRight <= toTop &&
    toRight <= toBottom
  ){
    mover->x += toRight;
    mover->xv = 0;
    return;
  }
  if (
    toTop <= toBottom
  ){
    mover->y -= toTop;
    mover->yv = 0;
    return;
  }
  mover->y += toBottom;
  mover->yv = 0;
  return;

}

#endif
