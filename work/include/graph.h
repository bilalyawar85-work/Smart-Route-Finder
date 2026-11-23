#ifndef GRAPH_H
#define GRAPH_H

#define MAX_NODES 20
#define MAX_EDGES 50
#define NAME_LEN 40

/* time-of-day slots: the column order in edges.csv */
#define SLOT_MORNING   0
#define SLOT_AFTERNOON 1
#define SLOT_EVENING   2
#define SLOT_NIGHT     3
#define NUM_SLOTS      4

/* One place on the map. node_id in nodes.csv = its index in the nodes[] array. */
typedef struct {
    int id;
    char name[NAME_LEN];
    int x, y;          /* where to draw it on the screen */
} Node;

/* One road between two places (works in both directions). */
typedef struct {
    int id;
    int from, to;      /* node indexes */
    float distance_km;
    float minutes[NUM_SLOTS]; /* travel time for each time slot */
} Edge;

typedef struct {
    Node nodes[MAX_NODES];
    int node_count;
    Edge edges[MAX_EDGES];
    int edge_count;
} Graph;

/*---- Person A writes these (graph.c) ----*/

/* Read nodes.csv into g->nodes. Returns 1 if OK, 0 if the file can't be opened. */
int load_nodes(Graph *g, const char *filename);

/* Read edges.csv into g->edges. Returns 1 if OK, 0 if the file can't be opened. */
int load_edges(Graph *g, const char *filename);

/* Travel time of one road in a time slot. If rain is 1, it is 30% slower. */
float edge_minutes(const Edge *e, int slot, int rain);

#endif