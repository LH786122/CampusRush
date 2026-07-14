#include "world.h"
#include <stdio.h>

// NOTE: Building rectangles below are estimated from the IUT campus map image
// (assets/map.png, 2048x1529). Open the image in an editor and adjust the
// x, y, width, height values here if you want tighter/looser collision boxes
// around any specific building.

void World_Load(World *world) {
    world->mapTexture = LoadTexture("assets/map.png");
    world->mapWidth = world->mapTexture.width;   // 2048
    world->mapHeight = world->mapTexture.height; // 1529

    int i = 0;

    world->buildings[i] = (Rectangle){ 100, 225, 435, 235 };
    world->buildingNames[i++] = "Academic Building-2";

    world->buildings[i] = (Rectangle){ 655, 225, 410, 235 };
    world->buildingNames[i++] = "North Hall Res A";

    world->buildings[i] = (Rectangle){ 1106, 225, 410, 235 };
    world->buildingNames[i++] = "North Hall Res B";

    world->buildings[i] = (Rectangle){ 1557, 225, 390, 235 };
    world->buildingNames[i++] = "North Hall Res C";

    world->buildings[i] = (Rectangle){ 100, 795, 435, 245 };
    world->buildingNames[i++] = "Academic Building-1";

    world->buildings[i] = (Rectangle){ 655, 795, 410, 245 };
    world->buildingNames[i++] = "South Hall Res A";

    world->buildings[i] = (Rectangle){ 1106, 795, 410, 245 };
    world->buildingNames[i++] = "South Hall Res B";

    world->buildings[i] = (Rectangle){ 1557, 795, 390, 245 };
    world->buildingNames[i++] = "South Hall Res C";

    world->buildings[i] = (Rectangle){ 1905, 155, 143, 915 };
    world->buildingNames[i++] = "Male Common Facs";

    world->buildings[i] = (Rectangle){ 143, 1147, 390, 230 };
    world->buildingNames[i++] = "Admin Bldg";

    world->buildings[i] = (Rectangle){ 614, 1101, 370, 320 };
    world->buildingNames[i++] = "Cafet / Library";

    world->buildings[i] = (Rectangle){ 1188, 1101, 760, 275 };
    world->buildingNames[i++] = "Student Centre & Gymnasium";

    world->buildings[i] = (Rectangle){ 1188, 30, 205, 125 };
    world->buildingNames[i++] = "Pump House";

    world->buildingCount = i;

    // Goal: courtyard just in front of Academic Building-2's entrance
    world->goalZone = (Rectangle){ 200, 470, 235, 90 };

    // Start: on the open ground in front of (south of) the Student Centre & Gymnasium
    world->startPosition = (Vector2){ 1560, 1400 };
}

void World_Unload(World *world) {
    UnloadTexture(world->mapTexture);
}

void World_Draw(World *world) {
    DrawTexture(world->mapTexture, 0, 0, WHITE);

    // Uncomment to visualize collision boxes while tuning:
    // for (int i = 0; i < world->buildingCount; i++) {
    //     DrawRectangleLinesEx(world->buildings[i], 2, RED);
    // }
}

void World_DrawGoalMarker(World *world) {
    Rectangle g = world->goalZone;
    DrawRectangleLinesEx(g, 3, LIME);
    DrawText("GOAL: Academic Building-2", (int)g.x - 20, (int)g.y - 28, 20, LIME);
}

bool World_CheckCollision(World *world, Rectangle playerRect) {
    for (int i = 0; i < world->buildingCount; i++) {
        if (CheckCollisionRecs(playerRect, world->buildings[i])) {
            return true;
        }
    }
    return false;
}

bool World_CheckGoal(World *world, Rectangle playerRect) {
    return CheckCollisionRecs(playerRect, world->goalZone);
}
