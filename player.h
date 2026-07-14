#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "world.h"

typedef enum Direction {
    DIR_DOWN = 0,   // row 0 in the sprite sheet (facing viewer)
    DIR_UP,         // row 1 (facing away)
    DIR_LEFT,       // row 2 (side view, used as-is)
    DIR_RIGHT       // row 2 (side view, mirrored horizontally)
} Direction;

typedef struct Player {
    Vector2 position;      // top-left position in world/map space

    Texture2D spriteSheet;
    int frameWidth;        // pixel width of a single frame in the sheet
    int frameHeight;       // pixel height of a single frame in the sheet
    int framesPerRow;      // walk-cycle frame count per direction (8)
    int currentFrame;
    float frameTimer;
    float frameTime;       // seconds each frame is shown

    Direction direction;
    bool isMoving;

    float speed;           // pixels per second
    int width;              // on-screen draw size (scaled down from frame size)
    int height;
} Player;

void Player_Load(Player *player, Vector2 startPos);
void Player_Unload(Player *player);
void Player_Update(Player *player, World *world, float dt);
void Player_Draw(Player *player);
Rectangle Player_GetCollisionRect(Player *player);

#endif // PLAYER_H
