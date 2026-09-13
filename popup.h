#ifndef POPUP_H
#define POPUP_H

#include "raylib.h"
#include <stdbool.h>

typedef struct PopupSystem {
    char message[128];
    float timer;
    bool lowEnergyTriggered;
    int state; // 0: Standard, 1: Question [Y/N], 2: Direction
} PopupSystem;

void InitPopupSystem(PopupSystem *popup);
void ResetPopupSystem(PopupSystem *popup);
void UpdatePopupSystem(PopupSystem *popup, float dt, float timeLeft);
void TriggerPopup(PopupSystem *popup, const char *msg, float duration);
void DrawPopupInWorld(const PopupSystem *popup, Vector2 playerPos, float playerWidth);

#endif