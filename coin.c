#include "coin.h"
#include "blocked.h"


static Vector2 COIN_POSITIONS[] = {
    {24, 206}, {154, 270}, {67, 353}, {152, 382}, {237, 478},
    {356, 389}, {358, 496}, {282, 613}, {464, 53}, 
    {475, 404}, {549, 512}, {560, 653}, {618, 734},
    {594, 852}, {638, 877}, {641, 93}, {701, 339},
     {616, 532}, {670, 633}, {764, 839},
    {775, 42}, {800, 189}, {802, 270}, {789, 391},
    {775, 523}, {768, 622}, {836, 783}, {827, 900}, {874, 445},
    {894, 754}, {961, 87}, {1015, 87},
    {975, 841}, {948, 893}, {1015, 642}, {1031, 792}, {1141, 206},
     {1179, 393}, {1161, 689}, {1257, 105},
    {1228, 218}, {1259, 449}, {1257, 530}, {1378, 487}, {1374, 700}
};


void CreateCoins(Coin coins[])
{
    for (int i = 0; i < 40; i++)
    {
        coins[i].position = COIN_POSITIONS[i];
        coins[i].radius = 10.0f;
        coins[i].collected = false;
    }
}

void DrawCoin(Coin coin, Texture2D coinTexture)
{
    if (!coin.collected)
    {
        Rectangle source = {
            0,
            0,
            (float)coinTexture.width,
            (float)coinTexture.height
        };

        Rectangle destination = {
            coin.position.x,
            coin.position.y,
            20,
            20
        };

        Vector2 origin = {
            10,
            10
        };

        DrawTexturePro(
            coinTexture,
            source,
            destination,
            origin,
            0.0f,
            WHITE
        );
    }
}


bool CheckCoinCollision(Coin *coin, Rectangle playerRect)
{
    if (!coin->collected &&
        CheckCollisionCircleRec(
            coin->position,
            coin->radius,
            playerRect
        ))
    {
        coin->collected = true;
        return true;
    }

    return false;
}