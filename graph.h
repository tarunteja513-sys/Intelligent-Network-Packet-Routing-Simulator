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

void initializeGraph(void);
void addRouter(void);
void addLink(void);
void removeRouter(void);
void changeLink(void);
void removeLink(void);

void displayRouters(void);
void displayNetwork(void);
void displayMatrix(void);

#endif