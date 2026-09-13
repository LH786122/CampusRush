#include "hurdle.h"


static const Vector2 HURDLE_POSITIONS[HURDLE_COUNT] = {

    {177,231}, {275,191}, {432,184}, {800,43}, {782,224}, {1049,193}, {356,375}, {793,357}, {197,440}, {354,458},

    {845,440}, {1132,417}, {486,520}, {928,518}, {1293,502}, {280,590}, {760,563}, {1136,574}, {576,641}, {961,632},

    {1152,657}, {768,756}, {1042,747}, {672,899}, {800,917}, {975,863}
};


void CreateHurdles(Hurdle hurdles[])
{
    for (int i = 0; i < HURDLE_COUNT; i++)
    {
        hurdles[i].position = HURDLE_POSITIONS[i];

        hurdles[i].width = 32;
        hurdles[i].height = 32;

        hurdles[i].hurdle_collision = false;
    }
}



void DrawHurdle(Hurdle hurdle, Texture2D hurdleTexture)
{
    if (!hurdle.hurdle_collision)
    {
        Rectangle source = {
            0,
            0,
            (float)hurdleTexture.width,
            (float)hurdleTexture.height
        };


        Rectangle destination = {
            hurdle.position.x,
            hurdle.position.y,
            hurdle.width,
            hurdle.height
        };


        Vector2 origin = {
            hurdle.width / 2,
            hurdle.height / 2
        };


        DrawTexturePro(
            hurdleTexture,
            source,
            destination,
            origin,
            0.0f,
            WHITE
        );
    }
}


bool CheckHurdleCollision(Hurdle *hurdle, Rectangle playerRect)
{
    if (!hurdle->hurdle_collision &&
        CheckCollisionRecs(
            (Rectangle){
                hurdle->position.x - hurdle->width / 2,
                hurdle->position.y - hurdle->height / 2,
                hurdle->width,
                hurdle->height
            },
            playerRect
        ))
    {
        hurdle->hurdle_collision = true;

        return true;
    }

    return false;
}