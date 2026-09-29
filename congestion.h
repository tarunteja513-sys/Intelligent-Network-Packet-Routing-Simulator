#ifndef CONGESTION_H
#define CONGESTION_H
#define MAX_ROUTERS 20
#define QUEUE_SIZE 20
typedef struct
{
    int packetId;
    int source;
    int destination;
} Packet;
typedef struct
{
    Packet packets[QUEUE_SIZE];
    int front;
    int rear;
    int count;
} PacketQueue;

typedef struct
{
    int routerId;
    int capacity;
    int currentPackets;
    int packetsReceived;
    int packetsSent;
    int packetsDropped;
    int congestion;
    PacketQueue queue;
} Router;
void initializeQueue(PacketQueue *queue);
int isQueueEmpty(PacketQueue *queue);
int isQueueFull(PacketQueue *queue);
void enqueue(PacketQueue *queue, Packet packet);
Packet dequeue(PacketQueue *queue);
void initializeRouters(Router routers[], int n);
void addPacket(Router routers[], int router, Packet packet);
void sendPacket(Router routers[], int router);
void dropPacket(Router routers[], int router);
void calculateCongestion(Router routers[], int n);
int findMostCongested(Router routers[], int n);
void displayQueue(PacketQueue *queue);
void displayRouters(Router routers[], int n);
void displayStatistics(Router routers[], int n);
#endif
