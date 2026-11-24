#include <stdio.h>
#include "graph.h"
#include "gui.h"

int main(void)
{
    int a;
    printf("Enter 0 for Console Version, Enter 1 for Map Version\n");
    scanf("%d", &a);
    Graph g;

    // set counts to 0 first, uninitialized variables hold garbage
    g.node_count = 0;
    g.edge_count = 0;

    // load the data, 0 means the loading failed
    if (load_nodes(&g, "data/nodes.csv") == 0)
    {
        printf("error: could not load data/nodes.csv\n");
        return 1;
    }
    if (load_edges(&g, "data/edges.csv") == 0)
    {
        printf("error: could not load data/edges.csv\n");
        return 1;
    }

    
    if(a==0){
    run_console(&g);
    }
    else
     run_gui(&g);

    return 0;
}
