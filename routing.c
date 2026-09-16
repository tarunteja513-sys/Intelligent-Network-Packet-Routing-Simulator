#include <stdio.h>
#include <limits.h>

#define MAX_NODES 20

/*
 * Function: findMinDistance
 *
 * This function searches for the unvisited node
 * that currently has the smallest distance value.
 *
 * distance[] stores the minimum known distance
 * from the source node.
 *
 * visited[] tells whether a node has already been
 * processed by Dijkstra's algorithm.
 *
 * Returns:
 * The node number with the minimum distance.
 * Returns -1 if no suitable node is found.
 */
int findMinDistance(int distance[], int visited[], int n)
{
    int minDistance = INT_MAX;
    int minNode = -1;

    /* Check every node to find the closest unvisited node */
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0 && distance[i] < minDistance)
        {
            minDistance = distance[i];
            minNode = i;
        }
    }

    return minNode;
}

/*
 * Function: printPath
 *
 * This function reconstructs and prints the shortest
 * path from the source node to the given destination.
 *
 * previous[] stores the previous node in the shortest
 * path for each node.
 */
void printPath(int previous[], int destination)
{
    int path[MAX_NODES];
    int count = 0;
    int node = destination;

    /*
     * Follow the previous-node information backwards
     * until the source node is reached.
     */
    while (node != -1)
    {
        path[count] = node;
        count++;
        node = previous[node];
    }

    /*
     * The path was stored in reverse order,
     * so print it from the last stored node
     * back to the destination.
     */
    for (int i = count - 1; i >= 0; i--)
    {
        printf("%d", path[i]);

        if (i != 0)
        {
            printf(" -> ");
        }
    }
}

/*
 * Function: dijkstra
 *
 * This function implements Dijkstra's shortest-path
 * algorithm.
 *
 * graph[][] represents the network topology.
 * n represents the number of nodes.
 * source represents the starting node.
 *
 * The algorithm calculates the minimum-cost route
 * from the source node to all other reachable nodes.
 */
void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int source)
{
    /*
     * distance[] stores the minimum cost from the
     * source node to every other node.
     */
    int distance[MAX_NODES];

    /*
     * visited[] keeps track of nodes whose minimum
     * distance has already been finalized.
     */
    int visited[MAX_NODES];

    /*
     * previous[] stores the previous node used to
     * reach each node through the shortest path.
     */
    int previous[MAX_NODES];

    /*
     * Initial setup:
     *
     * Initially, all nodes are considered unreachable.
     * No node has been visited.
     * No previous node is assigned.
     */
    for (int i = 0; i < n; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = 0;
        previous[i] = -1;
    }

    /*
     * The distance from the source node to itself
     * is always zero.
     */
    distance[source] = 0;

    /*
     * Main Dijkstra process.
     *
     * In every iteration, select the unvisited node
     * having the smallest known distance.
     */
    for (int count = 0; count < n - 1; count++)
    {
        int current = findMinDistance(distance, visited, n);

        /*
         * If no unvisited reachable node is found,
         * the remaining nodes cannot be reached.
         */
        if (current == -1)
        {
            break;
        }

        /* Mark the selected node as visited */
        visited[current] = 1;

        /*
         * Check all possible neighbouring nodes
         * connected to the current node.
         */
        for (int next = 0; next < n; next++)
        {
            /*
             * A value greater than zero indicates
             * that an edge exists between the nodes.
             *
             * The next node must not already be visited.
             *
             * distance[current] must also be valid.
             */
            if (graph[current][next] > 0 &&
                visited[next] == 0 &&
                distance[current] != INT_MAX)
            {
                int newDistance;

                /*
                 * Calculate the cost of reaching the
                 * neighbouring node through the current node.
                 */
                newDistance =
                    distance[current] + graph[current][next];

                /*
                 * If this route is cheaper than the
                 * previously known route, update it.
                 */
                if (newDistance < distance[next])
                {
                    distance[next] = newDistance;

                    /*
                     * Store the current node so that
                     * the complete shortest path can
                     * be reconstructed later.
                     */
                    previous[next] = current;
                }
            }
        }
    }

    /*
     * Display the final routing table.
     *
     * It shows the minimum cost from the source
     * node to every destination node.
     */
    printf("\nRouting Table from Node %d\n", source);
    printf("----------------------------------\n");
    printf("Destination\tCost\n");
    printf("----------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        /*
         * INT_MAX means that the destination node
         * cannot be reached from the source.
         */
        if (distance[i] == INT_MAX)
        {
            printf("%d\t\tINF\n", i);
        }
        else
        {
            printf("%d\t\t%d\n", i, distance[i]);
        }
    }

    /*
     * Display the shortest route from the source
     * to every reachable destination.
     */
    printf("\nBest Routes from Node %d\n", source);
    printf("----------------------------------\n");

    for (int destination = 0; destination < n; destination++)
    {
        /*
         * The route from the source to itself
         * does not need to be displayed.
         */
        if (destination == source)
        {
            continue;
        }

        /*
         * If the destination has an infinite distance,
         * there is no available route.
         */
        if (distance[destination] == INT_MAX)
        {
            printf("To Node %d: No route available\n", destination);
            continue;
        }

        /* Display the destination node */
        printf("To Node %d: ", destination);

        /*
         * Print the complete shortest path using
         * the previous[] array.
         */
        printPath(previous, destination);

        /* Display the total cost of the selected route */
        printf(" | Cost = %d\n", distance[destination]);
    }
}