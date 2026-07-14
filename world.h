#ifndef WORLD_H
#define WORLD_H

#include "raylib.h"

#define MAX_BUILDINGS 13

typedef struct World {
    Texture2D mapTexture;
    Rectangle buildings[MAX_BUILDINGS];
    const char *buildingNames[MAX_BUILDINGS];
    int buildingCount;

    Rectangle goalZone;      // player must reach this to win (Academic Building-2 courtyard)
    Vector2 startPosition;   // player spawn (in front of Student Centre & Gym)

    int mapWidth;
    int mapHeight;
} World;

void World_Load(World *world);
void World_Unload(World *world);
void World_Draw(World *world);
void World_DrawGoalMarker(World *world);

// Returns true if playerRect overlaps ANY building (i.e. blocked)
bool World_CheckCollision(World *world, Rectangle playerRect);

// Returns true if playerRect overlaps the goal zone
bool World_CheckGoal(World *world, Rectangle playerRect);

#endif // WORLD_H
