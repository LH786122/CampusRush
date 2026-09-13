#ifndef COIN_H
#define COIN_H

#include "raylib.h"
#include <stdbool.h>

#define COIN_COUNT 40

typedef struct
{
    Vector2 position;
    float radius;
    bool collected;
} Coin;

void CreateCoins(Coin coins[]);

void DrawCoin(Coin coin, Texture2D coinTexture);

bool CheckCoinCollision(Coin *coin, Rectangle playerRect);

#endif