#include "coin.h"


Coin CreateCoin(int mapWidth, int mapHeight){
    Coin coin;
    coin.position= (Vector2){
        GetRandomValue(50, mapWidth - 50),
        GetRandomValue(50, mapHeight -50)
    };
    coin.radius =20;
    coin.collected = false;

    return coin;
    }

void DrawCoin(Coin coin){
    if(!coin.collected){
        DrawCircleV(coin.position, coin.radius, YELLOW);
    }
}

bool CheckCoinCollision(Coin *coin, Rectangle playerRect)
{
    if(!coin->collected && CheckCollisionCircleRec(coin->position, coin->radius, playerRect))
    {
        coin ->collected = true;
        return true;
    }
    return false;
}    