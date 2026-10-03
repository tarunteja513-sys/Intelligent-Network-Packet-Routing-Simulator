#include <stdio.h>

#define MAX_NODES 20

void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int source);

int main(void)
{
    int network[MAX_NODES][MAX_NODES] = {0};
    int nodes = 5;
    int i;

    network[0][1] = 5;
    network[1][0] = 5;

    network[0][2] = 2;
    network[2][0] = 2;

    network[1][3] = 3;
    network[3][1] = 3;

    network[2][3] = 4;
    network[3][2] = 4;

    printf("\n============================================\n");
    printf("   INTELLIGENT NETWORK PACKET ROUTING\n");
    printf("            ROUTING TEST\n");
    printf("============================================\n");

    printf("\nAvailable Routers:\n");

    for (i = 0; i < nodes; i++)
    {
        printf("Router %d\n", i);
    }

    printf("\n--------------------------------------------\n");
    printf("Calculating routes from Router 0...\n");
    printf("--------------------------------------------\n");

    dijkstra(network, nodes, 0);

    return 0;
}