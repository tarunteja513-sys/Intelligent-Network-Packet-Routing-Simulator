#include <stdio.h>

#define MAX_NODES 20

/*
 * Function declaration for Dijkstra's algorithm.
 *
 * The function receives:
 * graph  - adjacency matrix representing the network
 * n      - total number of nodes
 * source - starting node for routing
 */
void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int source);

int main()
{
    /*
     * Create an adjacency matrix for the network.
     *
     * MAX_NODES defines the maximum number of nodes
     * supported by the simulator.
     *
     * Initializing with {0} means there are no
     * connections between nodes initially.
     */
    int graph[MAX_NODES][MAX_NODES] = {0};

    /*
     * Number of routers currently used
     * in this test network.
     */
    int n = 4;

    /*
     * Network connections
     *
     * The network contains four routers:
     *
     *       5
     *  0 ------- 1
     *  |         |
     *  2         3
     *  |         |
     *  2 ------- 3
     *       4
     *
     * The numbers on the connections represent
     * the cost/weight of each network link.
     */

    /*
     * Connection between Router 0 and Router 1
     * with a link cost of 5.
     *
     * Both directions are assigned because this
     * network is represented as an undirected graph.
     */
    graph[0][1] = 5;
    graph[1][0] = 5;

    /*
     * Connection between Router 0 and Router 2
     * with a link cost of 2.
     */
    graph[0][2] = 2;
    graph[2][0] = 2;

    /*
     * Connection between Router 1 and Router 3
     * with a link cost of 3.
     */
    graph[1][3] = 3;
    graph[3][1] = 3;

    /*
     * Connection between Router 2 and Router 3
     * with a link cost of 4.
     */
    graph[2][3] = 4;
    graph[3][2] = 4;

    /*
     * Display the title of the project.
     */
    printf("Intelligent Network Packet Routing Simulator\n");
    printf("================================================\n");

    /*
     * Display the router/node information
     * used in the simulation.
     */
    printf("\nNodes:\n");
    printf("0 = Router 0\n");
    printf("1 = Router 1\n");
    printf("2 = Router 2\n");
    printf("3 = Router 3\n");

    /*
     * Start Dijkstra's algorithm.
     *
     * The source node is Router 0.
     *
     * The algorithm will calculate the minimum-cost
     * route from Router 0 to all other routers.
     */
    dijkstra(graph, n, 0);

    /*
     * Return 0 indicates that the program
     * executed successfully.
     */
    return 0;
}