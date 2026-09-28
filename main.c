#include <stdio.h>
#include "graph.h"

int main()
{
    int choice;

    initializeGraph();

    printf("============================================\n");
    printf(" INTELLIGENT NETWORK PACKET ROUTING SYSTEM\n");
    printf("        NETWORK TOPOLOGY MODULE\n");
    printf("============================================\n");

    while (1)
    {
        printf("\n\n----------- MENU -----------\n");
        printf("1. Add Router\n");
        printf("2. Add Communication Link\n");
        printf("3. Display Routers\n");
        printf("4. Display Network\n");
        printf("5. Display Adjacency Matrix\n");
        printf("6. Remove Router\n");
        printf("7. Change Link Cost\n");
        printf("8. Remove Link\n");
        printf("9. Exit\n");
        printf("----------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addRouter();
                break;

            case 2:
                addLink();
                break;

            case 3:
                displayRouters();
                break;

            case 4:
                displayNetwork();
                break;

            case 5:
                displayMatrix();
                break;

            case 6:
                removeRouter();
                break;

            case 7:
                changeLink();
                break;

            case 8:
                removeLink();
                break;

            case 9:
                printf("\nProgram terminated.\n");
                return 0;

            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }

    return 0;
}