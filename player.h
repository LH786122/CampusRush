#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef enum Direction {
    DIR_DOWN = 0,
    DIR_UP,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

typedef struct Player {
    Vector2 position;

    Texture2D spriteSheet;
    int frameWidth;
    int frameHeight;
    int framesPerRow;
    int currentFrame;
    float frameTimer;
    float frameTime;

    Direction direction;
    bool isMoving;

    float speed;
    int width;
    int height;
} Player;

void Player_Load(Player *player, Vector2 startPos);
void Player_Unload(Player *player);
void Player_Update(Player *player, float dt);
void Player_Draw(Player *player);
Rectangle Player_GetCollisionRect(Player *player);

#endif