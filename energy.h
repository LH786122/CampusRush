#ifndef ENERGY_H
#define ENERGY_H

#include "raylib.h"
#include <stdbool.h>

typedef struct EnergySystem {
    float current;
    float max;
    float drainRate;     // energy lost per second while moving
    float lowThreshold;  // fraction (0-1) below which the bar turns red
} EnergySystem;

void Energy_Init(EnergySystem *energy);
void Energy_Update(EnergySystem *energy, float dt, bool isMoving);
void Energy_Restore(EnergySystem *energy, float percent); // percent as 0.5f = +50%
bool Energy_IsEmpty(EnergySystem *energy);
bool Energy_IsLow(EnergySystem *energy);
void Energy_Draw(EnergySystem *energy, int screenWidth);

#endif
