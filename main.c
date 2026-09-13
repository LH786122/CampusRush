#include "raylib.h"
#include "player.h"
#include "coin.h"
#include "timer.h"
#include "hurdle.h"
#include "blocked.h"
#include "popup.h"
#include "screens.h"
#include <stdio.h>

#define MAP_WIDTH 1529
#define MAP_HEIGHT 1028

void InitMenuPage(int screenWidth, int screenHeight);
int UpdateAndDrawMenuPage(int screenWidth, int screenHeight);
void UnloadMenuPage(void);

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "CampusRush");

    Texture2D map = LoadTexture("assets/map.png");
    Texture2D coinTexture = LoadTexture("assets/coin-removebg-preview.png");
    SetTextureFilter(coinTexture, TEXTURE_FILTER_POINT);
    Texture2D hurdleTexture = LoadTexture("assets/stone-removebg-preview.png");
    SetTextureFilter(hurdleTexture, TEXTURE_FILTER_POINT);
    
    Texture2D manualBg = LoadTexture("forcover (1).png"); 
    Texture2D winBg = LoadTexture("forcover (1).png"); 
    Texture2D loseBg = LoadTexture("forcover (1).png");

    // Initialize Popup System & Menus
    PopupSystem popup;
    InitPopupSystem(&popup);
    InitMenuPage(screenWidth, screenHeight);

    Player player;
    Player_Load(&player, (Vector2){834.0f, 955.0f});

    Camera2D camera = {0};
    camera.target = player.position;
    camera.offset = (Vector2){400, 225};
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;

    Coin coins[COIN_COUNT];
    Hurdle hurdles[HURDLE_COUNT];
    int score = 0;
    GameScreen currentScreen = SCREEN_TITLE;
    float timeLeft = 60.0f;
    
    CreateCoins(coins);
    CreateHurdles(hurdles);

    // Goal location over Academic Building 2
    Rectangle academicBuilding2 = { 300, 143, 240,140 };

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        int currentW = GetScreenWidth();
        int currentH = GetScreenHeight();
        camera.offset = (Vector2){ currentW / 2.0f, currentH / 2.0f };

        // --- UPDATE STEP ---
        if (currentScreen == SCREEN_MANUAL)
        {
            if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_BACKSPACE))
            {
                currentScreen = SCREEN_TITLE;
            }
        }
        else if (currentScreen == SCREEN_GAMEPLAY)
        {
            float dt = GetFrameTime();

            Player_Update(&player, dt, MAP_WIDTH, MAP_HEIGHT);
            UpdateTimer(&timeLeft);
            UpdatePopupSystem(&popup, dt, timeLeft); // Updated popup system

            Rectangle playerRect = Player_GetCollisionRect(&player);
            camera.target = player.position;

            for (int i = 0; i < COIN_COUNT; i++)
            {
                if (CheckCoinCollision(&coins[i], playerRect))
                {
                    score++;
                }
            }

            // Check Game State Conditions (Victory/Defeat)
            CheckGameConditions(playerRect, academicBuilding2, timeLeft, &currentScreen);
        }
        else if (currentScreen == SCREEN_VICTORY || currentScreen == SCREEN_GAME_OVER)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                score = 0;
                timeLeft = 60.0f;
                ResetPopupSystem(&popup);
                player.position = (Vector2){ 834.0f, 955.0f };
                CreateCoins(coins);
                currentScreen = SCREEN_GAMEPLAY;
            }
            else if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_BACKSPACE))
            {
                score = 0;
                timeLeft = 60.0f;
                ResetPopupSystem(&popup);
                player.position = (Vector2){ 834.0f, 955.0f };
                CreateCoins(coins);
                currentScreen = SCREEN_TITLE;
            }
        }

        // --- DRAW STEP ---
        BeginDrawing();
            ClearBackground(BEIGE);

            if (currentScreen == SCREEN_TITLE)
            {
                int menuAction = UpdateAndDrawMenuPage(currentW, currentH);
                if (menuAction == 1)
                {
                    currentScreen = SCREEN_GAMEPLAY;
                }
                else if (menuAction == 2)
                {
                    currentScreen = SCREEN_MANUAL;
                }
            }
            else if (currentScreen == SCREEN_MANUAL)
            {
                DrawManualScreen(manualBg, currentW, currentH);
            }
            else if (currentScreen == SCREEN_GAMEPLAY)
            {
                // World Rendering
                BeginMode2D(camera);

                    DrawTexture(map, 0, 0, WHITE);

                    for (int i = 0; i < COIN_COUNT; i++) {
                        DrawCoin(coins[i], coinTexture);
                    }

                    for (int i = 0; i < HURDLE_COUNT; i++) {
                        DrawHurdle(hurdles[i], hurdleTexture);
                    }

                    Player_Draw(&player);
                    DrawPopupInWorld(&popup, player.position, player.width); // Rendered popup

                EndMode2D();

                // UI Overlay
                DrawText(TextFormat("Score: %i", score), 10, 10, 30, BLACK); 
                DrawTimer(timeLeft);
            }
            else if (currentScreen == SCREEN_VICTORY)
            {
                DrawVictoryScreen(winBg, currentW, currentH);
            }
            else if (currentScreen == SCREEN_GAME_OVER)
            {
                DrawGameOverScreen(loseBg, currentW, currentH);
            }

        EndDrawing();
    }

    // Unload assets
    Player_Unload(&player);
    UnloadTexture(map);
    UnloadTexture(coinTexture);
    UnloadTexture(hurdleTexture);
    UnloadTexture(manualBg);
    UnloadTexture(winBg);
    UnloadTexture(loseBg);

    UnloadMenuPage();
    CloseWindow();

    return 0;
}