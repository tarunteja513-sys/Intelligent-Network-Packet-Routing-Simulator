#include <stdio.h>
#include "packet.h"

int main()
{
    PacketQueue queue;
    Packet packet;

    initializeQueue(&queue);

    printf("=== Packet Creation & Priority Queue Test ===\n");

    packet.packetID = 1;
    packet.source = 0;
    packet.destination = 3;
    packet.priority = 3;
    packet.size = 500;
    enqueuePacket(&queue, packet);

    packet.packetID = 2;
    packet.source = 0;
    packet.destination = 2;
    packet.priority = 1;
    packet.size = 300;
    enqueuePacket(&queue, packet);

    packet.packetID = 3;
    packet.source = 1;
    packet.destination = 3;
    packet.priority = 2;
    packet.size = 400;
    enqueuePacket(&queue, packet);

    displayPackets(&queue);

    printf("\n=== Transmission Order ===\n");

    while (queue.count > 0)
    {
        dequeuePacket(&queue);
    }

    return 0;
}