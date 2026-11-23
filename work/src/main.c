
#include <stdio.h>
#include "graph.h"
#include "gui.h"

int main(void)
{
    Graph g;

    g.node_count = 0;
    g.edge_count = 0;

    if (load_nodes(&g, "data/nodes.csv") == 0)
    {
        printf("Error: could not load nodes.csv\n");
        return 1;
    }

    if (load_edges(&g, "data/edges.csv") == 0)
    {
        printf("Error: could not load edges.csv\n");
        return 1;
    }

    run_gui(&g);

    return 0;
}
