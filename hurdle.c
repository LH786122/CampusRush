#include "hurdle.h"
#include "blocked.h"


Hurdle CreateHurdle(int mapWidth, int mapHeight){
     Hurdle hurdle;
     Vector2 pos;
     do{
        pos.x=(float)GetRandomValue(50,mapWidth-50);
        pos.y=(float)GetRandomValue(50,mapHeight-50);
    }while(isBlocked(pos));

    
    hurdle.width = 20;
    hurdle.height = 20;

    hurdle.hurdle_collision = false;

    return hurdle;
}

void DrawHurdle(Hurdle hurdle){
    if(!hurdle.hurdle_collision){
        DrawRectangleV(hurdle.position, (Vector2){hurdle.width, hurdle.height}, RED);
    }
}

bool CheckHurdleCollision(Hurdle *hurdle, Rectangle playerRect){
    if(!hurdle->hurdle_collision && CheckCollisionRecs((Rectangle){hurdle->position.x, hurdle->position.y, hurdle->width, hurdle->height}, playerRect))
    {
        hurdle ->hurdle_collision = true;
        return true;
    }
    return false;
}