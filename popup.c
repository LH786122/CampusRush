#include "popup.h"
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

void UpdatePopupSystem(PopupSystem *popup, float dt, float timeLeft) {
    if (popup->timer > 0.0f) {
        popup->timer -= dt;
    } else {
        popup->state = 0;
    }

    // Low Energy Prompt Check
    float popupTriggerTime = 30.0f;
    if (timeLeft <= popupTriggerTime && !popup->lowEnergyTriggered) {
        popup->lowEnergyTriggered = true;
        popup->state = 1;
        snprintf(popup->message, sizeof(popup->message), "Do you want an energy booster? [Y/N]");
        popup->timer = 5.0f;
    }

    // Input Handling for Question
    if (popup->state == 1 && popup->timer > 0.0f) {
        if (IsKeyPressed(KEY_Y)) {
            popup->state = 2;
            snprintf(popup->message, sizeof(popup->message), "If YES, go to ROCKET!");
            popup->timer = 4.0f;
        } else if (IsKeyPressed(KEY_N)) {
            popup->timer = 0.0f;
            popup->state = 0;
        }
    }
}

void DrawPopupInWorld(const PopupSystem *popup, Vector2 playerPos, float playerWidth) {
    if (popup->timer > 0.0f) {
        int textW = MeasureText(popup->message, 18);
        float textX = playerPos.x + (playerWidth / 2.0f) - (textW / 2.0f);
        float textY = playerPos.y - 70.0f;

        DrawRectangle((int)textX - 10, (int)textY - 6, textW + 20, 32, (Color){ 240, 240, 240, 240 });
        DrawRectangleLines((int)textX - 10, (int)textY - 6, textW + 20, 32, BLACK);
        DrawText(popup->message, (int)textX, (int)textY, 18, BLACK);
    }
}