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
    DrawRectangle(8, 55, 180, 45, Fade(BROWN, 0.75f));
    DrawRectangleLines(8, 55, 180, 45, BLACK);
    DrawText(TextFormat("Time: %.0f", timeLeft), 20, 65, 30, BLACK);
}