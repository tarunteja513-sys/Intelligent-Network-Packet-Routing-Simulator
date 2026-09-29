#include <stdio.h>
#include "graph.h"
#include "packet.h"
#include "congestion.h"

#define MAX_NODES 20
#define MAX_ROUTERS 20

/* Member 3 */
void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int source);

/* Convert Member 1 graph for Member 3 */
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

/* ================= MEMBER 1 ================= */

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

/* ================= MEMBER 2 ================= */

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

/* ================= MEMBER 3 ================= */

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

/* ================= MEMBER 4 ================= */

void congestionMenu()
{
    CongestionRouter routers[MAX_ROUTERS];
    int choice;
    int router;
    int n;
    CongestionPacket packet;

    n = routerCount;

    if (n == 0)
    {
        printf("\nNo routers are available.\n");
        printf("Please add routers first.\n");
        return;
    }

    if (n > MAX_ROUTERS)
        n = MAX_ROUTERS;

    initializeRouters(routers, n);

    while (1)
    {
        printf("\n========== CONGESTION MENU ==========\n");
        printf("1. Add Packet to Router\n");
        printf("2. Send Packet\n");
        printf("3. Drop Packet\n");
        printf("4. Display Router Information\n");
        printf("5. Display Queue\n");
        printf("6. Display Traffic Statistics\n");
        printf("7. Find Most Congested Router\n");
        printf("8. Back to Main Menu\n");
        printf("=====================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter router number: ");
                scanf("%d", &router);

                printf("Enter packet ID: ");
                scanf("%d", &packet.packetId);

                printf("Enter source router: ");
                scanf("%d", &packet.source);

                printf("Enter destination router: ");
                scanf("%d", &packet.destination);

                addPacket(routers, router, packet);
                break;

            case 2:
                printf("Enter router number: ");
                scanf("%d", &router);

                sendPacket(routers, router);
                break;

            case 3:
                printf("Enter router number: ");
                scanf("%d", &router);

                dropPacket(routers, router);
                break;

            case 4:
                displayCongestionRouters(routers, n);
                break;

            case 5:
                printf("Enter router number: ");
                scanf("%d", &router);

                if (router >= 0 && router < n)
                {
                    displayCongestionQueue(
                        &routers[router].queue
                    );
                }
                else
                {
                    printf("Invalid router.\n");
                }

                break;

            case 6:
                displayStatistics(routers, n);
                break;

            case 7:
                calculateCongestion(routers, n);

                router = findMostCongested(routers, n);

                printf("\nMost Congested Router: %d\n", router);
                printf("Congestion: %d%%\n",
                       routers[router].congestion);
                break;

            case 8:
                return;

            default:
                printf("Invalid choice.\n");
        }
    }
}

/* ================= MAIN ================= */

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
        printf("\n\n=============== MAIN MENU ===============\n");
        printf("1. Network Topology Management\n");
        printf("2. Packet Management\n");
        printf("3. Shortest Path Routing\n");
        printf("4. Congestion Management\n");
        printf("5. Exit\n");
        printf("==========================================\n");

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
                congestionMenu();
                break;

            case 5:
                printf("\nProgram terminated.\n");
                return 0;

            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }

    return 0;
}