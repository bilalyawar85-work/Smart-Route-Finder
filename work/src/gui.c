#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "graph.h"
#include "dijkstra.h"
#include "gui.h"


int ask_number(const char question[], int low, int high)
{
    int x;    
    int ok;   
    int c;    

    while (1)
    {
        printf("%s", question);
        ok = scanf("%d", &x);

        
        if (ok == EOF)
        {
            return low;
        }

        if (ok != 1)
        {
            
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            printf("invalid\n");
        }
        else if (x < low || x > high)
        {
            printf("invalid\n");
        }
        else
        {
            return x;
        }
    }
}

// ---------------------------------------------------------------

// ---------------------------------------------------------------
void run_console(const Graph *g)
{
    const char *names[4] = {"morning", "afternoon", "evening", "night"};
    int again = 1;   

    while (again == 1)
    {
        int i;         
        int s;         
        int start;     
        int end;       
        int slot;      
        int rain;      
        Route route;   
        Route other;   

        
        printf("\n");
        for (i = 0; i < g->node_count; i++)
        {
            printf("%d - %s\n", i, g->nodes[i].name);
        }

        
        start = ask_number("start: ", 0, g->node_count - 1);
        end = ask_number("destination: ", 0, g->node_count - 1);
        slot = ask_number("time slot (0 morning, 1 afternoon, 2 evening, 3 night): ", 0, 3);
        rain = ask_number("rain (0 no, 1 yes): ", 0, 1);

        
        route = find_route(g, start, end, slot, rain);

        
        if (route.found == 0)
        {
            printf("No route\n");
        }
        else
        {
            printf("\nroute: ");
            for (i = 0; i < route.count; i++)
            {
                printf("%s", g->nodes[route.path[i]].name);
                if (i < route.count - 1)
                {
                    printf(" > ");
                }
            }
            printf("\n");
            printf("minutes: %.1f\n", route.total_minutes);
            printf("km: %.1f\n", route.total_km);
        }

        
        printf("\nsame trip at different times:\n");
        for (s = 0; s < 4; s++)
        {
            other = find_route(g, start, end, s, rain);
            if (other.found == 1)
            {
                printf("%s: %.1f minutes\n", names[s], other.total_minutes);
            }
        }

        again = ask_number("\nagain? (1 yes, 0 no): ", 0, 1);
    }
}

// ---------------------------------------------------------------
// map window
// ---------------------------------------------------------------
void run_gui(const Graph *g)
{
    const char *names[4] = {"morning", "afternoon", "evening", "night"};
    int start = -1;        
    int end = -1;          
    int slot = 0;          
    int rain = 0;          
    int need_update = 0;   
    Route route;           

    int i;                 
    int j;                 
    int a;                 
    int b;                 
    int e;                 
    char label[NAME_LEN];  

    route.found = 0;
    route.count = 0;
    route.total_minutes = 0;
    route.total_km = 0;

    InitWindow(1000, 700, "Smart Route Finder");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mouse = GetMousePosition();
            for (i = 0; i < g->node_count; i++)
            {
                Vector2 center = {(float)g->nodes[i].x, (float)g->nodes[i].y};
                if (CheckCollisionPointCircle(mouse, center, 14))
                {
                    if (start == -1)
                    {
                        start = i;        
                    }
                    else if (end == -1)
                    {
                        if (i != start)
                        {
                            end = i;      
                        }
                    }
                    else
                    {
                        start = i;        
                        end = -1;
                    }
                    need_update = 1;
                    break;
                }
            }
        }

        // keys
        if (IsKeyPressed(KEY_ONE))   { slot = 0; need_update = 1; }
        if (IsKeyPressed(KEY_TWO))   { slot = 1; need_update = 1; }
        if (IsKeyPressed(KEY_THREE)) { slot = 2; need_update = 1; }
        if (IsKeyPressed(KEY_FOUR))  { slot = 3; need_update = 1; }
        if (IsKeyPressed(KEY_R))
        {
            rain = 1 - rain;      
            need_update = 1;
        }
        if (IsKeyPressed(KEY_C))
        {
            start = -1;
            end = -1;
            need_update = 1;
        }


        if (need_update == 1)
        {
            if (start != -1 && end != -1)
            {
                route = find_route(g, start, end, slot, rain);
            }
            else
            {
                route.found = 0;
                route.count = 0;
            }
            need_update = 0;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // roads first, so the circles sit on top
        for (i = 0; i < g->edge_count; i++)
        {
            a = g->edges[i].from;
            b = g->edges[i].to;
            DrawLine(g->nodes[a].x, g->nodes[a].y, g->nodes[b].x, g->nodes[b].y, GRAY);
        }

        
        if (route.found == 1)
        {
            for (i = 0; i < route.count - 1; i++)
            {
                e = route.edges[i];
                a = g->edges[e].from;
                b = g->edges[e].to;
                Vector2 p1 = {(float)g->nodes[a].x, (float)g->nodes[a].y};
                Vector2 p2 = {(float)g->nodes[b].x, (float)g->nodes[b].y};
                DrawLineEx(p1, p2, 5, ORANGE);
            }
        }

        
        for (i = 0; i < g->node_count; i++)
        {
            Color color = DARKBLUE;
            if (i == start)
            {
                color = GREEN;
            }
            if (i == end)
            {
                color = RED;
            }
            DrawCircle(g->nodes[i].x, g->nodes[i].y, 14, color);

            
            strncpy(label, g->nodes[i].name, NAME_LEN - 1);
            label[NAME_LEN - 1] = '\0';
            for (j = 0; label[j] != '\0'; j++)
            {
                if (label[j] == '_')
                {
                    label[j] = ' ';
                }
            }
            DrawText(label, g->nodes[i].x - 30, g->nodes[i].y + 18, 14, BLACK);
        }

        
        DrawText(TextFormat("time: %s (keys 1-4)", names[slot]), 20, 580, 18, BLACK);
        DrawText(TextFormat("rain: %s (key R)", rain ? "yes" : "no"), 20, 605, 18, BLACK);
        DrawText("click start, then destination. C clears.", 20, 670, 16, DARKGRAY);

        if (route.found == 1)
        {
            DrawText(TextFormat("minutes: %.1f", route.total_minutes), 450, 580, 18, BLACK);
            DrawText(TextFormat("km: %.1f", route.total_km), 450, 605, 18, BLACK);
        }
        else if (start != -1 && end != -1)
        {
            DrawText("No route", 450, 580, 18, RED);
        }

        EndDrawing();
    }

    CloseWindow();
}
