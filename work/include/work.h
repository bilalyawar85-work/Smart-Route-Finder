
#ifndef RAYLIB_STUB_H
#define RAYLIB_STUB_H

// ---------- types ----------
typedef struct {
    float x;
    float y;
} Vector2;

typedef struct {
    unsigned char r, g, b, a;
} Color;

// ---------- colors ----------
#define RAYWHITE (Color){245, 245, 245, 255}
#define BLACK    (Color){0, 0, 0, 255}
#define GRAY     (Color){130, 130, 130, 255}
#define DARKGRAY (Color){80, 80, 80, 255}
#define DARKBLUE (Color){0, 82, 172, 255}
#define GREEN    (Color){0, 228, 48, 255}
#define RED      (Color){230, 41, 55, 255}
#define ORANGE   (Color){255, 161, 0, 255}

// ---------- mouse and keys ----------
#define MOUSE_BUTTON_LEFT 0
#define KEY_ONE   49
#define KEY_TWO   50
#define KEY_THREE 51
#define KEY_FOUR  52
#define KEY_C     67
#define KEY_R     82

// ---------- window ----------
void InitWindow(int width, int height, const char *title);
void SetTargetFPS(int fps);
int WindowShouldClose(void);
void CloseWindow(void);

// ---------- drawing ----------
void BeginDrawing(void);
void EndDrawing(void);
void ClearBackground(Color color);
void DrawCircle(int centerX, int centerY, float radius, Color color);
void DrawLine(int startX, int startY, int endX, int endY, Color color);
void DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color);
void DrawText(const char *text, int posX, int posY, int fontSize, Color color);
const char *TextFormat(const char *text, ...);

// ---------- input ----------
int IsMouseButtonPressed(int button);
Vector2 GetMousePosition(void);
int CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius);
int IsKeyPressed(int key);

#endif
