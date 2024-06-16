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
    double score = 0;
    double stillTime = 0;
    double maxStillTime = 3;
    int stillBarThickness = 8;
    const int ENEMY_SPEED = 5;
    int speedMultiplier = 1;

    Texture2D playerSprite = LoadTexture(ASSETS_PATH"klerb.png");;
    Texture2D floorSprite = LoadTexture(ASSETS_PATH"floor.png");;
    Texture2D enemySprite = LoadTexture(ASSETS_PATH"enemy.png");;

    Object player = {16, screenHeight - 64, 64, 64, 0, 0, &playerSprite};
//     player.sprite = &playerSprite;

    Object floor = {0, screenHeight - 64, 800, 64, 0, 0, &floorSprite};
//     floor.sprite = &floorSprite;

    Object annoyingEnemy = {-16, 0, 16, 16, 0, 0, &enemySprite};

    Object enemies[8];
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> randomX(0, 800);

//     SetTargetFPS(60);

    bool playing = false;

    while (!WindowShouldClose()){

      if (playing == true){

        double deltaTime = GetFrameTime() * 60;
        score += GetFrameTime() * 1;

        // Update stuff

        bool onFloor = doObjectsCollide(&player, &floor);
        bool jumpPressed = false;

        if (onFloor){
          if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){
            player.yv = -15;
            jumpPressed = true;
          }
        } else {
          jumpPressed = true;
        }

        player.xv = 0;

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)){
          player.xv -= playerSpeed;
        }
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)){
          player.xv += playerSpeed;
        }
        if (true){//jumpPressed == false || player.xv == 0 || player.x == 0 || player.x == screenWidth - player.width){
          stillTime += GetFrameTime();
          if (stillTime >= maxStillTime){
//             playing = false;
            if ((annoyingEnemy.xv == 0 && annoyingEnemy.yv == 0) || ((annoyingEnemy.xv < 0 && annoyingEnemy.x < 0) || annoyingEnemy.xv > 0 && annoyingEnemy.x > screenWidth)){
//             std::cout << "Began attack" << std::endl;
            stillTime -= maxStillTime;
              if (player.x + player.width/2 < screenWidth / 2){
                annoyingEnemy.x = -16;
                annoyingEnemy.y = screenHeight - floor.height - annoyingEnemy.height;
                annoyingEnemy.xv = ENEMY_SPEED * speedMultiplier;
                annoyingEnemy.yv = 0;
              } else {
                annoyingEnemy.x = screenWidth + 16;
                annoyingEnemy.y = screenHeight - floor.height - annoyingEnemy.height;
                annoyingEnemy.xv = -ENEMY_SPEED * speedMultiplier;
                annoyingEnemy.yv = 0;
              }
            }
          }
        } else {
          stillTime = 0;
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
          if (doObjectsCollide(&player, &enemies[i])){
            playing = false;
          }
          enemies[i].y += enemies[i].yv * deltaTime;
          if (enemies[i].y > screenHeight){
            if (i == 0){
              enemies[i].x = player.x;
            } else {
              enemies[i].x = randomX(rng);
            }
            enemies[i].y -= screenHeight * 2;
          }
        }
        annoyingEnemy.x += annoyingEnemy.xv * deltaTime;
        annoyingEnemy.y += annoyingEnemy.yv * deltaTime;
        if (doObjectsCollide(&player, &annoyingEnemy)){
          playing = false;
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
            enemies[i].yv = ENEMY_SPEED * speedMultiplier;
          }
          annoyingEnemy.x = -20;
          annoyingEnemy.xv = annoyingEnemy.yv = 0;
          playing = true;
          score = 0;
          stillTime = 0;
        }
        if (IsKeyDown(KEY_Q)){
          speedMultiplier = 1;
        }
        if (IsKeyDown(KEY_W)){
          speedMultiplier = 2;
        }
        if (IsKeyDown(KEY_E)){
          speedMultiplier = 3;
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
              DrawTexture(*annoyingEnemy.sprite, annoyingEnemy.x, annoyingEnemy.y, WHITE);
              DrawTexture(*floor.sprite, floor.x, floor.y, WHITE);
              DrawTexture(*player.sprite, player.x, player.y, WHITE);
              DrawRectangle(player.x, player.y - (stillBarThickness + 4), player.width * stillTime/maxStillTime, stillBarThickness, GRAY);
              DrawText(TextFormat("%i", (int)score), 8, 0, 32, BLACK);

            } else {
        // Menu stuff
              ClearBackground(RAYWHITE);
              DrawText("Didactic Chainsaw", 64, 0, 64, BLACK);
              DrawText("Press <space> to start!", 32, 64, 32, BLACK);
              DrawText(TextFormat("Score: %f", score), 32, 128, 32, BLACK);
              DrawText("Select difficulty with the Q, W or E keys", 32, screenHeight - 32, 32, BLACK);
            }

            if (debugStuff){
              DrawRectangle(screenWidth, 0, 128, screenHeight, BLACK);
              DrawFPS(screenWidth, 0);
              DrawText(TextFormat("%f", score), screenWidth, 16, 20, GREEN);
              DrawText(TextFormat("%f", stillTime), screenWidth, 36, 20, GREEN);
            }
        EndDrawing();

    }
    UnloadTexture(playerSprite);
    UnloadTexture(floorSprite);
    UnloadTexture(enemySprite);
    CloseWindow();

    return 0;
}
