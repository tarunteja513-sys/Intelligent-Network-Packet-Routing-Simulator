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
    printf("\nEnter Packet ID: ");
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
    if (queue->count >= MAX_QUEUE_SIZE)
    {
        printf("\nQueue is full. Packet cannot be added.\n");
        return;
    }

    queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    queue->packets[queue->rear] = packet;
    queue->count++;

    printf("\nPacket %d added to the queue.\n", packet.packetID);
}

Packet dequeuePacket(PacketQueue *queue)
{
    Packet result = {0, 0, 0, 0, 0};
    int selected;
    int selectedPriority;
    int position;

    if (queue->count <= 0)
    {
        printf("\nQueue is empty. No packet to transmit.\n");
        return result;
    }

    selected = queue->front;
    selectedPriority = queue->packets[selected].priority;

    /* Find the highest-priority packet.
       Smaller priority number means higher priority. */
    for (position = 1; position < queue->count; position++)
    {
        int current = (queue->front + position) % MAX_QUEUE_SIZE;

        if (queue->packets[current].priority < selectedPriority)
        {
            selected = current;
            selectedPriority = queue->packets[current].priority;
        }
    }

    result = queue->packets[selected];

    /* Shift the remaining packets */
    while (selected != queue->rear)
    {
        int next = (selected + 1) % MAX_QUEUE_SIZE;

        queue->packets[selected] = queue->packets[next];
        selected = next;
    }

    queue->rear =
        (queue->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;

    queue->count--;

    if (queue->count == 0)
    {
        queue->front = 0;
        queue->rear = -1;
    }

    printf("\nPacket %d transmitted (Priority: %d).\n",
           result.packetID,
           result.priority);

    return result;
}

void displayPackets(const PacketQueue *queue)
{
    int position;

    if (queue->count == 0)
    {
        printf("\nNo packets in the queue.\n");
        return;
    }

    printf("\n================ PACKET QUEUE ================\n");
    printf("ID\tSource\tDestination\tPriority\tSize\n");
    printf("------------------------------------------------\n");

    for (position = 0; position < queue->count; position++)
    {
        int index = (queue->front + position) % MAX_QUEUE_SIZE;

        printf("%d\t%d\t%d\t\t%d\t\t%d\n",
               queue->packets[index].packetID,
               queue->packets[index].source,
               queue->packets[index].destination,
               queue->packets[index].priority,
               queue->packets[index].size);
    }

    printf("------------------------------------------------\n");
}