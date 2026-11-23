/* dijkstra.h - guessed from the stub file. replace with person b's real one */
#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "graph.h"

typedef struct {
    int found;               /* 1 if a route exists */
    int count;               /* number of nodes in path */
    int path[MAX_NODES];     /* node ids, start to end */
    int edges[MAX_NODES];    /* edge ids, count - 1 of them */
    float total_minutes;
    float total_km;
} Route;

Route find_route(const Graph *g, int start, int end, int slot, int rain);

#endif