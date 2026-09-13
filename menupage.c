#include "raylib.h"

static Texture2D background;
static Rectangle startBtnBounds;
static Rectangle manualBtnBounds;
static bool isInitialized = false;

// Basic, flat button rendering
void DrawButton(Rectangle bounds, const char *text, Color btnColor)
{
    // Draw solid button background
    DrawRectangleRec(bounds, btnColor);
    DrawRectangleLinesEx(bounds, 2, BLACK); // Simple 2px border

    // Draw centered text
    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);
    float textX = bounds.x + (bounds.width - textWidth) / 2.0f;
    float textY = bounds.y + (bounds.height - fontSize) / 2.0f;
    
    DrawText(text, (int)textX, (int)textY, fontSize, BLACK);
}

void InitMenuPage(int screenWidth, int screenHeight)
{
    background = LoadTexture("forcover (1).png");
    isInitialized = true;
}

// Return codes: 0 = None, 1 = Start Game, 2 = See Manual
int UpdateAndDrawMenuPage(int screenWidth, int screenHeight)
{
    if (!isInitialized) InitMenuPage(screenWidth, screenHeight);

    // Layout math
    float btnWidth = 220.0f;
    float btnHeight = 50.0f;
    float spacing = 15.0f;
    float startY = (screenHeight - (btnHeight * 2 + spacing)) / 2.0f + 60.0f;

    startBtnBounds = (Rectangle){ (screenWidth - btnWidth) / 2.0f, startY, btnWidth, btnHeight };
    manualBtnBounds = (Rectangle){ (screenWidth - btnWidth) / 2.0f, startY + btnHeight + spacing, btnWidth, btnHeight };

    // Mouse Interaction
    Vector2 mousePoint = GetMousePosition();
    bool startHovered = CheckCollisionPointRec(mousePoint, startBtnBounds);
    bool manualHovered = CheckCollisionPointRec(mousePoint, manualBtnBounds);

    int action = 0;
    if ((startHovered && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) || IsKeyPressed(KEY_ENTER))
    {
        action = 1;
    }
    else if (manualHovered && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        action = 2;
    }

    // --- GRAPHICS DRAWS ---
    if (background.id > 0)
    {
        DrawTexturePro(
            background,
            (Rectangle){ 0, 0, (float)background.width, (float)background.height },
            (Rectangle){ 0, 0, (float)screenWidth, (float)screenHeight },
            (Vector2){ 0, 0 },
            0.0f,
            WHITE
        );
    }
    else
    {
        ClearBackground(BEIGE);
    }

    // Render Minimal Buttons
    DrawButton(startBtnBounds, "READY TO RUSH?", PINK);
    DrawButton(manualBtnBounds, "SEE MANUAL", PINK);

    return action;
}

void UnloadMenuPage(void)
{
    if (isInitialized) {
        if (background.id > 0) UnloadTexture(background);
        isInitialized = false;
    }
}