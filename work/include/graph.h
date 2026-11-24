#ifndef GRAPH_H
#define GRAPH_H

#define MAX_NODES 20
#define MAX_EDGES 50
#define NAME_LEN 40


#define SLOT_MORNING   0
#define SLOT_AFTERNOON 1
#define SLOT_EVENING   2
#define SLOT_NIGHT     3
#define NUM_SLOTS      4


typedef struct {
    int id;
    char name[NAME_LEN];
    int x, y;          
} Node;


typedef struct {
    int id;
    int from, to;      
    float distance_km;
    float minutes[NUM_SLOTS]; 
} Edge;

typedef struct {
    Node nodes[MAX_NODES];
    int node_count;
    Edge edges[MAX_EDGES];
    int edge_count;
} Graph;


int load_nodes(Graph *g, const char *filename);


int load_edges(Graph *g, const char *filename);


float edge_minutes(const Edge *e, int slot, int rain);

#endif