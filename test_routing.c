#include <stdio.h>

#define MAX_NODES 20

void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int source);

int main()
{
    int graph[MAX_NODES][MAX_NODES] = {0};
    int n = 4;

    /*
     * Network connections
     *
     * 0 ----5---- 1
     * |           |
     * 2           3
     * |           |
     * 2 ----4---- 3
     */

    graph[0][1] = 5;
    graph[1][0] = 5;

    graph[0][2] = 2;
    graph[2][0] = 2;

    graph[1][3] = 3;
    graph[3][1] = 3;

    graph[2][3] = 4;
    graph[3][2] = 4;

    printf("Intelligent Network Packet Routing Simulator\n");
    printf("================================================\n");

    printf("\nNodes:\n");
    printf("0 = Router 0\n");
    printf("1 = Router 1\n");
    printf("2 = Router 2\n");
    printf("3 = Router 3\n");

    dijkstra(graph, n, 0);

    return 0;
}