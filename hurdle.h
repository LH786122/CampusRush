#ifndef HURDLE_H
#define HURDLE_H

#include "raylib.h"
#include <stdbool.h>

#define HURDLE_COUNT 26

typedef struct
{
    Vector2 position;
    float width;
    float height;
    bool hurdle_collision;

} Hurdle;

void CreateHurdles(Hurdle hurdles[]);

void DrawHurdle(Hurdle hurdle, Texture2D hurdleTexture);

bool CheckHurdleCollision(Hurdle *hurdle, Rectangle playerRect);

#endif