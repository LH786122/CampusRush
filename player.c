#include "player.h"
#include <math.h>

#define FRAME_TIME 0.14f   // slower walk cycle, ~7 fps (was 0.09f / ~11fps)

void Player_Load(Player *player, Vector2 startPos) {
    player->spriteSheet = LoadTexture("assets/player_spritesheet.png");

    if (player->spriteSheet.width == 0 || player->spriteSheet.height == 0) {
        TraceLog(LOG_ERROR, "Could not load assets/player_spritesheet.png - "
                             "make sure the file exists next to the .exe, "
                             "inside an 'assets' folder.");
    }

    // Sheet layout: 8 columns (walk frames) x 3 rows (down, up, side)
    player->framesPerRow = 8;
    player->frameWidth = player->spriteSheet.width / player->framesPerRow;
    player->frameHeight = player->spriteSheet.height / 3;

    // Guard against divide-by-zero / NaN sizes if the texture failed to load,
    // which previously corrupted the camera and made the whole screen go black.
    if (player->frameWidth <= 0) player->frameWidth = 64;
    if (player->frameHeight <= 0) player->frameHeight = 64;

    player->currentFrame = 0;
    player->frameTimer = 0.0f;
    player->frameTime = FRAME_TIME;

    player->direction = DIR_DOWN;
    player->isMoving = false;

    player->position = startPos;
    player->speed = 190.0f; // was 260 - a bit slower, less frantic

    // On-screen size: scaled down from the large source frames, aspect preserved
    player->height = 100; // was 70 - bigger, more visible character
    player->width = (int)(player->height * ((float)player->frameWidth / (float)player->frameHeight));
}

void Player_Unload(Player *player) {
    UnloadTexture(player->spriteSheet);
}

Rectangle Player_GetCollisionRect(Player *player) {
    // Collision box around the character's feet, smaller than the full sprite
    float footW = player->width * 0.5f;
    float footH = player->height * 0.20f;
    float x = player->position.x + (player->width - footW) / 2.0f;
    float y = player->position.y + player->height - footH;
    return (Rectangle){ x, y, footW, footH };
}

void Player_Update(Player *player, World *world, float dt) {
    Vector2 move = { 0, 0 };

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) move.x += 1;
    if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)) move.x -= 1;
    if (IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) move.y += 1;
    if (IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W)) move.y -= 1;

    float len = sqrtf(move.x * move.x + move.y * move.y);
    player->isMoving = (len > 0.0f);
    if (len > 0.0f) {
        move.x /= len;
        move.y /= len;
    }

    // Pick which direction row/flip to show. On diagonal movement, whichever
    // axis is dominant wins (so holding up+left mostly shows the left walk).
    if (player->isMoving) {
        if (fabsf(move.x) >= fabsf(move.y)) {
            player->direction = (move.x < 0) ? DIR_LEFT : DIR_RIGHT;
        } else {
            player->direction = (move.y < 0) ? DIR_UP : DIR_DOWN;
        }
    }

    // Advance the walk-cycle only while actually moving; freeze on frame 0 (a
    // mid-stride pose) when idle.
    if (player->isMoving) {
        player->frameTimer += dt;
        if (player->frameTimer >= player->frameTime) {
            player->frameTimer -= player->frameTime;
            player->currentFrame = (player->currentFrame + 1) % player->framesPerRow;
        }
    } else {
        player->currentFrame = 0;
        player->frameTimer = 0.0f;
    }

    // Move on X axis, resolve collision, then Y axis, resolve collision.
    Vector2 oldPos = player->position;

    player->position.x += move.x * player->speed * dt;
    if (World_CheckCollision(world, Player_GetCollisionRect(player))) {
        player->position.x = oldPos.x;
    }

    oldPos = player->position;
    player->position.y += move.y * player->speed * dt;
    if (World_CheckCollision(world, Player_GetCollisionRect(player))) {
        player->position.y = oldPos.y;
    }

    // Clamp to map bounds
    if (player->position.x < 0) player->position.x = 0;
    if (player->position.y < 0) player->position.y = 0;
    if (player->position.x + player->width > world->mapWidth)
        player->position.x = (float)(world->mapWidth - player->width);
    if (player->position.y + player->height > world->mapHeight)
        player->position.y = (float)(world->mapHeight - player->height);
}

void Player_Draw(Player *player) {
    int row;
    bool flip = false;

    switch (player->direction) {
        case DIR_DOWN:  row = 0; break;
        case DIR_UP:    row = 1; break;
        case DIR_LEFT:  row = 2; flip = false; break;
        case DIR_RIGHT: row = 2; flip = true;  break;
        default:        row = 0; break;
    }

    Rectangle src = {
        (float)(player->currentFrame * player->frameWidth),
        (float)(row * player->frameHeight),
        (float)player->frameWidth,
        (float)player->frameHeight
    };
    if (flip) src.width = -src.width; // mirror the side-view frame for DIR_RIGHT

    Rectangle dst = { player->position.x, player->position.y,
                       (float)player->width, (float)player->height };

    DrawTexturePro(player->spriteSheet, src, dst, (Vector2){ 0, 0 }, 0.0f, WHITE);
}
