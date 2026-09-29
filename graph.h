#ifndef GRAPH_H
#define GRAPH_H

#define MAX_ROUTERS 20
#define INF 9999

typedef struct
{
    int id;
    char name[20];
} Router;

extern Router routers[MAX_ROUTERS];
extern int graph[MAX_ROUTERS][MAX_ROUTERS];
extern int routerCount;

void initializeGraph();

void addRouter();
void addLink();

void removeRouter();
void changeLink();
void removeLink();

void displayRouters();
void displayNetwork();
void displayMatrix();

#endif