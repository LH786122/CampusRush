#include "screens.h"

void DrawTextBright(const char *text, int posX, int posY, int fontSize, Color color) {
    DrawText(text, posX + 2, posY + 2, fontSize, BLACK);
    DrawText(text, posX, posY, fontSize, color);
}

void DrawManualScreen(Texture2D background, int screenWidth, int screenHeight) {
    if (background.id > 0) {
        DrawTexturePro(
            background,
            (Rectangle){ 0, 0, (float)background.width, (float)background.height },
            (Rectangle){ 0, 0, (float)screenWidth, (float)screenHeight },
            (Vector2){ 0, 0 }, 0.0f, WHITE
        );
    } else {
        ClearBackground(DARKGRAY);
    }

    DrawRectangle(0, 0, screenWidth, screenHeight, (Color){ 0, 0, 0, 200 });

    DrawTextBright("CAMPUS RUSH - MANUAL", screenWidth/2 - MeasureText("CAMPUS RUSH - MANUAL", 25)/2, 50, 25, YELLOW);
    DrawTextBright("1. Collect coins to earn points.", 100, 160, 20, WHITE);
    DrawTextBright("2. Navigate around campus obstacles.", 100, 200, 20, WHITE);
    DrawTextBright("3. Get energy booster drinks to run faster.", 100, 240, 20, WHITE);
    DrawTextBright("4. Reach Academic Building-2 before the timer runs out!", 100, 280, 20, WHITE);
    DrawTextBright("Press [BACKSPACE] to return to Menu", 100, 340, 20, YELLOW);
}

void DrawVictoryScreen(Texture2D background, int screenWidth, int screenHeight) {
    if (background.id > 0) {
        DrawTexturePro(
            background,
            (Rectangle){ 0, 0, (float)background.width, (float)background.height },
            (Rectangle){ 0, 0, (float)screenWidth, (float)screenHeight },
            (Vector2){ 0, 0 }, 0.0f, WHITE
        );
    } else {
        ClearBackground(DARKGREEN);
    }

    DrawRectangle(0, 0, screenWidth, screenHeight, (Color){ 0, 0, 0, 180 });

    const char *winTitle = "SAVED FOR TODAY!";
    const char *winPrompt = "Press [ENTER] to Play Again | [BACKSPACE] for Menu";

    DrawTextBright(winTitle, screenWidth/2 - MeasureText(winTitle, 30)/2, screenHeight/2 - 80, 30, YELLOW);
    DrawTextBright(winPrompt, screenWidth/2 - MeasureText(winPrompt, 18)/2, screenHeight/2 + 70, 18, LIGHTGRAY);
}

void DrawGameOverScreen(Texture2D background, int screenWidth, int screenHeight) {
    if (background.id > 0) {
        DrawTexturePro(
            background,
            (Rectangle){ 0, 0, (float)background.width, (float)background.height },
            (Rectangle){ 0, 0, (float)screenWidth, (float)screenHeight },
            (Vector2){ 0, 0 }, 0.0f, WHITE
        );
    } else {
        ClearBackground(MAROON);
    }

    DrawRectangle(0, 0, screenWidth, screenHeight, (Color){ 0, 0, 0, 190 });

    const char *loseTitle = "IN IUT, ATTENDANCE MATTERS!";
    const char *losePrompt = "Press [ENTER] to Try Again | [BACKSPACE] for Menu";

    DrawTextBright(loseTitle, screenWidth/2 - MeasureText(loseTitle, 30)/2, screenHeight/2 - 80, 30, YELLOW);
    DrawTextBright(losePrompt, screenWidth/2 - MeasureText(losePrompt, 18)/2, screenHeight/2 + 70, 18, LIGHTGRAY);
}

void CheckGameConditions(Rectangle playerRect, Rectangle goalRect, float timeLeft, GameScreen *currentScreen) {
    if (CheckCollisionRecs(playerRect, goalRect)) {
        *currentScreen = SCREEN_VICTORY;
    } else if (timeLeft <= 0.0f) {
        *currentScreen = SCREEN_GAME_OVER;
    }
}