// Arda Menşur
#include "avltree.h"

int main()
{
    int exit = FALSE;
    char filename[MAX]="fishes.txt";
    int command;
    printf("********Welcome to Fishdom Analysis********\n");

    do {
        printf("*******************************************\n"
               "Menu\n"
               "1. Display the full index of fishdom\n"
               "2. Display the heaviest fishes\n"
               "3. Display the longest fishes\n"
               "4. Exit\n"
               "*******************************************\n"
               "Enter your option:");
        scanf("%d",&command);
        fflush(stdin);
        AVLTree New_Tree = readData(filename);
        switch (command)
        {
            case 1: {//Display the full index of fishdom
                displayIndex(New_Tree);
                break;
            }
            case 2: {//Display the heaviest fishes
                heaviestFish(New_Tree);
                break;
            }
            case 3: {//Display the longest fishes
                Node longest_fish_node = longestFish(New_Tree);
                printf("%s  %03d  %.2f %02d/%02d/%-5d  %s\n", longest_fish_node->name, longest_fish_node->weight, longest_fish_node->length, longest_fish_node->day, longest_fish_node->month, longest_fish_node->year, longest_fish_node->city);
                break;
            }
            case 4: {//exit condition.
                exit = TRUE;
                break;
            }
            default:
                printf("You entered wrong command!!! Please try again\n");
        }

    } while (!exit);
    printf("Bye!\n");
    return 0;
}

