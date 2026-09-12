#include "raylib.h"

static Texture2D background;
static Font pixelFont;

static Color pinkFill;
static Color hoverFill;

static Rectangle startBtnBounds;
static Rectangle manualBtnBounds;

static bool isInitialized = false;
static bool customFontLoaded = false;

// Custom pixel-art button rendering engine
void DrawPixelButton(Rectangle bounds, const char *text, Font font, float fontSize, Color btnColor, Color textColor, bool pressed)
{
    float roundness = 0.5f;
    int segments = 8;
    float yOffset = pressed ? 3.0f : 0.0f;

    // 1. Drop Shadow
    if (!pressed)
    {
        Rectangle shadowRec = { bounds.x + 3, bounds.y + 4, bounds.width, bounds.height };
        DrawRectangleRounded(shadowRec, roundness, segments, (Color){ 20, 20, 30, 255 });
    }

    // 2. Main Button Box
    Rectangle activeBounds = { bounds.x, bounds.y + yOffset, bounds.width, bounds.height };

    // 3. Outer Black Border
    DrawRectangleRounded(activeBounds, roundness, segments, BLACK);

    // 4. Inner Fill
    Rectangle fillRec = { activeBounds.x + 2, activeBounds.y + 2, activeBounds.width - 4, activeBounds.height - 4 };
    DrawRectangleRounded(fillRec, roundness, segments, btnColor);

    // 5. White Gloss Line
    DrawRectangle(fillRec.x + 10, fillRec.y + 3, fillRec.width - 20, 2, WHITE);

    // 6. Centered Text with Shadow
    Vector2 textSize = MeasureTextEx(font, text, fontSize, 2.0f);
    Vector2 textPos = {
        activeBounds.x + (activeBounds.width - textSize.x) / 2.0f,
        activeBounds.y + (activeBounds.height - textSize.y) / 2.0f
    };
    
    Vector2 shadowPos = { textPos.x + 1.0f, textPos.y + 1.0f };
    DrawTextEx(font, text, shadowPos, fontSize, 2.0f, (Color){ 0, 0, 0, 150 });
    DrawTextEx(font, text, textPos, fontSize, 2.0f, textColor);
}

void InitMenuPage(int screenWidth, int screenHeight)
{
    background = LoadTexture("forcover (1).png");
    pixelFont = GetFontDefault();
    customFontLoaded = false; 

    pinkFill = (Color){ 255, 120, 170, 255 };
    hoverFill = (Color){ 255, 90, 150, 255 };

    isInitialized = true;
}

// Return codes: 0 = None, 1 = Start Game, 2 = See Manual
int UpdateAndDrawMenuPage(int screenWidth, int screenHeight)
{
    if (!isInitialized) InitMenuPage(screenWidth, screenHeight);

    float fontSize = customFontLoaded ? 22.0f : 10.0f;
    
    Vector2 startTextSize = MeasureTextEx(pixelFont, "READY TO RUSH?", fontSize, 2.0f);
    Vector2 manualTextSize = MeasureTextEx(pixelFont, "SEE MANUAL", fontSize, 2.0f);

    float maxTextWidth = (startTextSize.x > manualTextSize.x) ? startTextSize.x : manualTextSize.x;
    float btnWidth = maxTextWidth + 40.0f;
    float btnHeight = 50.0f;
    float spacing = 15.0f;

    float startY = (screenHeight - (btnHeight * 2 + spacing)) / 2.0f + 60.0f;

    startBtnBounds = (Rectangle){ (screenWidth - btnWidth) / 2.0f, startY, btnWidth, btnHeight };
    manualBtnBounds = (Rectangle){ (screenWidth - btnWidth) / 2.0f, startY + btnHeight + spacing, btnWidth, btnHeight };

    Vector2 mousePoint = GetMousePosition();

    bool startHovered = CheckCollisionPointRec(mousePoint, startBtnBounds);
    bool startPressed = startHovered && IsMouseButtonDown(MOUSE_BUTTON_LEFT);

    bool manualHovered = CheckCollisionPointRec(mousePoint, manualBtnBounds);
    bool manualPressed = manualHovered && IsMouseButtonDown(MOUSE_BUTTON_LEFT);

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
        ClearBackground(RAYWHITE);
    }

    DrawPixelButton(startBtnBounds, "READY TO RUSH?", pixelFont, fontSize, startHovered ? hoverFill : pinkFill, WHITE, startPressed);
    DrawPixelButton(manualBtnBounds, "SEE MANUAL", pixelFont, fontSize, manualHovered ? hoverFill : pinkFill, WHITE, manualPressed);

    return action;
}

void UnloadMenuPage(void)
{
    if (isInitialized) {
        if (background.id > 0) UnloadTexture(background);
        if (customFontLoaded && pixelFont.texture.id > 0) UnloadFont(pixelFont);
        isInitialized = false;
    }
}