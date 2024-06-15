#include "raylib.h"
#include "object.hpp"
#include <iostream>

int main(void){
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Didactic Chainsaw");

    double gravity = 0.5;
    double playerSpeed = 10;

    Object player = {0, 0, 64, 64, 0, 0};
    player.sprite = LoadTexture(ASSETS_PATH"klerb.png");

    Object floor = {0, screenHeight - 64, 800, 64, 0, 0};
    floor.sprite = LoadTexture(ASSETS_PATH"floor.png");

//     Object enemies[4];

//     for (int i = 0; i < sizeof(enemies)/sizeof(enemies[0]); i++){
//       enemies[i].x = 0;
//       enemies[i].y = -i * (screenHeight / 4);
//       enemies[i].width = 16;
//       enemies[i].height = 16;
//       enemies[i].sprite = LoadTexture(ASSETS_PATH"enemy.png");
//       enemies[i].xv = 0;
//       enemies[i].yv = 5;
//     }

//     SetTargetFPS(60);

    while (!WindowShouldClose()){

      double deltaTime = GetFrameTime() * 60;

      // Update stuff

      bool onFloor = doObjectsCollide(&player, &floor);

      if (IsKeyDown(KEY_W) && onFloor){
        player.yv = -15;
      }

      player.xv = 0;

      if (IsKeyDown(KEY_A)){
        player.xv -= playerSpeed;
      }
      if (IsKeyDown(KEY_D)){
        player.xv += playerSpeed;
      }

      player.yv += gravity * deltaTime * !onFloor;

      player.x += player.xv * deltaTime;
      player.y += player.yv * deltaTime;

      if (player.y > screenHeight - player.height){
        player.y = screenHeight - player.height;
        player.yv = 0;
      }
      if (player.y < 0){
        player.y = 0;
      }
      if (player.x > screenWidth - player.width){
        player.x = screenWidth - player.width;
      }
      if (player.x < 0){
        player.x = 0;
      }

//       for (int i = 0; i < sizeof(enemies)/sizeof(enemies[0]); i++){
//         enemies[i].y += enemies[i].yv * deltaTime;
//       }

//       std::cout << doObjectsCollide(&player, &floor) << std::endl;

      if (doObjectsCollide(&player, &floor)){
        handleCollision(&player, &floor);
      }

      // Draw everything
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawTexture(floor.sprite, floor.x, floor.y, WHITE);
//             for (int i = 0; i < sizeof(enemies)/sizeof(enemies[0]); i++){
//               DrawTexture(enemies[i].sprite, enemies[i].x, enemies[i].y, WHITE);
//             }
            DrawTexture(player.sprite, player.x, player.y, WHITE);
            DrawFPS(0, 0);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
