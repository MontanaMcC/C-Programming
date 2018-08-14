/******************************************************************************
** Student name: 	Montana McCallum
** Student number: 	s3645635
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm.h"

int main(int argc, char ** argv)
{
    VmSystem * system = malloc(sizeof * system);
    systemInit(system);
    
    if (argc != 3) {
        printf("Program requires a stock and coins arguments");
        return EXIT_SUCCESS;
    }
    if (argc == 3) {
        if(loadStock(system, argv[1]) == FALSE) {
                printf("Could not load file");
                return EXIT_SUCCESS;
        }
    }
    mainMenu(system);
    return EXIT_SUCCESS;
}

/* original menu function */
/*
void deprecatedMenu(char* stockFile) {
    int selection;
    printf("Main Menu: \n");
    printf("1. Display Items \n");
    printf("2. Purchase Items \n");
    printf("3. Save and Exit \n");
    printf("Administrator-Only Menu \n");
    printf("4. Add Item \n");
    printf("5. Remove Item \n");
    printf("6. Display Coins \n");
    printf("7. Reset Stock \n");
    printf("8. Reset Coins \n");
    printf("9. Abort Program \n");
    printf("Select your option (1-9): \n\n");

    scanf("%d", &selection);
    if (selection == 1) {
        printf("\n\n");
        displayStock(stockFile);
    }
    else if (selection == 9 || selection == 3) {
        exit(0);
    }
    else {
        printf("\nInvalid\n\n");
        exit(0);
    }
}
*/
