#include <stdio.h>
#include <string.h>
#include <math.h>
#include "graph.h"
#include <stdlib.h>


int load_nodes(Graph *g, const char*filename){
    int count = 0;

FILE *fp = fopen(filename, "r");
if(fp == NULL){
    printf("there was an error when trying to read the file");
    return 0;
};


char lines[500];

fgets(lines, sizeof(lines), fp);

while(count < MAX_NODES && fscanf(fp, "%d,%39[^,],%d,%d",
                           &g->nodes[count].id, 
                           g->nodes[count].name,
                            &g->nodes[count].x,
                             &g->nodes[count].y) == 4){
                                count++;
                            }
                            g->node_count = count;
                            fclose(fp);

return 1;
}

int load_edges(Graph *g, const char *filename){

    int count = 0;
    char lines[500];

    FILE *fp = fopen(filename, "r");

    if(fp == NULL){
        printf("there was an error when trying to read the file \n");
        return 0;
    }
    fgets(lines, sizeof(lines), fp);

    while(count < MAX_EDGES && fscanf(fp, "%d,%d,%d,%f,%f,%f,%f,%f",
                                &g->edges[count].id,
                            &g->edges[count].from,
                        &g->edges[count].to,
                    &g->edges[count].distance_km,
                &g->edges[count].minutes[SLOT_MORNING],
                &g->edges[count].minutes[SLOT_AFTERNOON],
            &g->edges[count].minutes[SLOT_EVENING],
        &g->edges[count].minutes[SLOT_NIGHT]) == 8){
            count++;

        }
g->edge_count = count;
fclose(fp);
return 1;

}
float edge_minutes(const Edge *e, int slot, int rain){
    float base = e->minutes[slot];

    if(rain == 1){
        return base * 1.3f;
    }

    return base;
}