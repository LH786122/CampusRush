#include "timer.h"
#include "raylib.h"

void UpdateTimer(float *timeLeft)
{
    if (*timeLeft > 0)
    {
        *timeLeft -= GetFrameTime();

        if (*timeLeft < 0)
        {
            *timeLeft = 0;
        }
    }
}

void DrawTimer(float timeLeft)
{
    DrawText(TextFormat("Time: %.0f", timeLeft),10,50,30,RED);
             
}