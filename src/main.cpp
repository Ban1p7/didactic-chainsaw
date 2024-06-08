#include "raylib.h"
#include "player.cpp"


int main(void){
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Didactic Chainsaw");

    int gravity = 5;

    Player player = {0, 0, 64, 64};
    player.sprite = LoadTexture(ASSETS_PATH"klerb.png");

    SetTargetFPS(60);

    while (!WindowShouldClose()){
    // Update stuff

    if (IsMouseButtonPressed(0)){
      gravity *= -1;
    }

    player.y += gravity;

    if (player.y > screenHeight - player.height){
      player.y = screenHeight - player.height;
    }
    if (player.y < 0){
      player.y = 0;
    }

    // Draw everything
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawTexture(player.sprite, player.x, player.y, WHITE);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
