#include "popup.h"
#include "energy.h"
#include <stdio.h>
#include <string.h>

void InitPopupSystem(PopupSystem *popup) {
    ResetPopupSystem(popup);
}

void ResetPopupSystem(PopupSystem *popup) {
    popup->message[0] = '\0';
    popup->timer = 0.0f;
    popup->lowEnergyTriggered = false;
    popup->state = 0;
}

void TriggerPopup(PopupSystem *popup, const char *msg, float duration) {
    popup->state = 0;
    snprintf(popup->message, sizeof(popup->message), "%s", msg);
    popup->timer = duration;
}

void UpdatePopupSystem(PopupSystem *popup, float dt, const EnergySystem *energy) {
    // 1. Timer Countdown
    if (popup->timer > 0.0f) {
        popup->timer -= dt;
    } else {
        // Clear message string when timer expires to prevent leftover rendering
        popup->message[0] = '\0';
        popup->state = 0;
    }

    float energyRatio = energy->current / energy->max;

    // 2. Trigger low energy prompt ONLY when no other popup is actively playing
    if (energyRatio <= 0.10f && !popup->lowEnergyTriggered && popup->timer <= 0.0f) {
        popup->lowEnergyTriggered = true;
        popup->state = 1;
        TriggerPopup(popup, "Energy low! Buy a drink? [Y/N]", 5.0f);
    }

    // Reset lock when energy is restored above 10%
    if (energyRatio > 0.10f) {
        popup->lowEnergyTriggered = false;
    }

    // 3. Handle Key Inputs during low energy prompt
    if (popup->state == 1 && popup->timer > 0.0f) {
        if (IsKeyPressed(KEY_Y)) {
            popup->state = 2;
            TriggerPopup(popup, "Go to ROCKET to buy a drink!", 4.0f);
        } else if (IsKeyPressed(KEY_N)) {
            popup->timer = 0.0f;
            popup->message[0] = '\0';
            popup->state = 0;
        }
    }
}

void DrawPopupInWorld(const PopupSystem *popup, Vector2 playerPos, float playerWidth) {
    // Only draw if there is a valid message and positive timer
    if (popup->timer > 0.0f && popup->message[0] != '\0') {
        int textW = MeasureText(popup->message, 18);
        float textX = playerPos.x + (playerWidth / 2.0f) - (textW / 2.0f);
        float textY = playerPos.y - 70.0f;

        DrawRectangle((int)textX - 10, (int)textY - 6, textW + 20, 32, (Color){ 240, 240, 240, 240 });
        DrawRectangleLines((int)textX - 10, (int)textY - 6, textW + 20, 32, BLACK);
        DrawText(popup->message, (int)textX, (int)textY, 18, BLACK);
    }
}