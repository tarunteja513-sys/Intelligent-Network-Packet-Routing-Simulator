#include <stdio.h>
#include "graph.h"
#include "packet.h"

#define MAX_NODES 20

/* Member 3 Dijkstra function */
void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int source);

/* Convert Member 1 graph into the format expected by Member 3 */
void prepareRoutingGraph(int routingGraph[MAX_NODES][MAX_NODES])
{
    int i;
    int j;

    for (i = 0; i < MAX_NODES; i++)
    {
        for (j = 0; j < MAX_NODES; j++)
        {
            if (i < routerCount && j < routerCount)
            {
                if (graph[i][j] == INF)
                    routingGraph[i][j] = 0;
                else
                    routingGraph[i][j] = graph[i][j];
            }
            else
            {
                routingGraph[i][j] = 0;
            }
        }
    }
}

/* Member 1 menu */
void graphMenu()
{
    int choice;

    while (1)
    {
        printf("\n========== NETWORK MENU ==========\n");
        printf("1. Add Router\n");
        printf("2. Add Communication Link\n");
        printf("3. Display Routers\n");
        printf("4. Display Network\n");
        printf("5. Display Adjacency Matrix\n");
        printf("6. Remove Router\n");
        printf("7. Change Link Cost\n");
        printf("8. Remove Link\n");
        printf("9. Back to Main Menu\n");
        printf("==================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addRouter();
                break;

            case 2:
                addLink();
                break;

            case 3:
                displayRouters();
                break;

            case 4:
                displayNetwork();
                break;

            case 5:
                displayMatrix();
                break;

            case 6:
                removeRouter();
                break;

            case 7:
                changeLink();
                break;

            case 8:
                removeLink();
                break;

            case 9:
                return;

            default:
                printf("Invalid choice.\n");
        }
    }
}

/* Member 2 menu */
void packetMenu(PacketQueue *queue)
{
    int choice;
    Packet packet;

    while (1)
    {
        printf("\n========== PACKET MENU ==========\n");
        printf("1. Create and Add Packet\n");
        printf("2. Display Packets\n");
        printf("3. Transmit Packet\n");
        printf("4. Back to Main Menu\n");
        printf("=================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                createPacket(&packet);
                enqueuePacket(queue, packet);
                break;

            case 2:
                displayPackets(queue);
                break;

            case 3:
                dequeuePacket(queue);
                break;

            case 4:
                return;

            default:
                printf("Invalid choice.\n");
        }
    }
}

/* Member 3 menu */
void routingMenu()
{
    int routingGraph[MAX_NODES][MAX_NODES];
    int source;

    if (routerCount == 0)
    {
        printf("\nNo routers are available.\n");
        printf("Please add routers first.\n");
        return;
    }

    prepareRoutingGraph(routingGraph);

    displayRouters();

    printf("\nEnter source router ID: ");
    scanf("%d", &source);

    if (source < 0 || source >= routerCount)
    {
        printf("Invalid router ID.\n");
        return;
    }

    dijkstra(routingGraph, routerCount, source);
}

int main()
{
    int choice;
    PacketQueue queue;

    initializeGraph();
    initializeQueue(&queue);

    printf("============================================\n");
    printf(" INTELLIGENT NETWORK PACKET ROUTING SYSTEM\n");
    printf("============================================\n");

    while (1)
    {
        printf("\n\n============= MAIN MENU =============\n");
        printf("1. Network Topology Management\n");
        printf("2. Packet Management\n");
        printf("3. Shortest Path Routing\n");
        printf("4. Exit\n");
        printf("=====================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                graphMenu();
                break;

            case 2:
                packetMenu(&queue);
                break;

            case 3:
                routingMenu();
                break;

            case 4:
                printf("\nProgram terminated.\n");
                return 0;

            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }

    return 0;
}