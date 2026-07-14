#include "raylib.h"
#include "player.h"
#include "coin.h"
#include "timer.h"


int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(800,450,"CampusRush");

    Texture2D grass = LoadTexture("assets/grass_raylib_compatible.png");

    Player player;
    Player_Load(&player,(Vector2){400,300});
    

    Camera2D camera = {0};
    camera.target = player.position;
    camera.offset = (Vector2){400,225};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Coin coins[10];
    int score =0;
    float timeLeft = 60.0f; // 60 seconds timer
    for(int i=0;i<10;i++)
    {
        coins[i]= CreateCoin(3000,3000);
    }

    SetTargetFPS(60);


    while(!WindowShouldClose())
    {
        float dt = GetFrameTime();

        Player_Update(&player, dt);
        UpdateTimer(&timeLeft);
        Rectangle playerRect=Player_GetCollisionRect(&player);
           

        camera.target = player.position;

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

               for(int y=0; y<GetScreenHeight(); y+=grass.height){
                    for(int x=0; x<GetScreenWidth(); x+=grass.width){
                        DrawTexture(grass, x, y, WHITE);
                    }
               }
                for(int i=0;i<10;i++){
                    DrawCoin(coins[i]);
                }

                Player_Draw(&player);

            EndMode2D();

            DrawText(TextFormat("Score: %i",score),10,10,30,BLACK); 
                
        
        DrawTimer(timeLeft);
        EndDrawing();
    }

    Player_Unload(&player);
    UnloadTexture(grass);

    CloseWindow();

    return 0;
}