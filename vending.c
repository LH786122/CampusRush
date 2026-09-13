#include "vending.h"
#include <stdio.h>

void Vending_Init(VendingMachine *vm)
{
    // Bounding area around the "Rocket" building on the map, with some
    // padding so the player doesn't have to stand exactly on top of it.
    // Based on map coordinates roughly (894,275) to (1051,394).
    vm->zone = (Rectangle){ 850, 230, 240, 200 };

    vm->price = 20;
    vm->restorePercent = 0.5f; // +50% energy per purchase
}

bool Vending_PlayerInZone(VendingMachine *vm, Rectangle playerRect)
{
    return CheckCollisionRecs(playerRect, vm->zone);
}

void Vending_Update(VendingMachine *vm, Rectangle playerRect, int *score, EnergySystem *energy,
                     char *popupMessage, int popupMessageSize, float *popupTimer)
{
    if (!Vending_PlayerInZone(vm, playerRect))
        return;

    if (IsKeyPressed(KEY_E))
    {
        if (*score >= vm->price)
        {
            *score -= vm->price;
            Energy_Restore(energy, vm->restorePercent);

            snprintf(popupMessage, popupMessageSize, "Energy boosted! +50%% energy");
            *popupTimer = 2.0f;
        }
        else
        {
            snprintf(popupMessage, popupMessageSize, "Not enough coins! Need %d", vm->price);
            *popupTimer = 2.0f;
        }
    }
}

void Vending_DrawPrompt(VendingMachine *vm, Rectangle playerRect, Vector2 playerPos, int playerWidth)
{
    if (!Vending_PlayerInZone(vm, playerRect))
        return;

    const char *prompt = "Press [E] to buy a drink (5 coins)";
    int textW = MeasureText(prompt, 18);

    float textX = playerPos.x + (playerWidth / 2.0f) - (textW / 2.0f);
    float textY = playerPos.y - 40.0f;

    DrawRectangle((int)textX - 10, (int)textY - 6, textW + 20, 28, (Color){ 0, 0, 0, 200 });
    DrawRectangleLines((int)textX - 10, (int)textY - 6, textW + 20, 28, YELLOW);
    DrawText(prompt, (int)textX, (int)textY, 18, YELLOW);
}
