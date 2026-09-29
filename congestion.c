#include <stdio.h>
#include "congestion.h"

void initializeCongestionQueue(CongestionQueue *queue)
{
    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
}

int isCongestionQueueEmpty(CongestionQueue *queue)
{
    if (queue->count == 0)
        return 1;

    return 0;
}

int isCongestionQueueFull(CongestionQueue *queue)
{
    if (queue->count == CONGESTION_QUEUE_SIZE)
        return 1;

    return 0;
}

void enqueueCongestion(CongestionQueue *queue,
                        CongestionPacket packet)
{
    if (isCongestionQueueFull(queue))
    {
        printf("Queue is full.\n");
        return;
    }

    queue->rear++;

    if (queue->rear == CONGESTION_QUEUE_SIZE)
        queue->rear = 0;

    queue->packets[queue->rear] = packet;
    queue->count++;
}

CongestionPacket dequeueCongestion(CongestionQueue *queue)
{
    CongestionPacket packet;

    packet.packetId = -1;
    packet.source = -1;
    packet.destination = -1;

    if (isCongestionQueueEmpty(queue))
    {
        printf("Queue is empty.\n");
        return packet;
    }

    packet = queue->packets[queue->front];

    queue->front++;

    if (queue->front == CONGESTION_QUEUE_SIZE)
        queue->front = 0;

    queue->count--;

    return packet;
}

void initializeRouters(CongestionRouter routers[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        routers[i].routerId = i;
        routers[i].capacity = 10;
        routers[i].currentPackets = 0;
        routers[i].packetsReceived = 0;
        routers[i].packetsSent = 0;
        routers[i].packetsDropped = 0;
        routers[i].congestion = 0;

        initializeCongestionQueue(&routers[i].queue);
    }
}

void addPacket(CongestionRouter routers[],
               int router,
               CongestionPacket packet)
{
    if (router < 0 || router >= MAX_ROUTERS)
    {
        printf("Invalid router.\n");
        return;
    }

    if (isCongestionQueueFull(&routers[router].queue))
    {
        routers[router].packetsDropped++;

        printf("Router %d queue is full.\n", router);
        printf("Packet %d dropped.\n", packet.packetId);

        return;
    }

    enqueueCongestion(&routers[router].queue, packet);

    routers[router].packetsReceived++;
    routers[router].currentPackets++;

    printf("Packet %d added to Router %d.\n",
           packet.packetId, router);
}

void sendPacket(CongestionRouter routers[], int router)
{
    CongestionPacket packet;

    if (router < 0 || router >= MAX_ROUTERS)
    {
        printf("Invalid router.\n");
        return;
    }

    if (isCongestionQueueEmpty(&routers[router].queue))
    {
        printf("No packets in Router %d.\n", router);
        return;
    }

    packet = dequeueCongestion(&routers[router].queue);

    routers[router].packetsSent++;

    if (routers[router].currentPackets > 0)
        routers[router].currentPackets--;

    printf("Packet %d sent from Router %d.\n",
           packet.packetId, router);
}

void dropPacket(CongestionRouter routers[], int router)
{
    CongestionPacket packet;

    if (router < 0 || router >= MAX_ROUTERS)
    {
        printf("Invalid router.\n");
        return;
    }

    if (isCongestionQueueEmpty(&routers[router].queue))
    {
        printf("No packet to drop.\n");
        return;
    }

    packet = dequeueCongestion(&routers[router].queue);

    routers[router].packetsDropped++;

    if (routers[router].currentPackets > 0)
        routers[router].currentPackets--;

    printf("Packet %d dropped from Router %d.\n",
           packet.packetId, router);
}

void calculateCongestion(CongestionRouter routers[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (routers[i].capacity == 0)
        {
            routers[i].congestion = 0;
        }
        else
        {
            routers[i].congestion =
                (routers[i].currentPackets * 100)
                / routers[i].capacity;
        }

        if (routers[i].congestion > 100)
            routers[i].congestion = 100;
    }
}

int findMostCongested(CongestionRouter routers[], int n)
{
    int i;
    int highest;

    highest = 0;

    for (i = 1; i < n; i++)
    {
        if (routers[i].congestion >
            routers[highest].congestion)
        {
            highest = i;
        }
    }

    return highest;
}

void displayCongestionQueue(CongestionQueue *queue)
{
    int i;
    int position;

    if (isCongestionQueueEmpty(queue))
    {
        printf("Queue is empty.\n");
        return;
    }

    position = queue->front;

    printf("\nPackets in Queue:\n");

    for (i = 0; i < queue->count; i++)
    {
        printf("Packet ID: %d\n",
               queue->packets[position].packetId);

        printf("Source: %d\n",
               queue->packets[position].source);

        printf("Destination: %d\n",
               queue->packets[position].destination);

        position++;

        if (position == CONGESTION_QUEUE_SIZE)
            position = 0;
    }
}

void displayCongestionRouters(CongestionRouter routers[], int n)
{
    int i;

    calculateCongestion(routers, n);

    printf("\nRouter Information\n");
    printf("-----------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("Router: %d\n", routers[i].routerId);
        printf("Capacity: %d\n", routers[i].capacity);
        printf("Packets: %d\n", routers[i].currentPackets);
        printf("Congestion: %d%%\n",
               routers[i].congestion);

        if (routers[i].congestion >= 80)
            printf("Status: HIGH\n");
        else if (routers[i].congestion >= 50)
            printf("Status: MEDIUM\n");
        else
            printf("Status: LOW\n");

        printf("-----------------------------\n");
    }
}

void displayStatistics(CongestionRouter routers[], int n)
{
    int i;
    int received;
    int sent;
    int dropped;

    received = 0;
    sent = 0;
    dropped = 0;

    printf("\nTraffic Statistics\n");
    printf("-----------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("Router %d\n", routers[i].routerId);

        printf("Received: %d\n",
               routers[i].packetsReceived);

        printf("Sent: %d\n",
               routers[i].packetsSent);

        printf("Dropped: %d\n",
               routers[i].packetsDropped);

        printf("\n");

        received = received + routers[i].packetsReceived;
        sent = sent + routers[i].packetsSent;
        dropped = dropped + routers[i].packetsDropped;
    }

    printf("Total Received: %d\n", received);
    printf("Total Sent: %d\n", sent);
    printf("Total Dropped: %d\n", dropped);
}