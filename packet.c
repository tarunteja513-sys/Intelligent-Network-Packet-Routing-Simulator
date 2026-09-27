#include <stdio.h>
#include "packet.h"

void initializeQueue(PacketQueue *queue)
{
    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
}

void createPacket(Packet *packet)
{
    printf("Enter Packet ID: ");
    scanf("%d", &packet->packetID);

    printf("Enter Source Router: ");
    scanf("%d", &packet->source);

    printf("Enter Destination Router: ");
    scanf("%d", &packet->destination);

    printf("Enter Priority (1=High, 2=Medium, 3=Low): ");
    scanf("%d", &packet->priority);

    printf("Enter Packet Size: ");
    scanf("%d", &packet->size);
}

void enqueuePacket(PacketQueue *queue, Packet packet)
{
    if (queue->count == MAX_QUEUE_SIZE)
    {
        printf("Queue is full. Packet cannot be added.\n");
        return;
    }

    queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    queue->packets[queue->rear] = packet;
    queue->count++;

    printf("Packet %d added to the queue.\n", packet.packetID);
}

Packet dequeuePacket(PacketQueue *queue)
{
    Packet packet = {0, 0, 0, 0, 0};

    if (queue->count == 0)
    {
        printf("Queue is empty. No packet to transmit.\n");
        return packet;
    }

    int bestIndex = queue->front;
    int bestPriority = queue->packets[bestIndex].priority;

    for (int i = 1; i < queue->count; i++)
    {
        int index = (queue->front + i) % MAX_QUEUE_SIZE;

        if (queue->packets[index].priority < bestPriority)
        {
            bestPriority = queue->packets[index].priority;
            bestIndex = index;
        }
    }

    packet = queue->packets[bestIndex];

    for (int i = bestIndex; i != queue->rear; i = (i + 1) % MAX_QUEUE_SIZE)
    {
        int nextIndex = (i + 1) % MAX_QUEUE_SIZE;
        queue->packets[i] = queue->packets[nextIndex];
    }

    queue->rear = (queue->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    queue->count--;

    if (queue->count == 0)
    {
        queue->front = 0;
        queue->rear = -1;
    }

    printf("Packet %d transmitted (Priority: %d).\n",
           packet.packetID, packet.priority);

    return packet;
}

void displayPackets(const PacketQueue *queue)
{
    if (queue->count == 0)
    {
        printf("No packets in the queue.\n");
        return;
    }

    printf("\nPackets in Queue:\n");
    printf("---------------------------------------------\n");
    printf("ID\tSource\tDestination\tPriority\tSize\n");
    printf("---------------------------------------------\n");

    for (int i = 0; i < queue->count; i++)
    {
        int index = (queue->front + i) % MAX_QUEUE_SIZE;
        Packet packet = queue->packets[index];

        printf("%d\t%d\t%d\t\t%d\t\t%d\n",
               packet.packetID,
               packet.source,
               packet.destination,
               packet.priority,
               packet.size);
    }

    printf("---------------------------------------------\n");
}