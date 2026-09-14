#include <stdio.h>
#include <limits.h>

#define MAX_NODES 20

// Find the unvisited node with the smallest distance
int findMinDistance(int distance[], int visited[], int n)
{
    int min = INT_MAX;
    int minIndex = -1;

    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && distance[i] < min)
        {
            min = distance[i];
            minIndex = i;
        }
    }

    return minIndex;
}

// Dijkstra's shortest path algorithm
void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int source)
{
    int distance[MAX_NODES];
    int visited[MAX_NODES];

    // Initialize distances and visited array
    for (int i = 0; i < n; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    // Distance from source to itself is 0
    distance[source] = 0;

    // Find shortest paths
    for (int count = 0; count < n - 1; count++)
    {
        int current = findMinDistance(distance, visited, n);

        if (current == -1)
        {
            break;
        }

        visited[current] = 1;

        // Update distances of neighbouring nodes
        for (int next = 0; next < n; next++)
        {
            if (!visited[next] &&
                graph[current][next] > 0 &&
                distance[current] != INT_MAX &&
                distance[current] + graph[current][next] < distance[next])
            {
                distance[next] =
                    distance[current] + graph[current][next];
            }
        }
    }

    // Display routing table
    printf("\nRouting Table from Node %d\n", source);
    printf("-----------------------------\n");
    printf("Destination\tCost\n");
    printf("-----------------------------\n");

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
}