#ifndef HURDLE_H
#define HURDLE_H

#include "raylib.h"

typedef struct {
    Vector2 position;
    float width;
    float height;
    bool hurdle_collision;
}Hurdle;

Hurdle CreateHurdle(int mapwidth, int mapheight);

void DrawHurdle(Hurdle hurdle);

bool CheckHurdleCollision(Hurdle *hurdle, Rectangle playerRect);

#endif
