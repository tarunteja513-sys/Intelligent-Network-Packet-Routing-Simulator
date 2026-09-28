#include <stdio.h>
#include <string.h>
#include "graph.h"

Router routers[MAX_ROUTERS];
int graph[MAX_ROUTERS][MAX_ROUTERS];
int routerCount = 0;

/* Initialize the adjacency matrix */
void initializeGraph()
{
    for (int i = 0; i < MAX_ROUTERS; i++)
    {
        for (int j = 0; j < MAX_ROUTERS; j++)
        {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = INF;
        }
    }
}

/* Add a router */
void addRouter()
{
    int count;

    if (routerCount >= MAX_ROUTERS)
    {
        printf("\nMaximum number of routers reached.\n");
        return;
    }

    printf("\nHow many routers do you want to add? ");
    scanf("%d", &count);

    if (count <= 0)
    {
        printf("Invalid number of routers.\n");
        return;
    }

    if (routerCount + count > MAX_ROUTERS)
    {
        printf("\nYou can add only %d more router(s).\n",
               MAX_ROUTERS - routerCount);
        return;
    }

    for (int i = 0; i < count; i++)
    {
        routers[routerCount].id = routerCount;

        printf("\nEnter name for Router %d: ",
               routerCount);

        scanf("%19s", routers[routerCount].name);

        printf("Router %s added successfully. ID = %d\n",
               routers[routerCount].name,
               routers[routerCount].id);

        routerCount++;
    }

    printf("\n%d router(s) added successfully.\n", count);
}
/* Display all routers */
void displayRouters()
{
    if (routerCount == 0)
    {
        printf("\nNo routers available.\n");
        return;
    }

    printf("\n----- Routers -----\n");

    for (int i = 0; i < routerCount; i++)
    {
        printf("ID: %d\tName: %s\n",
               routers[i].id,
               routers[i].name);
    }
}

/* Add a communication link */
void addLink()
{
    int count;
    int source, destination, cost;

    if (routerCount < 2)
    {
        printf("\nAt least two routers are required.\n");
        return;
    }

    printf("\nHow many links do you want to add? ");
    scanf("%d", &count);

    if (count <= 0)
    {
        printf("Invalid number of links.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        printf("\n========== LINK %d ==========\n", i + 1);

        displayRouters();

        printf("\nEnter source router ID: ");
        scanf("%d", &source);

        printf("Enter destination router ID: ");
        scanf("%d", &destination);

        if (source < 0 || source >= routerCount ||
            destination < 0 || destination >= routerCount)
        {
            printf("Invalid router ID.\n");
            printf("Please enter this link again.\n");
            i--;
            continue;
        }

        if (source == destination)
        {
            printf("A router cannot be connected to itself.\n");
            printf("Please enter this link again.\n");
            i--;
            continue;
        }

        if (graph[source][destination] != INF)
        {
            printf("A link already exists between %s and %s.\n",
                   routers[source].name,
                   routers[destination].name);

            printf("Please enter a different link.\n");
            i--;
            continue;
        }

        printf("Enter link cost: ");
        scanf("%d", &cost);

        if (cost <= 0)
        {
            printf("Link cost must be positive.\n");
            printf("Please enter this link again.\n");
            i--;
            continue;
        }

        graph[source][destination] = cost;
        graph[destination][source] = cost;

        printf("\nLink %d added successfully.\n", i + 1);
        printf("%s <---- %d ----> %s\n",
               routers[source].name,
               cost,
               routers[destination].name);
    }

    printf("\n%d link(s) added successfully.\n", count);
}
/* Remove a router */
void removeRouter()
{
    int count;
    int id;

    if (routerCount == 0)
    {
        printf("\nNo routers available.\n");
        return;
    }

    printf("\nHow many routers do you want to remove? ");
    scanf("%d", &count);

    if (count <= 0)
    {
        printf("Invalid number of routers.\n");
        return;
    }

    if (count > routerCount)
    {
        printf("\nYou can remove only %d router(s).\n", routerCount);
        return;
    }

    for (int k = 0; k < count; k++)
    {
        printf("\n========== REMOVE ROUTER %d ==========\n", k + 1);

        displayRouters();

        printf("\nEnter router ID to remove: ");
        scanf("%d", &id);

        if (id < 0 || id >= routerCount)
        {
            printf("Invalid router ID.\n");
            printf("Please enter the router again.\n");
            k--;
            continue;
        }

        printf("\nRemoving router: %s\n", routers[id].name);

        /*
         * Shift router information left.
         */
        for (int i = id; i < routerCount - 1; i++)
        {
            routers[i] = routers[i + 1];
            routers[i].id = i;
        }

        /*
         * Shift rows of adjacency matrix.
         */
        for (int i = id; i < routerCount - 1; i++)
        {
            for (int j = 0; j < routerCount; j++)
            {
                graph[i][j] = graph[i + 1][j];
            }
        }

        /*
         * Shift columns of adjacency matrix.
         */
        for (int i = 0; i < routerCount - 1; i++)
        {
            for (int j = id; j < routerCount - 1; j++)
            {
                graph[i][j] = graph[i][j + 1];
            }
        }

        routerCount--;

        /*
         * Reset unused row and column.
         */
        for (int i = 0; i < MAX_ROUTERS; i++)
        {
            graph[routerCount][i] = INF;
            graph[i][routerCount] = INF;
        }

        graph[routerCount][routerCount] = 0;

        printf("Router removed successfully.\n");
    }

    printf("\n%d router(s) removed successfully.\n", count);
}
/* Change the cost of an existing link */
void changeLink()
{
    int source, destination, newCost;

    if (routerCount < 2)
    {
        printf("\nAt least two routers are required.\n");
        return;
    }

    displayRouters();

    printf("\nEnter source router ID: ");
    scanf("%d", &source);

    printf("Enter destination router ID: ");
    scanf("%d", &destination);

    if (source < 0 || source >= routerCount ||
        destination < 0 || destination >= routerCount)
    {
        printf("Invalid router ID.\n");
        return;
    }

    if (source == destination)
    {
        printf("A router cannot be connected to itself.\n");
        return;
    }

    if (graph[source][destination] == INF)
    {
        printf("No link exists between these routers.\n");
        return;
    }

    printf("Current link cost: %d\n",
           graph[source][destination]);

    printf("Enter new link cost: ");
    scanf("%d", &newCost);

    if (newCost <= 0)
    {
        printf("Link cost must be positive.\n");
        return;
    }

    graph[source][destination] = newCost;
    graph[destination][source] = newCost;

    printf("\nLink cost changed successfully.\n");
    printf("%s <---- %d ----> %s\n",
           routers[source].name,
           newCost,
           routers[destination].name);
}

/* Remove a communication link */
void removeLink()
{
    int count;
    int source, destination;

    if (routerCount < 2)
    {
        printf("\nAt least two routers are required.\n");
        return;
    }

    printf("\nHow many links do you want to remove? ");
    scanf("%d", &count);

    if (count <= 0)
    {
        printf("Invalid number of links.\n");
        return;
    }

    for (int k = 0; k < count; k++)
    {
        printf("\n========== REMOVE LINK %d ==========\n", k + 1);

        displayRouters();

        printf("\nEnter source router ID: ");
        scanf("%d", &source);

        printf("Enter destination router ID: ");
        scanf("%d", &destination);

        if (source < 0 || source >= routerCount ||
            destination < 0 || destination >= routerCount)
        {
            printf("Invalid router ID.\n");
            printf("Please enter the link again.\n");
            k--;
            continue;
        }

        if (source == destination)
        {
            printf("A router cannot be connected to itself.\n");
            printf("Please enter the link again.\n");
            k--;
            continue;
        }

        if (graph[source][destination] == INF)
        {
            printf("\nNo link exists between %s and %s.\n",
                   routers[source].name,
                   routers[destination].name);

            printf("Please enter a different link.\n");
            k--;
            continue;
        }

        printf("\nRemoving link:\n");
        printf("%s <---- %d ----> %s\n",
               routers[source].name,
               graph[source][destination],
               routers[destination].name);

        graph[source][destination] = INF;
        graph[destination][source] = INF;

        printf("Link removed successfully.\n");
    }

    printf("\n%d link(s) removed successfully.\n", count);
}
/* Display network connections */
void displayNetwork()
{
    int found = 0;

    printf("\n========== NETWORK TOPOLOGY ==========\n");

    if (routerCount == 0)
    {
        printf("No routers available.\n");
        return;
    }

    for (int i = 0; i < routerCount; i++)
    {
        printf("%s -> ", routers[i].name);

        for (int j = 0; j < routerCount; j++)
        {
            if (graph[i][j] != INF &&
                graph[i][j] != 0)
            {
                printf("%s(%d) ",
                       routers[j].name,
                       graph[i][j]);

                found = 1;
            }
        }

        printf("\n");
    }

    if (!found)
        printf("No communication links available.\n");
}

/* Display adjacency matrix */
void displayMatrix()
{
    printf("\n========== ADJACENCY MATRIX ==========\n\n");

    if (routerCount == 0)
    {
        printf("No routers available.\n");
        return;
    }

    printf("%8s", "");

    for (int i = 0; i < routerCount; i++)
    {
        printf("%8s", routers[i].name);
    }

    printf("\n");

    for (int i = 0; i < routerCount; i++)
    {
        printf("%8s", routers[i].name);

        for (int j = 0; j < routerCount; j++)
        {
            if (graph[i][j] == INF)
                printf("%8s", "INF");
            else
                printf("%8d", graph[i][j]);
        }

        printf("\n");
    }
}