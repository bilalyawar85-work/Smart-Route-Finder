#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "graph.h"

typedef struct {
    int found;               
    int count;               
    int path[MAX_NODES];     
    int edges[MAX_NODES];    
    float total_minutes;
    float total_km;
} Route;

Route find_route(const Graph *g, int start, int end, int slot, int rain);

#endif