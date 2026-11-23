#include "dijkstra.h"

#define BIG 1000000.0f

/* Helper 1: which UNVISITED place has the smallest dist?
 * Returns its index, or -1 if every place is visited. */
static int find_smallest(const float distance[], const int visited[], int n) {
    int best = -1;

    // TODO: loop i from 0 to n - 1
    //       skip places that are visited
    //       if best is still -1, or dist[i] < dist[best], best = i
    int i;
    for(i = 0; i<n; i++)
    // if a node is visited then we need to skip it cuz we have already found the shortest possible
    // distance of it.
    {
        if(visited[i] == 1)
        continue;
        if(best == -1 || distance[i] < distance[best])
        {
            best = i;
        }
    }

    return best;
}

/* Helper 2: walk back from `end` to `start` and fill route->path,
 * route->edges and route->total_km (start first, end last). */
static void build_path(const Graph *g, Route *route,
                       const int prev_node[], const int prev_edge[], int end) {
    // TODO 1: walk back from end: v = end; while v != -1 ...
    //         store each v in a temporary array, store prev_edge[v] in
    //         another temporary array, then set v = prev_node[v]
    int temp_nodes[MAX_NODES];
    // this basically stores all the nodes we visit, ----- NODES = LOCATIONS -----
    int temp_edges[MAX_NODES];
    // this basically stores all the edges associated with the nods ------- EDGES = ROADS ----------

    int count = 0;
    // it tracks how many elements we have stored 
    int c = end; // c is basically the current node we are processing
    // a while loop going to -1 so kyun ke -1 se pata chal jaye ga that we reached  the starting or no.
    while(c != -1) 
    {
        // ham ne i ko end meaning destination pe initialize karwa dia, for example agar hamari destination node 3 jo ke xyz location hai wo 
        // hai to phir  c = 3 ho jaye ga aur count = 0 hai to temp_nodes ke array mein 0th element pe hamare paas 3 a jaye ga //
        /*
        It will look something like this 
        TEMP_NODE[0]  = 3
        */
        temp_nodes[count] = c;
// the line below basically stores the road that led to the current node, to basically agar ham log node 3 pe road 2 se aye hain to ye
// wo save kare gi
       temp_edges[count] = prev_edge[c];
        count++;
        // increasing count so that the next one stores at the next element
       c = prev_node[c];
       // the line above helps us to go backword
    }
    // TODO 2: copy the temporary arrays into route->path / route->edges
    //         in reverse order, set route->count
    /*In this above piece of code we have gone from the destination to the starting point
    suppose hamari destination gulshan chowrangi at node 3 thi
    aur hamari starting sohrab goth at node 1 thi
    to we have gone from node 3 to node 2
    suppose our arrays looks something like this
    nodes = {3,2,1}
    edges = {3,2,1}
    count = 3
    but we want it to look like this 
    nodes = 1,2,3
    edges = 1,2,3
    thats why we will reverse this array*/

    // ------------------ REVERSING AN ARRAY -------------------//
    int i;
    // In this loop we started from the starting like where we want to go from till the endings, it helped us reverse that temp array
    for(i = 0; i<count; i++)
    {
        route->path[i] = temp_nodes[count-1-i];
        
    }
    // this is the same thing but for edges, 2 changes we used count -1 cuz we will always have 1 edge less than the nodes and we used
    // count - 2- i cuz I dry ran this program and we were getting errors, no errors on -2-i 
    for(i=0; i<count-1; i++)
    {
        route->edges[i] = temp_edges[count-2-i];    
    }
    route->count = count;
    

    // TODO 3: add up g->edges[e].distance_km for every road on the path
    // Calculating Distance for every road in kilometers 
    /*
    Lets suppose we have edges 1,2,3
    now the distance from edge 1 to 2 is 2.5 for example and from 2 to 3 is 10, so we need total distance 12.5 km*/
    double store = 0.0;
    for(i=0; i<route->count-1; i++)
    {
        // g.edges stores the distance in kilometers of each rode , so for road 1 the distance is 2.5 km for example and road 2 is
        // 10 kilometers so it will add them bth and store in store 
        store += g->edges[route->edges[i]].distance_km; 
        
    }
    //debug 1 : after the function ends store was being thrown away this helps us save the result globally.
    route->total_km = store;
}   

Route find_route(const Graph *g, int start, int end, int slot, int rain) {
    Route route;
    route.found = 0;
    route.count = 0;
    route.total_minutes = 0;
    route.total_km = 0;

    float distance[MAX_NODES];
    int visited[MAX_NODES];
    int prev_node[MAX_NODES];
    int prev_edge[MAX_NODES];

    // STEP 1: set up the arrays (dist = BIG, visited = 0, prev = -1),
    //         then dist[start] = 0
int i;
for(i = 0; i < g->node_count; i++)
{
    distance[i] = BIG;
    visited[i] = 0;
    prev_node[i] = -1;
    
}
distance[start] = 0;
    // STEP 2: repeat g->node_count times:
    
    int j;
    for(i = 0; i < g->node_count; i++)
    {
        //here u is storing the result of the find_smallest function
        int u = find_smallest(distance, visited, g->node_count);
        if(u == -1 || distance[u] >= BIG)
        break;
        visited[u] = 1;
        for(j = 0; j < g->edge_count; j++)
        {
            //debug 2 : this if statement is to make sure that we are not going back to the same node we came from, for example if we are at node 1 and we came from node 0 then we dont want to go back to node 0 again
            if(g->edges[j].from != u && g->edges[j].to != u)
            continue;
            int v = (g->edges[j].from == u) ? g->edges[j].to : g->edges[j].from;
            float new_dist = distance[u] + edge_minutes(&g->edges[j], slot, rain);
            if(new_dist< distance[v])
           {

            distance[v] = new_dist;
            prev_node[v] = u;
            prev_edge[v] = j;


        }
        }
        

    }
    
    //   u = find_smallest(dist, visited, g->node_count)
    //   if u == -1 or dist[u] >= BIG: break
    //   visited[u] = 1
    //   loop over all edges: find the neighbor v of u (skip other edges),
    //   new_dist = dist[u] + edge_minutes(&g->edges[i], slot, rain),
    //   if new_dist < dist[v]: update dist[v], prev_node[v], prev_edge[v]

    // STEP 3: if dist[end] >= BIG, there is no route: return route
    if(distance[end] >= BIG)
    return route;
    // STEP 4: route.found = 1, route.total_minutes = dist[end],
    //         build_path(g, &route, prev_node, prev_edge, end)
    route.found = 1;
    route.total_minutes = distance[end];
    build_path(g, &route, prev_node, prev_edge, end);
    

    return route;
} 