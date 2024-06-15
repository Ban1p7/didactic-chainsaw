#include <iostream>
#include <random>

#include "raylib.h"

#include "object.hpp"

#define debugStuff false

int main(void){

    const int screenWidth = 800;
    const int screenHeight = 600;

    if (debugStuff){
      InitWindow(screenWidth + 128, screenHeight, "Didactic Chainsaw - Debug");
    } else {
      InitWindow(screenWidth, screenHeight, "Didactic Chainsaw");
    }

    double gravity = 0.5;
    double playerSpeed = 10;

    Texture2D playerSprite = LoadTexture(ASSETS_PATH"klerb.png");;
    Texture2D floorSprite = LoadTexture(ASSETS_PATH"floor.png");;
    Texture2D enemySprite = LoadTexture(ASSETS_PATH"enemy.png");;

    Object player = {16, screenHeight - 64, 64, 64, 0, 0};
    player.sprite = &playerSprite;

    Object floor = {0, screenHeight - 64, 800, 64, 0, 0};
    floor.sprite = &floorSprite;

    Object enemies[8];
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> randomX(0, 800);

//     SetTargetFPS(60);

    bool playing = false;

    while (!WindowShouldClose()){

      if (playing == true){

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

        for (int i = 0; i < sizeof(enemies)/sizeof(enemies[0]); i++){
          enemies[i].y += enemies[i].yv * deltaTime;
          if (doObjectsCollide(&player, &enemies[i])){
            playing = false;
          }
          if (enemies[i].y > screenHeight){
            enemies[i].y -= screenHeight * 2;
            enemies[i].x = randomX(rng);
          }
        }

  //       std::cout << doObjectsCollide(&player, &floor) << std::endl;

        if (doObjectsCollide(&player, &floor)){
          handleCollision(&player, &floor);
        }
      } else {
        if (IsKeyDown(KEY_SPACE)){
          player.x = 16;
          player.y = screenHeight - 64;

          for (int i = 0; i < sizeof(enemies)/sizeof(enemies[0]); i++){
            enemies[i].width = 16;
            enemies[i].height = 16;
            enemies[i].x = randomX(rng);
            enemies[i].y = -i * (screenHeight / 4);
            enemies[i].sprite = &enemySprite;
            enemies[i].xv = 0;
            enemies[i].yv = 5;
            playing = true;
          }
        }
      }

      // Draw everything
        BeginDrawing();

          // Game stuff
            if (playing == true){
              ClearBackground(RAYWHITE);
              for (int i = 0; i < sizeof(enemies)/sizeof(enemies[0]); i++){
                DrawTexture(*enemies[i].sprite, enemies[i].x, enemies[i].y, WHITE);
              }
              DrawTexture(*floor.sprite, floor.x, floor.y, WHITE);
              DrawTexture(*player.sprite, player.x, player.y, WHITE);

            } else {
        // Menu stuff
              ClearBackground(RAYWHITE);
              DrawText("Didactic Chainsaw", 64, 0, 64, BLACK);
              DrawText("Press <space> to start!", 32, 64, 32, BLACK);
            }

            if (debugStuff){
              DrawRectangle(screenWidth, 0, 128, screenHeight, BLACK);
              DrawFPS(screenWidth, 0);
            }
        EndDrawing();

    }
    UnloadTexture(playerSprite);
    UnloadTexture(floorSprite);
    UnloadTexture(enemySprite);
    CloseWindow();

    return 0;
}
