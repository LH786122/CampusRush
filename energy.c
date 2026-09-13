#include "energy.h"

void Energy_Init(EnergySystem *energy)
{
    energy->max = 100.0f;
    energy->current = 100.0f;

    // ~27 seconds of continuous movement drains it fully (100 / 27 ≈ 3.7 per sec)
    energy->drainRate = 3.7f;

    // Below 10% remaining, the bar shows red / "LOW ENERGY!" warning
    energy->lowThreshold = 0.10f;
}

void Energy_Update(EnergySystem *energy, float dt, bool isMoving)
{
    if (isMoving)
    {
        energy->current -= energy->drainRate * dt;

        if (energy->current < 0.0f)
            energy->current = 0.0f;
    }
}

void Energy_Restore(EnergySystem *energy, float percent)
{
    energy->current += energy->max * percent;

    if (energy->current > energy->max)
        energy->current = energy->max;
}

bool Energy_IsEmpty(EnergySystem *energy)
{
    return energy->current <= 0.0f;
}

bool Energy_IsLow(EnergySystem *energy)
{
    return (energy->current / energy->max) <= energy->lowThreshold;
}

void Energy_Draw(EnergySystem *energy, int screenWidth)
{
    int barWidth = 200;
    int barHeight = 22;
    int posX = screenWidth - barWidth - 20;
    int posY = 15;

    float ratio = energy->current / energy->max;
    if (ratio < 0.0f) ratio = 0.0f;

    Color barColor = GREEN;
    if (Energy_IsLow(energy))
        barColor = RED;
    else if (ratio < 0.5f)
        barColor = YELLOW;

    // Background + border
    DrawRectangle(posX - 2, posY - 2, barWidth + 4, barHeight + 4, (Color){ 0, 0, 0, 180 });
    DrawRectangle(posX, posY, barWidth, barHeight, DARKGRAY);

    // Fill
    DrawRectangle(posX, posY, (int)(barWidth * ratio), barHeight, barColor);
    DrawRectangleLines(posX, posY, barWidth, barHeight, WHITE);

    DrawText("ENERGY", posX, posY - 18, 14, WHITE);

    if (Energy_IsLow(energy))
    {
        DrawText("LOW ENERGY!", posX, posY + barHeight + 4, 16, RED);
    }
}
