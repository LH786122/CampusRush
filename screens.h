#ifndef SCREENS_H
#define SCREENS_H

#include "raylib.h"

typedef enum GameScreen { 
    SCREEN_TITLE, 
    SCREEN_MANUAL,
    SCREEN_GAMEPLAY,
    SCREEN_VICTORY,
    SCREEN_GAME_OVER
} GameScreen;

void DrawTextBright(const char *text, int posX, int posY, int fontSize, Color color);
void DrawManualScreen(Texture2D background, int screenWidth, int screenHeight);
void DrawVictoryScreen(Texture2D background, int screenWidth, int screenHeight);
void DrawGameOverScreen(Texture2D background, int screenWidth, int screenHeight);
void CheckGameConditions(Rectangle playerRect, Rectangle goalRect, float timeLeft, GameScreen *currentScreen);

#endif