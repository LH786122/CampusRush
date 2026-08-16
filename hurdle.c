#include "hurdle.h"


Hurdle CreateHurdle(int mapwidth, int mapheight){
    Hurdle hurdle;
    hurdle.position= (Vector2){
        GetRandomValue(50, mapwidth -50),
        GetRandomValue(50, mapheight - 50)
    };
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