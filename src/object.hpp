#ifndef objectdothpp
#define objectdothpp

#include "raylib.h"

struct Object {
  double x, y;
  int width, height;
  double xv, yv;
  Texture2D *sprite;
};

bool doObjectsCollide(Object *thing1, Object *thing2);
void handleCollision(Object *mover, Object *still);

#endif
