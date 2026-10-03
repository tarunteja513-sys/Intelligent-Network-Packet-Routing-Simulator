#include <stdio.h>
#include <string.h>
#include "graph.h"

Router routers[MAX_ROUTERS];
int graph[MAX_ROUTERS][MAX_ROUTERS];
int routerCount = 0;


/* Set up an empty graph */
void initializeGraph(void)
{
    int row, col;

    for (row = 0; row < MAX_ROUTERS; row++)
    {
        for (col = 0; col < MAX_ROUTERS; col++)
        {
            graph[row][col] = (row == col) ? 0 : INF;
        }
    }

    routerCount = 0;
}


/* Add one or more routers */
void addRouter(void)
{
    int number;
    int index, existing;
    int duplicate;

    if (routerCount >= MAX_ROUTERS)
    {
        printf("\nMaximum number of routers reached.\n");
        return;
    }

    printf("\nNumber of routers to add: ");
    scanf("%d", &number);

    if (number <= 0 || routerCount + number > MAX_ROUTERS)
    {
        printf("\nInvalid number of routers.\n");

        if (number > MAX_ROUTERS - routerCount)
            printf("Only %d router(s) can be added.\n",
                   MAX_ROUTERS - routerCount);

        return;
    }

    for (index = 0; index < number; index++)
    {
        do
        {
            duplicate = 0;

            printf("Enter name for router %d: ", routerCount);
            scanf("%19s", routers[routerCount].name);

            for (existing = 0; existing < routerCount; existing++)
            {
                if (strcmp(routers[existing].name,
                           routers[routerCount].name) == 0)
                {
                    duplicate = 1;
                    printf("Name already exists. Enter another name.\n");
                    break;
                }
            }

        } while (duplicate);

        routers[routerCount].id = routerCount;

        printf("Router %s added with ID %d.\n",
               routers[routerCount].name,
               routers[routerCount].id);

        routerCount++;
    }

    printf("\n%d router(s) added successfully.\n", number);
}


/* Show the routers currently present */
void displayRouters(void)
{
    int i;

    if (routerCount == 0)
    {
        printf("\nNo routers available.\n");
        return;
    }

    printf("\n------------- ROUTERS -------------\n");

    for (i = 0; i < routerCount; i++)
    {
        printf("ID: %-3d Name: %s\n",
               routers[i].id,
               routers[i].name);
    }
}


/* Add communication links */
void addLink(void)
{
    int number;
    int source, destination, cost;
    int link;

    if (routerCount < 2)
    {
        printf("\nAt least two routers are required.\n");
        return;
    }

    printf("\nNumber of links to add: ");
    scanf("%d", &number);

    if (number <= 0)
    {
        printf("\nInvalid number of links.\n");
        return;
    }

    for (link = 0; link < number; link++)
    {
        printf("\n------------- LINK %d -------------\n", link + 1);

        displayRouters();

        printf("Source router ID: ");
        scanf("%d", &source);

        printf("Destination router ID: ");
        scanf("%d", &destination);

        if (source < 0 || source >= routerCount ||
            destination < 0 || destination >= routerCount)
        {
            printf("Invalid router ID. Try again.\n");
            link--;
            continue;
        }

        if (source == destination)
        {
            printf("A router cannot connect to itself.\n");
            link--;
            continue;
        }

        if (graph[source][destination] != INF)
        {
            printf("A link already exists between %s and %s.\n",
                   routers[source].name,
                   routers[destination].name);
            link--;
            continue;
        }

        printf("Enter link cost: ");
        scanf("%d", &cost);

        if (cost <= 0)
        {
            printf("Link cost must be positive.\n");
            link--;
            continue;
        }

        graph[source][destination] = cost;
        graph[destination][source] = cost;

        printf("Link created: %s <--- %d ---> %s\n",
               routers[source].name,
               cost,
               routers[destination].name);
    }

    printf("\n%d link(s) added successfully.\n", number);
}


/* Remove routers and update the matrix */
void removeRouter(void)
{
    int number;
    int id;
    int i, j, step;

    if (routerCount == 0)
    {
        printf("\nNo routers available.\n");
        return;
    }

    printf("\nNumber of routers to remove: ");
    scanf("%d", &number);

    if (number <= 0 || number > routerCount)
    {
        printf("\nInvalid number of routers.\n");
        return;
    }

    for (step = 0; step < number; step++)
    {
        displayRouters();

        printf("\nRouter ID to remove: ");
        scanf("%d", &id);

        if (id < 0 || id >= routerCount)
        {
            printf("Invalid router ID. Try again.\n");
            step--;
            continue;
        }

        printf("Removing router %s...\n", routers[id].name);

        /* Move router records */
        for (i = id; i < routerCount - 1; i++)
        {
            routers[i] = routers[i + 1];
            routers[i].id = i;
        }

        /* Move matrix rows */
        for (i = id; i < routerCount - 1; i++)
        {
            for (j = 0; j < routerCount; j++)
                graph[i][j] = graph[i + 1][j];
        }

        /* Move matrix columns */
        for (i = 0; i < routerCount - 1; i++)
        {
            for (j = id; j < routerCount - 1; j++)
                graph[i][j] = graph[i][j + 1];
        }

        routerCount--;

        /* Clear the unused row and column */
        for (i = 0; i < MAX_ROUTERS; i++)
        {
            graph[routerCount][i] = INF;
            graph[i][routerCount] = INF;
        }

        graph[routerCount][routerCount] = 0;

        printf("Router removed successfully.\n");
    }

    printf("\n%d router(s) removed successfully.\n", number);
}


/* Modify the cost of an existing link */
void changeLink(void)
{
    int source, destination;
    int cost;

    if (routerCount < 2)
    {
        printf("\nAt least two routers are required.\n");
        return;
    }

    displayRouters();

    printf("\nSource router ID: ");
    scanf("%d", &source);

    printf("Destination router ID: ");
    scanf("%d", &destination);

    if (source < 0 || source >= routerCount ||
        destination < 0 || destination >= routerCount)
    {
        printf("Invalid router ID.\n");
        return;
    }

    if (source == destination)
    {
        printf("A router cannot connect to itself.\n");
        return;
    }

    if (graph[source][destination] == INF)
    {
        printf("No link exists between these routers.\n");
        return;
    }

    printf("Current cost: %d\n", graph[source][destination]);

    printf("Enter new cost: ");
    scanf("%d", &cost);

    if (cost <= 0)
    {
        printf("Link cost must be positive.\n");
        return;
    }

    graph[source][destination] = cost;
    graph[destination][source] = cost;

    printf("Link cost updated successfully.\n");
}


/* Remove communication links */
void removeLink(void)
{
    int number;
    int source, destination;
    int step;

    if (routerCount < 2)
    {
        printf("\nAt least two routers are required.\n");
        return;
    }

    printf("\nNumber of links to remove: ");
    scanf("%d", &number);

    if (number <= 0)
    {
        printf("\nInvalid number of links.\n");
        return;
    }

    for (step = 0; step < number; step++)
    {
        displayRouters();

        printf("\nSource router ID: ");
        scanf("%d", &source);

        printf("Destination router ID: ");
        scanf("%d", &destination);

        if (source < 0 || source >= routerCount ||
            destination < 0 || destination >= routerCount)
        {
            printf("Invalid router ID. Try again.\n");
            step--;
            continue;
        }

        if (source == destination)
        {
            printf("A router cannot connect to itself.\n");
            step--;
            continue;
        }

        if (graph[source][destination] == INF)
        {
            printf("No link exists between these routers.\n");
            step--;
            continue;
        }

        printf("Removing %s <--- %d ---> %s\n",
               routers[source].name,
               graph[source][destination],
               routers[destination].name);

        graph[source][destination] = INF;
        graph[destination][source] = INF;

        printf("Link removed successfully.\n");
    }

    printf("\n%d link(s) removed successfully.\n", number);
}


/* Display the current network */
void displayNetwork(void)
{
    int i, j;
    int connectionFound = 0;

    printf("\n========== NETWORK TOPOLOGY ==========\n");

    if (routerCount == 0)
    {
        printf("No routers available.\n");
        return;
    }

    for (i = 0; i < routerCount; i++)
    {
        printf("%s -> ", routers[i].name);

        for (j = 0; j < routerCount; j++)
        {
            if (graph[i][j] != INF && graph[i][j] != 0)
            {
                printf("%s(%d) ",
                       routers[j].name,
                       graph[i][j]);

                connectionFound = 1;
            }
        }

        printf("\n");
    }

    if (!connectionFound)
        printf("No communication links available.\n");
}


/* Print the adjacency matrix */
void displayMatrix(void)
{
    int i, j;

    printf("\n========== ADJACENCY MATRIX ==========\n\n");

    if (routerCount == 0)
    {
        printf("No routers available.\n");
        return;
    }

    printf("%8s", "");

    for (i = 0; i < routerCount; i++)
        printf("%8s", routers[i].name);

    printf("\n");

    for (i = 0; i < routerCount; i++)
    {
        printf("%8s", routers[i].name);

        for (j = 0; j < routerCount; j++)
        {
            if (graph[i][j] == INF)
                printf("%8s", "INF");
            else
                printf("%8d", graph[i][j]);
        }

        printf("\n");
    }
}