#include "screens.h"
#include "energy.h"

void DrawManualScreen(Texture2D background, int screenWidth, int screenHeight) {
    DrawTexturePro(
        background,
        (Rectangle){ 0, 0, (float)background.width, (float)background.height },
        (Rectangle){ 0, 0, (float)screenWidth, (float)screenHeight },
        (Vector2){ 0, 0 }, 0.0f, WHITE
    );

    int titleWidth = MeasureText("CAMPUS RUSH - MANUAL", 25);
    DrawText("CAMPUS RUSH - MANUAL", (screenWidth - titleWidth) / 2, 50, 25, YELLOW);

    DrawText("1. Reach Academic Building-2 before your energy & timer runs out!", 50, 160, 20, WHITE);
    DrawText("2. Each Step and Hurdles cause energy loss.", 50, 200, 20, WHITE);
    DrawText("3. Collect more & more coins to buy energy booster drinks.", 50, 240, 20, WHITE);
    DrawText("Press [BACKSPACE] to return to Menu", 50, 280, 20, YELLOW);
}

void DrawVictoryScreen(Texture2D background, int screenWidth, int screenHeight) {
    // Draws your background image instead of solid GREEN
    DrawTexturePro(
        background,
        (Rectangle){ 0, 0, (float)background.width, (float)background.height },
        (Rectangle){ 0, 0, (float)screenWidth, (float)screenHeight },
        (Vector2){ 0, 0 }, 0.0f, WHITE
    );

    const char *winTitle = "CONGRATS!! SAVED FOR TODAY!";
    const char *winPrompt = "Press [ENTER] to Play Again | [BACKSPACE] for Menu";

    int titleWidth = MeasureText(winTitle, 30);
    int promptWidth = MeasureText(winPrompt, 18);

    DrawText(winTitle, (screenWidth - titleWidth) / 2, screenHeight / 2 - 40, 30, YELLOW);
    DrawText(winPrompt, (screenWidth - promptWidth) / 2, screenHeight / 2 + 40, 18, LIGHTGRAY);
}

void DrawGameOverScreen(Texture2D background, int screenWidth, int screenHeight) {
    // Draws your background image instead of solid RED
    DrawTexturePro(
        background,
        (Rectangle){ 0, 0, (float)background.width, (float)background.height },
        (Rectangle){ 0, 0, (float)screenWidth, (float)screenHeight },
        (Vector2){ 0, 0 }, 0.0f, WHITE
    );

    const char *loseTitle = "SORRY! IN IUT, ATTENDANCE MATTERS!";
    const char *losePrompt = "Press [ENTER] to Try Again | [BACKSPACE] for Menu";

    int titleWidth = MeasureText(loseTitle, 30);
    int promptWidth = MeasureText(losePrompt, 18);

    DrawText(loseTitle, (screenWidth - titleWidth) / 2, screenHeight / 2 - 40, 30, YELLOW);
    DrawText(losePrompt, (screenWidth - promptWidth) / 2, screenHeight / 2 + 40, 18, LIGHTGRAY);
}

void CheckGameConditions(Rectangle playerRect, Rectangle goalRect, float timeLeft, EnergySystem *energy, GameScreen *currentScreen) {
    if (CheckCollisionRecs(playerRect, goalRect)) {
        *currentScreen = SCREEN_VICTORY;
    } 
    else if (timeLeft <= 0.0f || Energy_IsEmpty(energy)) {
        *currentScreen = SCREEN_GAME_OVER;
    }
}