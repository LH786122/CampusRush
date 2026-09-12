#include "coin.h"
#include "blocked.h"


Coin CreateCoin(int mapWidth, int mapHeight){
    Coin coin;
    Vector2 pos;

    do{
        pos.x=(float)GetRandomValue(50,mapWidth-50);
        pos.y=(float)GetRandomValue(50,mapHeight-50);
    }while(isBlocked(pos));
    
    coin.position = pos;
    coin.radius = 10;
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