#ifndef PACKET_H
#define PACKET_H

#define MAX_QUEUE_SIZE 100

typedef struct
{
    int packetID;
    int source;
    int destination;
    int priority;
    int size;
} Packet;

typedef struct
{
    Packet packets[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int count;
} PacketQueue;

void initializeQueue(PacketQueue *queue);
void createPacket(Packet *packet);
void enqueuePacket(PacketQueue *queue, Packet packet);
Packet dequeuePacket(PacketQueue *queue);
void displayPackets(const PacketQueue *queue);

#endif