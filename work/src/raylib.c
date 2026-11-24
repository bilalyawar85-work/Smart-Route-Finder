
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "raylib.h"

#define COLS 100          
#define ROWS 30          
#define MAX_PLACES 50
#define MAX_INFO 10

static char grid[ROWS][COLS + 1];       
static char info[MAX_INFO][100];       
static int info_count = 0;

static int frame = 0;                   
static Vector2 circles[MAX_PLACES];   
static char circle_chars[MAX_PLACES];   
static int circle_count = 0;
static Vector2 old_circles[MAX_PLACES]; 
static int old_count = 0;

static Vector2 mouse = {0, 0};
static int clicked = 0;              
static int key_pressed = 0;             

static char text_buffer[4][128];       
static int text_next = 0;

// put one character on the screen, pixels turned into rows and columns
static void put(int px, int py, char ch)
{
    int col = px / 10;
    int row = py / 24;

    if (px < 0 || py < 0 || col >= COLS || row >= ROWS)
    {
        return;
    }
    grid[row][col] = ch;
}

static void put_line(int x1, int y1, int x2, int y2, char ch)
{
    int t;              
    int steps = 100;

    for (t = 0; t <= steps; t++)
    {
        put(x1 + (x2 - x1) * t / steps, y1 + (y2 - y1) * t / steps, ch);
    }
}

static int same_color(Color a, Color b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b;
}


void InitWindow(int width, int height, const char *title)
{
    printf("[fake window opened %d x %d: %s]\n", width, height, title);
}

void SetTargetFPS(int fps)
{
    (void)fps;
}

void CloseWindow(void)
{
    printf("[fake window closed]\n");
}


int WindowShouldClose(void)
{
    frame++;
    clicked = 0;
    key_pressed = 0;

    if (frame == 2 && old_count > 0)
    {
        mouse = old_circles[0];
        clicked = 1;
        printf("[pretend user clicks the first place]\n");
    }
    if (frame == 3 && old_count > 0)
    {
        mouse = old_circles[old_count - 1];
        clicked = 1;
        printf("[pretend user clicks the last place]\n");
    }
    if (frame == 4)
    {
        key_pressed = KEY_THREE;
        printf("[pretend user presses 3 = evening]\n");
    }
    if (frame == 5)
    {
        key_pressed = KEY_R;
        printf("[pretend user presses R = rain]\n");
    }
    if (frame == 6)
    {
        key_pressed = KEY_C;
        printf("[pretend user presses C = clear]\n");
    }

    if (frame > 7)
    {
        return 1;
    }
    return 0;
}

void BeginDrawing(void)
{
    int r;   
    int c;  

    for (r = 0; r < ROWS; r++)
    {
        for (c = 0; c < COLS; c++)
        {
            grid[r][c] = ' ';
        }
        grid[r][COLS] = '\0';
    }
    info_count = 0;
    circle_count = 0;
}

void EndDrawing(void)
{
    int r;   
    int k;   

    
    for (k = 0; k < circle_count; k++)
    {
        put((int)circles[k].x, (int)circles[k].y, circle_chars[k]);
    }

    
    for (k = 0; k < circle_count; k++)
    {
        old_circles[k] = circles[k];
    }
    old_count = circle_count;

    if (frame == 1 || frame == 3 || frame == 5)
    {
        printf("\n===== fake window, frame %d =====\n", frame);
        for (r = 0; r < ROWS; r++)
        {
            printf("|%s|\n", grid[r]);
        }
        for (r = 0; r < info_count; r++)
        {
            printf("   %s\n", info[r]);
        }
    }
}

void ClearBackground(Color color)
{
    (void)color;
}

void DrawCircle(int centerX, int centerY, float radius, Color color)
{
    char ch = 'O';   

    (void)radius;
    if (same_color(color, GREEN))
    {
        ch = 'S'; 
    }
    if (same_color(color, RED))
    {
        ch = 'E';    
    }

    if (circle_count < MAX_PLACES)
    {
        circle_chars[circle_count] = ch;
        circles[circle_count].x = (float)centerX;
        circles[circle_count].y = (float)centerY;
        circle_count++;
    }
}

void DrawLine(int startX, int startY, int endX, int endY, Color color)
{
    (void)color;
    put_line(startX, startY, endX, endY, '.');
}

void DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color)
{
    (void)thick;
    (void)color;
    put_line((int)startPos.x, (int)startPos.y, (int)endPos.x, (int)endPos.y, '#');
}

void DrawText(const char *text, int posX, int posY, int fontSize, Color color)
{
    int k;   

    (void)fontSize;
    (void)color;

    
    if (posY >= 560)
    {
        if (info_count < MAX_INFO)
        {
            strncpy(info[info_count], text, 99);
            info[info_count][99] = '\0';
            info_count++;
        }
        return;
    }

    
    for (k = 0; text[k] != '\0'; k++)
    {
        put(posX + k * 10, posY + 24, text[k]);
    }
}

const char *TextFormat(const char *text, ...)
{
    va_list args;
    char *buffer = text_buffer[text_next];

    text_next = (text_next + 1) % 4;
    va_start(args, text);
    vsnprintf(buffer, 128, text, args);
    va_end(args);
    return buffer;
}


int IsMouseButtonPressed(int button)
{
    return button == MOUSE_BUTTON_LEFT && clicked == 1;
}

Vector2 GetMousePosition(void)
{
    return mouse;
}

int CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius)
{
    float dx = point.x - center.x;
    float dy = point.y - center.y;

    return dx * dx + dy * dy <= radius * radius;
}

int IsKeyPressed(int key)
{
    return key_pressed == key;
}
