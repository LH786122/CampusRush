#include "raylib.h"
#include "player.h"
#include "coin.h"
#include "timer.h"
#include "hurdle.h"
#include "blocked.h"
#define MAP_WIDTH 1529
#define MAP_HEIGHT 1028
#include <stdio.h>



int main()

{   int mapWidth = 1529;
    int mapHeight = 1028;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(mapWidth,mapHeight,"CampusRush");

    Texture2D map = LoadTexture("assets/map.png");


    Player player;
    Player_Load(&player,(Vector2){400,300});
    

    Camera2D camera = {0};

camera.target = player.position;
camera.offset = (Vector2){
    GetScreenWidth() / 2.0f,
    GetScreenHeight() / 2.0f
};
camera.rotation = 0.0f;
camera.zoom = 2.0f;

    Coin coins[10];
    Hurdle hurdles[5];
    int score =0;

    float timeLeft = 60.0f;
     
    for(int i=0;i<10;i++)
    {
        coins[i]= CreateCoin(map.width, map.height);
    }

    for(int i=0;i<5;i++){
        hurdles[i]= CreateHurdle(map.width, map.height);
    }

    SetTargetFPS(60);


    while(!WindowShouldClose())
    {
        float dt = GetFrameTime();

        Player_Update(&player, dt,mapWidth, mapHeight);

        UpdateTimer(&timeLeft);

        Rectangle playerRect=Player_GetCollisionRect(&player);
           

        camera.target = player.position;

        camera.offset = (Vector2){
            GetScreenWidth() / 2.0f,
            GetScreenHeight() / 2.0f
        };

        for(int i=0;i<10;i++)
        {
            if(CheckCoinCollision(&coins[i],playerRect))
            {
                score++;
            }
        }
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);

                DrawTexture(map,0,0,WHITE);

                for(int i=0;i<10;i++){
                    DrawCoin(coins[i]);
                }

                for(int i=0;i<5;i++){
                    DrawHurdle(hurdles[i]);
                }

                Player_Draw(&player);

            EndMode2D();

            DrawText(TextFormat("Score: %i",score),10,10,30,BLACK); 
                
            DrawTimer(timeLeft);
        EndDrawing();
    }

    Player_Unload(&player);
    UnloadTexture(map);

    CloseWindow();
    printf("%d\n",GetScreenWidth());
    printf("%d",GetScreenHeight());

    return 0;
}