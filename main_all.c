#include <stdio.h>
#include "graph.h"
#include "packet.h"
#include "congestion.h"

#define MAX_NODES 20
#define MAX_ROUTER_COUNT 20

void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int source);

void prepareRoutingGraph(int route[MAX_NODES][MAX_NODES])
{
    int row;
    int col;

    for (row = 0; row < MAX_NODES; row++)
    {
        for (col = 0; col < MAX_NODES; col++)
        {
            if (row >= routerCount || col >= routerCount)
            {
                route[row][col] = 0;
            }
            else if (graph[row][col] == INF)
            {
                route[row][col] = 0;
            }
            else
            {
                route[row][col] = graph[row][col];
            }
        }
    }
}

void graphMenu(void)
{
    int option;

    do
    {
        printf("\n====================================\n");
        printf("         NETWORK TOPOLOGY\n");
        printf("====================================\n");
        printf("1. Add Router\n");
        printf("2. Add Communication Link\n");
        printf("3. Display Routers\n");
        printf("4. Display Network\n");
        printf("5. Display Adjacency Matrix\n");
        printf("6. Remove Router\n");
        printf("7. Change Link Cost\n");
        printf("8. Remove Link\n");
        printf("9. Return\n");
        printf("====================================\n");

        printf("Select option: ");
        scanf("%d", &option);

        switch (option)
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
                break;

            default:
                printf("\nInvalid option.\n");
        }

    } while (option != 9);
}

void packetMenu(PacketQueue *queue)
{
    int option;
    Packet newPacket;

    do
    {
        printf("\n====================================\n");
        printf("          PACKET MANAGEMENT\n");
        printf("====================================\n");
        printf("1. Create and Add Packet\n");
        printf("2. Display Packets\n");
        printf("3. Transmit Packet\n");
        printf("4. Return\n");
        printf("====================================\n");

        printf("Select option: ");
        scanf("%d", &option);

        switch (option)
        {
            case 1:
                createPacket(&newPacket);
                enqueuePacket(queue, newPacket);
                break;

            case 2:
                displayPackets(queue);
                break;

            case 3:
                dequeuePacket(queue);
                break;

            case 4:
                break;

            default:
                printf("\nInvalid option.\n");
        }

    } while (option != 4);
}

void routingMenu(void)
{
    int route[MAX_NODES][MAX_NODES];
    int source;

    if (routerCount <= 0)
    {
        printf("\nNo routers have been added yet.\n");
        return;
    }

    prepareRoutingGraph(route);

    displayRouters();

    printf("\nEnter source router ID: ");
    scanf("%d", &source);

    if (source < 0 || source >= routerCount)
    {
        printf("Invalid router ID.\n");
        return;
    }

    dijkstra(route, routerCount, source);
}

void congestionMenu(void)
{
    CongestionRouter routerData[MAX_ROUTER_COUNT];
    CongestionPacket packet;
    int option;
    int routerId;
    int routerTotal = routerCount;

    if (routerTotal <= 0)
    {
        printf("\nNo routers have been added yet.\n");
        return;
    }

    if (routerTotal > MAX_ROUTER_COUNT)
        routerTotal = MAX_ROUTER_COUNT;

    initializeRouters(routerData, routerTotal);

    do
    {
        printf("\n====================================\n");
        printf("        CONGESTION MANAGEMENT\n");
        printf("====================================\n");
        printf("1. Add Packet to Router\n");
        printf("2. Send Packet\n");
        printf("3. Drop Packet\n");
        printf("4. Display Router Information\n");
        printf("5. Display Queue\n");
        printf("6. Display Traffic Statistics\n");
        printf("7. Find Most Congested Router\n");
        printf("8. Return\n");
        printf("====================================\n");

        printf("Select option: ");
        scanf("%d", &option);

        switch (option)
        {
            case 1:
                printf("Enter router number: ");
                scanf("%d", &routerId);

                printf("Enter packet ID: ");
                scanf("%d", &packet.packetId);

                printf("Enter source router: ");
                scanf("%d", &packet.source);

                printf("Enter destination router: ");
                scanf("%d", &packet.destination);

                addPacket(routerData, routerId, packet);
                break;

            case 2:
                printf("Enter router number: ");
                scanf("%d", &routerId);

                sendPacket(routerData, routerId);
                break;

            case 3:
                printf("Enter router number: ");
                scanf("%d", &routerId);

                dropPacket(routerData, routerId);
                break;

            case 4:
                displayCongestionRouters(routerData, routerTotal);
                break;

            case 5:
                printf("Enter router number: ");
                scanf("%d", &routerId);

                if (routerId >= 0 && routerId < routerTotal)
                {
                    displayCongestionQueue(
                        &routerData[routerId].queue
                    );
                }
                else
                {
                    printf("Invalid router number.\n");
                }
                break;

            case 6:
                displayStatistics(routerData, routerTotal);
                break;

            case 7:
                calculateCongestion(routerData, routerTotal);

                routerId = findMostCongested(
                    routerData,
                    routerTotal
                );

                if (routerId >= 0)
                {
                    printf("\nMost Congested Router: %d\n",
                           routerId);
                    printf("Congestion: %d%%\n",
                           routerData[routerId].congestion);
                }
                break;

            case 8:
                break;

            default:
                printf("\nInvalid option.\n");
        }

    } while (option != 8);
}

int main(void)
{
    PacketQueue packetQueue;
    int option;

    initializeGraph();
    initializeQueue(&packetQueue);

    printf("\n============================================\n");
    printf("   INTELLIGENT NETWORK PACKET ROUTING SYSTEM\n");
    printf("============================================\n");

    do
    {
        printf("\n============================================\n");
        printf("                MAIN MENU\n");
        printf("============================================\n");
        printf("1. Network Topology Management\n");
        printf("2. Packet Management\n");
        printf("3. Shortest Path Routing\n");
        printf("4. Congestion Management\n");
        printf("5. Exit\n");
        printf("============================================\n");

        printf("Select option: ");
        scanf("%d", &option);

        switch (option)
        {
            case 1:
                graphMenu();
                break;

            case 2:
                packetMenu(&packetQueue);
                break;

            case 3:
                routingMenu();
                break;

            case 4:
                congestionMenu();
                break;

            case 5:
                printf("\nProgram terminated.\n");
                break;

            default:
                printf("\nInvalid option. Try again.\n");
        }

    } while (option != 5);

    return 0;
}