#include <stdio.h>
#include <limits.h>

#define MAX_NODES 20

/*
 * Finds the unvisited node having the smallest
 * known distance from the source node.
 */
int findMinDistance(int distance[], int visited[], int n)
{
    int minDistance = INT_MAX;
    int minNode = -1;

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
 * Prints the shortest path from source
 * to the selected destination.
 */
void printPath(int previous[], int destination)
{
    int path[MAX_NODES];
    int count = 0;
    int node = destination;

    while (node != -1)
    {
        path[count] = node;
        count++;
        node = previous[node];
    }

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
 * Dijkstra's algorithm is used to find
 * minimum-cost routes from one source node.
 */
void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int source)
{
    int distance[MAX_NODES];
    int visited[MAX_NODES];
    int previous[MAX_NODES];

    /*
     * Initial setup
     */
    for (int i = 0; i < n; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = 0;
        previous[i] = -1;
    }

    /*
     * Distance from source to itself is zero.
     */
    distance[source] = 0;

    /*
     * Main Dijkstra process
     */
    for (int count = 0; count < n - 1; count++)
    {
        int current = findMinDistance(distance, visited, n);

        if (current == -1)
        {
            break;
        }

        visited[current] = 1;

        /*
         * Check all neighbouring nodes.
         */
        for (int next = 0; next < n; next++)
        {
            if (graph[current][next] > 0 &&
                visited[next] == 0 &&
                distance[current] != INT_MAX)
            {
                int newDistance;

                newDistance =
                    distance[current] + graph[current][next];

                if (newDistance < distance[next])
                {
                    distance[next] = newDistance;
                    previous[next] = current;
                }
            }
        }
    }

    /*
     * Display routing table.
     */
    printf("\nRouting Table from Node %d\n", source);
    printf("----------------------------------\n");
    printf("Destination\tCost\n");
    printf("----------------------------------\n");

    for (int i = 0; i < n; i++)
    {
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
     * Display shortest route to every node.
     */
    printf("\nBest Routes from Node %d\n", source);
    printf("----------------------------------\n");

    for (int destination = 0; destination < n; destination++)
    {
        if (destination == source)
        {
            continue;
        }

        if (distance[destination] == INT_MAX)
        {
            printf("To Node %d: No route available\n", destination);
            continue;
        }

        printf("To Node %d: ", destination);

        printPath(previous, destination);

        printf(" | Cost = %d\n", distance[destination]);
    }
}