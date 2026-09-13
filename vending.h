#ifndef VENDING_H
#define VENDING_H

#include "raylib.h"
#include "energy.h"
#include <stdbool.h>

typedef struct VendingMachine {
    Rectangle zone;         // interaction area near the Rocket
    int price;              // coins required
    float restorePercent;   // fraction of max energy restored (0.5f = +50%)
} VendingMachine;

void Vending_Init(VendingMachine *vm);
bool Vending_PlayerInZone(VendingMachine *vm, Rectangle playerRect);

// Call every frame during gameplay. Handles the [E] key purchase itself.
void Vending_Update(VendingMachine *vm, Rectangle playerRect, int *score, EnergySystem *energy,
                     char *popupMessage, int popupMessageSize, float *popupTimer);

// Draws the "Press [E] to buy a drink" prompt above the player when in zone.
void Vending_DrawPrompt(VendingMachine *vm, Rectangle playerRect, Vector2 playerPos, int playerWidth);

#endif
