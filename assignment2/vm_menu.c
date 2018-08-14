/******************************************************************************
** Student name: 	Montana McCallum
** Student number: 	s3645635
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm_menu.h"

/**
 * vm_menu.c handles the initialisation and management of the menu array.
 **/

/**
 * In this function you need to initialise the array of menu items
 * according to the text to be displayed for the menu. This array is
 * an array of MenuItem with text and a pointer to the function
 * that will be called.
 **/
void mainMenu(VmSystem * system)
{
    MenuItem menu[9];
    MenuFunction function;
    int a;

    initMenu(menu);
    printf("\n");
    printf("Main Menu: \n");
    for(a = 0; a < 3; a++) {
        printf("%s \n", menu[a].text);
    }
    printf("Administrator-Only Menu: \n");
    for(a = 3; a < 9; a++) {
        printf("%s \n", menu[a].text);
    }
    while(TRUE) {
        printf("\nSelect your option (1-9): ");
        function = getMenuChoice(menu);
        if(function == NULL) {
            continue;
        }
        else {
            function(system);
            mainMenu(system);
        }
    }
}
 
void initMenu(MenuItem * menu)
{ 
    strcpy(menu[0].text, "1. Display Items");
    menu[0].function = &displayItems;
    strcpy(menu[1].text, "2. Purchase Items");
    menu[1].function = &purchaseItem;
    strcpy(menu[2].text, "3. Save and Exit");
    menu[2].function = &saveAndExit;
    strcpy(menu[3].text, "4. Add Item");
    menu[3].function = &addItem;
    strcpy(menu[4].text, "5. Remove Item");
    menu[4].function = &removeItem;
    strcpy(menu[5].text, "6. Display Coins");
    menu[5].function = &displayCoins;
    strcpy(menu[6].text, "7. Reset Stock");
    menu[6].function = &resetStock;
    strcpy(menu[7].text, "8. Reset Coins");
    menu[7].function = &resetCoins;
    strcpy(menu[8].text, "9. Abort Program");
    menu[8].function = &abortProgram;
}

/**
 * Gets input from the user and returns a pointer to the MenuFunction
 * that defines how to perform the user's selection. NULL is returned
 * if an invalid option is entered.
 **/

MenuFunction getMenuChoice(MenuItem * menu)
{
    int choice;
    char input[512];
    char * end;

    if(fgets(input, sizeof(input), stdin) == NULL) {
        return NULL;
    }
    else {
        if(input[strlen(input) - 1] != '\n') {
            printf("Line entered was too long \n\n");
            readRestOfLine();
            return NULL;
        }
        else {
            input[strlen(input) - 1] = '\0'; /* removes enter at end of line */
            choice = strtol(input, &end, 10);

            if(choice > 0 && choice < 10) {
                choice--;
                return menu[choice].function;
            }
            else {
                printf("That is not a valid option\n");
                return NULL;
            }
        }
    }
    if(input[0] == '\0') {
        return NULL;
    }
    printf("That is not a valid option");
    return NULL;
}
