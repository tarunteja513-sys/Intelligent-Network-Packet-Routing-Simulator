#include <stdio.h>
#include "packet.h"

int main(void)
{
    PacketQueue queue;
    Packet packet;

    initializeQueue(&queue);

    printf("\n============================================\n");
    printf("       PACKET PRIORITY QUEUE TEST\n");
    printf("============================================\n");

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

    printf("\nCurrent Queue:\n");
    displayPackets(&queue);

    printf("\n============================================\n");
    printf("          PACKET TRANSMISSION\n");
    printf("============================================\n");

    while (queue.count != 0)
    {
        dequeuePacket(&queue);
    }

    printf("\nAll packets have been transmitted.\n");

    return 0;
}