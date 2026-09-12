#include "raylib.h"
#include "player.h"
#include "coin.h"
#include "timer.h"
#include "hurdle.h"
#include <stdio.h>

#define MAP_WIDTH 2150
#define MAP_HEIGHT 1450

typedef enum GameScreen { 
    SCREEN_TITLE, 
    SCREEN_MANUAL,
    SCREEN_GAMEPLAY,
    SCREEN_VICTORY,
    SCREEN_GAME_OVER
} GameScreen;

void InitMenuPage(int screenWidth, int screenHeight);
int UpdateAndDrawMenuPage(int screenWidth, int screenHeight);
void UnloadMenuPage(void);

static void DrawTextBright(const char *text, int posX, int posY, int fontSize, Color color) {
    DrawText(text, posX + 2, posY + 2, fontSize, BLACK);
    DrawText(text, posX, posY, fontSize, color);
}

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "CampusRush");

    InitMenuPage(screenWidth, screenHeight);

    GameScreen currentScreen = SCREEN_TITLE;
    int score = 0;
    float timeLeft = 60.0f;

    // --- POPUP SYSTEM VARIABLES ---
    char popupMessage[128] = "";
    float popupTimer = 0.0f;
    bool lowEnergyTriggered = false;
    Texture2D grass = LoadTexture("assets/FINALMAPPP.png");
    Texture2D manualBg = LoadTexture("forcover (1).png"); 
    Texture2D winBg = LoadTexture("forcover (1).png"); 
    Texture2D loseBg = LoadTexture("forcover (1).png");

    Player player;
    // Initial Load Spawn near bottom-right (below CDS)
    Player_Load(&player, (Vector2){ 1750.0f, 1300.0f });
    
    Camera2D camera = {0};
    camera.target = player.position;
    camera.offset = (Vector2){400, 225};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Coin coins[10];
    Hurdle hurdles[5];
     
    for (int i = 0; i < 10; i++) {
        coins[i] = CreateCoin(MAP_WIDTH, MAP_HEIGHT);
    }

    for (int i = 0; i < 5; i++) {
        hurdles[i] = CreateHurdle(MAP_WIDTH, MAP_HEIGHT);
    }

    // Goal location over Academic Building 2
    Rectangle academicBuilding2 = { 50, 0, 520, 260 };

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

            Player_Update(&player, dt);
            UpdateTimer(&timeLeft);

            // Update popup timer duration
            if (popupTimer > 0.0f)
            {
                popupTimer -= dt;
            }
            float popupTriggerTime = 30.0f; // Set your target time here (e.g., 15 seconds remaining)
            Rectangle playerRect = Player_GetCollisionRect(&player);
            camera.target = player.position;

            // Check coin collision & trigger popup
            for (int i = 0; i < 10; i++)
            {
                if (CheckCoinCollision(&coins[i], playerRect))
                {
                    score++;
                    snprintf(popupMessage, sizeof(popupMessage), "Would you like to have a ENERGY BOOSTER?\nIf YES,Go to ROCKET!");
                    popupTimer = 4.0f; // Show for 2 seconds
                }
            }

            if (CheckCollisionRecs(playerRect, academicBuilding2))
            {
                currentScreen = SCREEN_VICTORY;
            }

            if (timeLeft <= 0.0f)
            {
                currentScreen = SCREEN_GAME_OVER;
            }
        }
        else if (currentScreen == SCREEN_VICTORY || currentScreen == SCREEN_GAME_OVER)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                score = 0;
                timeLeft = 60.0f;
                popupTimer = 0.0f;
                player.position = (Vector2){ 1750.0f, 1300.0f };
                for (int i = 0; i < 10; i++) coins[i] = CreateCoin(MAP_WIDTH, MAP_HEIGHT);
                currentScreen = SCREEN_GAMEPLAY;
            }
            else if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_BACKSPACE))
            {
                score = 0;
                timeLeft = 60.0f;
                popupTimer = 0.0f;
                player.position = (Vector2){ 1750.0f, 1300.0f };
                for (int i = 0; i < 10; i++) coins[i] = CreateCoin(MAP_WIDTH, MAP_HEIGHT);
                currentScreen = SCREEN_TITLE;
            }
        }

        // --- GRAPHICS DRAW STEP ---
        BeginDrawing();
            ClearBackground(RAYWHITE);

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
                if (manualBg.id > 0)
                {
                    DrawTexturePro(
                        manualBg,
                        (Rectangle){ 0, 0, (float)manualBg.width, (float)manualBg.height },
                        (Rectangle){ 0, 0, (float)currentW, (float)currentH },
                        (Vector2){ 0, 0 }, 0.0f, WHITE
                    );
                }
                else ClearBackground(DARKGRAY);

                DrawRectangle(0, 0, currentW, currentH, (Color){ 0, 0, 0, 200 });

                DrawTextBright("CAMPUS RUSH - MANUAL", currentW/2 - MeasureText("CAMPUS RUSH - MANUAL", 25)/2, 50, 25, YELLOW);
                DrawTextBright("1. Collect coins to earn points.", 100, 160, 20, WHITE);
                DrawTextBright("2. Avoid hurdles to prevent slowdowns.", 100, 200, 20, WHITE);
                DrawTextBright("3. Get energy booster drinks to run faster.", 100, 240, 20, WHITE);
                DrawTextBright("4. Reach Academic Building-2 before the timer runs out!", 100, 280, 20, WHITE);
                DrawTextBright("Press [BACKSPACE] to return to Menu", 100, 340, 20, YELLOW);
            }
            else if (currentScreen == SCREEN_GAMEPLAY)
            {
                BeginMode2D(camera);

                    if (grass.id > 0) {
                        DrawTexturePro(
                            grass,
                            (Rectangle){ 0, 0, (float)grass.width, (float)grass.height },
                            (Rectangle){ 0, 0, (float)MAP_WIDTH, (float)MAP_HEIGHT },
                            (Vector2){ 0, 0 }, 0.0f, WHITE
                        );
                    } else {
                        ClearBackground(DARKGREEN);
                    }

                    // Translucent goal box over Academic Building 2
                    DrawRectangleRec(academicBuilding2, (Color){ 255, 215, 0, 80 }); 
                    DrawRectangleLinesEx(academicBuilding2, 3, GREEN);               
                    
                    for (int i = 0; i < 10; i++) {
                        DrawCoin(coins[i]);
                    }

                    for (int i = 0; i < 5; i++) {
                        DrawHurdle(hurdles[i]);
                    }

                    Player_Draw(&player);

                    // --- DRAW FLOATING POPUP TEXT OVER PLAYER ---
                    if (popupTimer > 0.0f)
                    {
                        int textW = MeasureText(popupMessage, 18);
                        float textX = player.position.x + (player.width / 2.0f) - (textW / 2.0f);
                        float textY = player.position.y - 30.0f;

                        DrawRectangle((int)textX - 6, (int)textY - 4, textW + 12, 24, (Color){ 0, 0, 0, 200 });
                        DrawText(popupMessage, (int)textX, (int)textY, 18, YELLOW);
                    }

                EndMode2D();

                DrawTextBright(TextFormat("Score: %i", score), 15, 15, 30, YELLOW); 
                DrawTimer(timeLeft);
            }
            else if (currentScreen == SCREEN_VICTORY)
            {
                if (winBg.id > 0)
                {
                    DrawTexturePro(
                        winBg,
                        (Rectangle){ 0, 0, (float)winBg.width, (float)winBg.height },
                        (Rectangle){ 0, 0, (float)currentW, (float)currentH },
                        (Vector2){ 0, 0 }, 0.0f, WHITE
                    );
                }
                else ClearBackground(DARKGREEN);

                DrawRectangle(0, 0, currentW, currentH, (Color){ 0, 0, 0, 180 });

                const char *winTitle = "SAVED FOR TODAY!";
                const char *winPrompt = "Press [ENTER] to Play Again | [ESC] for Menu";

                DrawTextBright(winTitle, currentW/2 - MeasureText(winTitle, 30)/2, currentH/2 - 80, 30, YELLOW);
                DrawTextBright(winPrompt, currentW/2 - MeasureText(winPrompt, 18)/2, currentH/2 + 70, 18, LIGHTGRAY);
            }
            else if (currentScreen == SCREEN_GAME_OVER)
            {
                if (loseBg.id > 0)
                {
                    DrawTexturePro(
                        loseBg,
                        (Rectangle){ 0, 0, (float)loseBg.width, (float)loseBg.height },
                        (Rectangle){ 0, 0, (float)currentW, (float)currentH },
                        (Vector2){ 0, 0 }, 0.0f, WHITE
                    );
                }
                else ClearBackground(MAROON);

                DrawRectangle(0, 0, currentW, currentH, (Color){ 0, 0, 0, 190 });

                const char *loseTitle = "IN IUT, ATTENDANCE MATTERS!";
                const char *losePrompt = "Press [ENTER] to Try Again | [ESC] for Menu";

                DrawTextBright(loseTitle, currentW/2 - MeasureText(loseTitle, 30)/2, currentH/2 - 80, 30, YELLOW);
                DrawTextBright(losePrompt, currentW/2 - MeasureText(losePrompt, 18)/2, currentH/2 + 70, 18, LIGHTGRAY);
            }

        EndDrawing();
    }

    Player_Unload(&player);
    UnloadTexture(grass);
    UnloadTexture(manualBg);
    UnloadTexture(winBg);
    UnloadTexture(loseBg);
    
    UnloadMenuPage(); 
    CloseWindow();

    return 0;
}