#ifndef CONGESTION_H
#define CONGESTION_H

#define MAX_ROUTERS 20
#define CONGESTION_QUEUE_SIZE 20

typedef struct
{
    int packetId;
    int source;
    int destination;
} CongestionPacket;

typedef struct
{
    CongestionPacket packets[CONGESTION_QUEUE_SIZE];
    int front;
    int rear;
    int count;
} CongestionQueue;

typedef struct
{
    int routerId;
    int capacity;
    int currentPackets;
    int packetsReceived;
    int packetsSent;
    int packetsDropped;
    int congestion;
    CongestionQueue queue;
} CongestionRouter;

void initializeCongestionQueue(CongestionQueue *queue);

int isCongestionQueueEmpty(CongestionQueue *queue);

int isCongestionQueueFull(CongestionQueue *queue);

void enqueueCongestion(CongestionQueue *queue,
                        CongestionPacket packet);

CongestionPacket dequeueCongestion(CongestionQueue *queue);

void initializeRouters(CongestionRouter routers[], int n);

void addPacket(CongestionRouter routers[],
               int router,
               CongestionPacket packet);

void sendPacket(CongestionRouter routers[], int router);

void dropPacket(CongestionRouter routers[], int router);

void calculateCongestion(CongestionRouter routers[], int n);

int findMostCongested(CongestionRouter routers[], int n);

void displayCongestionQueue(CongestionQueue *queue);

void displayCongestionRouters(CongestionRouter routers[], int n);

void displayStatistics(CongestionRouter routers[], int n);

#endif