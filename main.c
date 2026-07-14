#include "raylib.h"
#include "player.h"
#include "world.h"

#define TIME_LIMIT 40.0f   // seconds to reach Academic Building-2
#define SCREEN_W 1000
#define SCREEN_H 700

typedef enum GameState {
    STATE_MENU,
    STATE_PLAYING,
    STATE_WIN,
    STATE_LOSE
} GameState;

static Camera2D MakeCamera(Player *player) {
    Camera2D camera = { 0 };
    camera.target = (Vector2){ player->position.x + player->width / 2.0f,
                                player->position.y + player->height / 2.0f };
    camera.offset = (Vector2){ SCREEN_W / 2.0f, SCREEN_H / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    return camera;
}

int main(void) {
    InitWindow(SCREEN_W, SCREEN_H, "IUT Campus Rush - Reach Academic Building 2!");
    SetTargetFPS(60);

    World world;
    World_Load(&world);

    Player player;
    Player_Load(&player, world.startPosition);

    GameState state = STATE_MENU;
    float timeRemaining = TIME_LIMIT;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // ---- UPDATE ----
        switch (state) {
            case STATE_MENU: {
                if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
                    state = STATE_PLAYING;
                    timeRemaining = TIME_LIMIT;
                    player.position = world.startPosition;
                }
            } break;

            case STATE_PLAYING: {
                Player_Update(&player, &world, dt);

                timeRemaining -= dt;
                if (timeRemaining <= 0.0f) {
                    timeRemaining = 0.0f;
                    state = STATE_LOSE;
                }

                if (World_CheckGoal(&world, Player_GetCollisionRect(&player))) {
                    state = STATE_WIN;
                }
            } break;

            case STATE_WIN:
            case STATE_LOSE: {
                if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
                    state = STATE_PLAYING;
                    timeRemaining = TIME_LIMIT;
                    player.position = world.startPosition;
                }
            } break;
        }

        // ---- DRAW ----
        BeginDrawing();
        ClearBackground(BLACK);

        if (state == STATE_MENU) {
            DrawText("IUT CAMPUS RUSH", SCREEN_W/2 - MeasureText("IUT CAMPUS RUSH", 40)/2, 220, 40, RED);
            DrawText("Get from the Gym to Academic Building-2 before time runs out!",
                     SCREEN_W/2 - MeasureText("Get from the Gym to Academic Building-2 before time runs out!", 20)/2,
                     300, 20, RAYWHITE);
            DrawText("Move: WASD / Arrow Keys", SCREEN_W/2 - MeasureText("Move: WASD / Arrow Keys", 20)/2, 340, 20, GRAY);
            DrawText("Press ENTER to start", SCREEN_W/2 - MeasureText("Press ENTER to start", 22)/2, 400, 22, YELLOW);
        } else {
            Camera2D camera = MakeCamera(&player);
            BeginMode2D(camera);
                World_Draw(&world);
                World_DrawGoalMarker(&world);
                Player_Draw(&player);
            EndMode2D();

            // HUD
            DrawRectangle(0, 0, SCREEN_W, 50, Fade(BLACK, 0.5f));
            DrawText(TextFormat("Time: %.1f s", timeRemaining), 20, 12, 26,
                      (timeRemaining < 10.0f) ? RED : RAYWHITE);
            DrawText("Reach Academic Building-2!", SCREEN_W - 320, 12, 22, RAYWHITE);

            if (state == STATE_WIN) {
                DrawRectangle(0, 0, SCREEN_W, SCREEN_H, Fade(BLACK, 0.6f));
                DrawText("YOU WIN!", SCREEN_W/2 - MeasureText("YOU WIN!", 50)/2, 280, 50, GREEN);
                DrawText("Press ENTER to play again", SCREEN_W/2 - MeasureText("Press ENTER to play again", 20)/2, 350, 20, RAYWHITE);
            } else if (state == STATE_LOSE) {
                DrawRectangle(0, 0, SCREEN_W, SCREEN_H, Fade(BLACK, 0.6f));
                DrawText("TIME'S UP - YOU LOSE", SCREEN_W/2 - MeasureText("TIME'S UP - YOU LOSE", 50)/2, 280, 50, RED);
                DrawText("Press ENTER to try again", SCREEN_W/2 - MeasureText("Press ENTER to try again", 20)/2, 350, 20, RAYWHITE);
            }
        }

        EndDrawing();
    }

    Player_Unload(&player);
    World_Unload(&world);
    CloseWindow();

    return 0;
}
