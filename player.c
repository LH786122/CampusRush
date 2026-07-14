#include "player.h"
#include <math.h>

#define FRAME_TIME 0.14f

void Player_Load(Player *player, Vector2 startPos)
{
    player->spriteSheet = LoadTexture("assets/player_spritesheet.png");

    player->framesPerRow = 8;
    player->frameWidth = player->spriteSheet.width / 8;
    player->frameHeight = player->spriteSheet.height / 3;

    if (player->frameWidth <= 0) player->frameWidth = 64;
    if (player->frameHeight <= 0) player->frameHeight = 64;

    player->currentFrame = 0;
    player->frameTimer = 0.0f;
    player->frameTime = FRAME_TIME;

    player->direction = DIR_DOWN;
    player->isMoving = false;

    player->position = startPos;
    player->speed = 190.0f;

    player->height = 100;
    player->width = (int)(player->height *
        ((float)player->frameWidth / player->frameHeight));
}

void Player_Unload(Player *player)
{
    UnloadTexture(player->spriteSheet);
}

Rectangle Player_GetCollisionRect(Player *player)
{
    float footW = player->width * 0.5f;
    float footH = player->height * 0.20f;

    return (Rectangle){
        player->position.x + (player->width - footW) / 2.0f,
        player->position.y + player->height - footH,
        footW,
        footH
    };
}

void Player_Update(Player *player, float dt)
{
    Vector2 move = {0, 0};

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) move.x += 1;
    if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)) move.x -= 1;
    if (IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) move.y += 1;
    if (IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W)) move.y -= 1;

    float len = sqrtf(move.x * move.x + move.y * move.y);
    player->isMoving = (len > 0.0f);

    if (len > 0.0f)
    {
        move.x /= len;
        move.y /= len;
    }

    // Direction
    if (player->isMoving)
    {
        if (fabsf(move.x) >= fabsf(move.y))
            player->direction = (move.x < 0) ? DIR_LEFT : DIR_RIGHT;
        else
            player->direction = (move.y < 0) ? DIR_UP : DIR_DOWN;
    }

    // Animation
    if (player->isMoving)
    {
        player->frameTimer += dt;

        if (player->frameTimer >= player->frameTime)
        {
            player->frameTimer -= player->frameTime;
            player->currentFrame =
                (player->currentFrame + 1) % player->framesPerRow;
        }
    }
    else
    {
        player->currentFrame = 0;
        player->frameTimer = 0.0f;
    }

    // Movement
    player->position.x += move.x * player->speed * dt;
    player->position.y += move.y * player->speed * dt;

    // Keep inside 3000x3000 map
    if (player->position.x < 0)
        player->position.x = 0;

    if (player->position.y < 0)
        player->position.y = 0;

    if (player->position.x + player->width > 3000)
        player->position.x = 3000 - player->width;

    if (player->position.y + player->height > 3000)
        player->position.y = 3000 - player->height;
}

void Player_Draw(Player *player)
{
    int row;
    bool flip = false;

    switch (player->direction)
    {
        case DIR_DOWN:
            row = 0;
            break;

        case DIR_UP:
            row = 1;
            break;

        case DIR_LEFT:
            row = 2;
            flip = false;
            break;

        case DIR_RIGHT:
            row = 2;
            flip = true;
            break;

        default:
            row = 0;
            break;
    }

    Rectangle src = {
        (float)(player->currentFrame * player->frameWidth),
        (float)(row * player->frameHeight),
        (float)player->frameWidth,
        (float)player->frameHeight
    };

    if (flip)
        src.width = -src.width;

    Rectangle dst = {
        player->position.x,
        player->position.y,
        (float)player->width,
        (float)player->height
    };

    DrawTexturePro(player->spriteSheet, src, dst,
                   (Vector2){0, 0}, 0.0f, WHITE);
}