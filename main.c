#include "raylib.h"
#include "player.h"

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(800,450,"CampusRush");

    Texture2D mapTexture = LoadTexture("assets/map.png");

    Vector2 position ={400,300};

    Camera2D camera = {0};
    camera.target = position;
    camera.offset = (Vector2){400,225};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    float speed = 300.0f;

    while(!WindowShouldClose())
    {
        UpdatePlayer(&position, speed);

        camera.target = position;

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);

                DrawTexture(mapTexture,0,0,WHITE);

                DrawPlayer(position);

            EndMode2D();

        EndDrawing();
    }

    UnloadTexture(mapTexture);

    CloseWindow();

    return 0;
}