#include "player.h"

void DrawPlayer(Vector2 position){
    DrawRectangleV(position, (Vector2){100,100},BLUE);
}

void UpdatePlayer(Vector2 *position, float speed){
     if(IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_D)){
            position->x += speed*GetFrameTime();
        }
        if(IsKeyDown(KEY_LEFT)|| IsKeyDown(KEY_A)){
            position->x -= speed*GetFrameTime();
        }
        if(IsKeyDown(KEY_DOWN)|| IsKeyDown(KEY_S)){
            position->y += speed*GetFrameTime();
        }
        if(IsKeyDown(KEY_UP)|| IsKeyDown(KEY_W)){
            position->y -= speed*GetFrameTime();
        }
}