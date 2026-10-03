#include <stdio.h>
#include <limits.h>

#define MAX_NODES 20

int findMinDistance(int distance[], int visited[], int n)
{
    int node = -1;
    int smallest = INT_MAX;
    int i;

    for (i = 0; i < n; i++)
    {
        if (!visited[i] && distance[i] < smallest)
        {
            smallest = distance[i];
            node = i;
        }
    }

    return node;
}

void printPath(int previous[], int destination)
{
    int route[MAX_NODES];
    int length = 0;
    int current = destination;
    int i;

    while (current != -1 && length < MAX_NODES)
    {
        route[length++] = current;
        current = previous[current];
    }

    for (i = length - 1; i >= 0; i--)
    {
        printf("%d", route[i]);

        if (i > 0)
            printf(" -> ");
    }
}

void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int source)
{
    int distance[MAX_NODES];
    int visited[MAX_NODES];
    int previous[MAX_NODES];

    int i;
    int step;

    for (i = 0; i < n; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = 0;
        previous[i] = -1;
    }

    distance[source] = 0;

    for (step = 0; step < n; step++)
    {
        int current = findMinDistance(distance, visited, n);

        if (current == -1)
            break;

        visited[current] = 1;

        for (i = 0; i < n; i++)
        {
            if (!visited[i] &&
                graph[current][i] > 0 &&
                distance[current] != INT_MAX)
            {
                int cost = distance[current] + graph[current][i];

                if (cost < distance[i])
                {
                    distance[i] = cost;
                    previous[i] = current;
                }
            }
        }
    }

    printf("\n========== ROUTING TABLE ==========\n");
    printf("Source Node: %d\n", source);
    printf("-----------------------------------\n");
    printf("Destination\tCost\n");
    printf("-----------------------------------\n");

    for (i = 0; i < n; i++)
    {
        if (distance[i] == INT_MAX)
            printf("%d\t\tINF\n", i);
        else
            printf("%d\t\t%d\n", i, distance[i]);
    }

    printf("\n========== SHORTEST ROUTES ==========\n");

    for (i = 0; i < n; i++)
    {
        if (i == source)
            continue;

        printf("To Node %d: ", i);

        if (distance[i] == INT_MAX)
        {
            printf("No route available\n");
        }
        else
        {
            printPath(previous, i);
            printf(" | Cost = %d\n", distance[i]);
        }
    }

    printf("-------------------------------------\n");
}