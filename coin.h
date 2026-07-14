#ifndef COIN_H
#define COIN_H

#include "raylib.h"

typedef struct {
    Vector2 position;
    float radius;
    bool collected;
}Coin;

Coin CreateCoin(int mapWidth, int mapHeight);

void DrawCoin(Coin coin);

bool CheckCoinCollision(Coin *coin, Rectangle playerRect);


#endif 
