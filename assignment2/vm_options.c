/******************************************************************************
** Student name:    Montana McCallum
** Student number: 	s3645635
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm_options.h"

/**
 * vm_options.c this is where you need to implement the system handling
 * functions (e.g., init, free, load, save) and the main options for
 * your program. You may however have some of the actual work done
 * in functions defined elsewhere.
 **/

/**
 * Initialise the system to a known safe state. Look at the structure
 * defined in vm_system.h.
 **/
Boolean systemInit(VmSystem * system)
{
    int a;
    List * stockList;
    stockList = createList();

    for (a = 0; a < NUM_DENOMS; a++) {
        system->cashRegister[a].denom = a;
        system->cashRegister[a].count = 0;
    }

    system->itemList = stockList;
    system->stockFileName = "stock.dat";
    system->coinFileName = "coints.dat";

    return FALSE;
}

/**
 * Free all memory that has been allocated. If you are struggling to
 * find all your memory leaks, compile your program with the -g flag
 * and run it through valgrind.
 **/
void systemFree(VmSystem * system)
{ 
    freeList(system);
    free(system);
}

/**
 * Loads the stock and coin data into the system. You will also need to assign
 * the char pointers to the stock and coin file names in the system here so
 * that the same files will be used for saving. A key part of this function is
 * validation. A substantial number of marks are allocated to this function.
 **/
Boolean loadData(
    VmSystem * system, const char * stockFileName, const char * coinsFileName)
{
    return FALSE;
}

/**
 * Loads the stock file data into the system.
 **/
Boolean loadStock(VmSystem * system, const char * fileName)
{
    FILE * fp;
    char buffer[512];
    char * end;
    int a;
    int onHand;

    system->stockFileName = fileName;
    
    if((fp = fopen(fileName, "r")) != NULL) {
        while(fgets(buffer, 512, fp) != NULL) {
            char * token;
            Stock stock;
            a = 0;
            token = strtok(buffer, STOCK_DELIM);
            while(token != NULL) {
                if(a == 0) {
                    strcpy(stock.id, token);
                }
                else if(a == 1) {
                    strcpy(stock.name, token);
                }
                else if(a == 2) {
                    strcpy(stock.desc, token);
                }
                else if(a == 3) {
                    stock.price = initPrice(token);
                }
                else if(a == 4) {
                    onHand = strtol(token, &end, 10);
                    stock.onHand = onHand;
                }
                token = strtok(NULL, STOCK_DELIM);
                a++;
            }
            insertNode(system, system->itemList, &stock);
        }
        fclose(fp);
        return TRUE;
    }
    else {
        return FALSE;
    }
}

/**
 * Loads the coin file data into the system.
 **/
Boolean loadCoins(VmSystem * system, const char * fileName)
{
    return FALSE;
}

/**
 * Saves all the stock back to the stock file.
 **/
Boolean saveStock(VmSystem * system)
{
    FILE * fp;
    Node * node = system->itemList->head;

    if((fp = fopen("stock.dat", "w")) != NULL) {
        while(node != NULL)
        {
            fprintf(fp, "%s|%s|%s|%d.%02d|%d\n", node->data->id, node->data->name, node->data->desc, node->data->price.dollars, node->data->price.cents, node->data->onHand);
            node = node->next;
        }
        fclose(fp);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * Saves all the coins back to the coins file.
 **/
Boolean saveCoins(VmSystem * system)
{
    return FALSE;
}

/**
 * This option allows the user to display the items in the system.
 * This is the data loaded into the linked list in the requirement 2.
 **/
void displayItems(VmSystem * system)
{
    Node * node = system->itemList->head;
    Node * longestName = system->itemList->head;
    int length;
    int longestString = 0;
    int addLength;
    int a;

    while(longestName != NULL)
    {
        length = strlen(longestName->data->name);
        if(length > longestString) {
            longestString = length;
        }
        longestName = longestName->next;
    }

    longestString++;
    printf("Items Menu\n\n");
    addLength = longestString - 4;
    printf("ID    | Name");

    for(a = 0; a < addLength; a++) {
        printf(" ");
    }

    printf("| Available | Price \n");
    printf("---------------------------------------------\n");

    while(node != NULL) {
        printf("%s | ", node->data->id);
        printf("%s", node->data->name);
        addLength = longestString - strlen(node->data->name);

        for(a = 0; a < addLength; a++) {
            printf(" ");
        }
        
        printf("| %d ", node->data->onHand);
        
        /* checks if onHand is 1 or 2 digits and adds spaces accordingly */
        if(node->data->onHand >= 10) {
            for(a = 0; a < 7; a++) {
                printf(" ");    
            }
        }
        else {
            for(a = 0; a < 8; a++) {
                printf(" ");  
            }
        }
        printf("| %d.%02d \n", node->data->price.dollars, node->data->price.cents);
        node = node->next;
    }
    printf("\n");
}

/**
 * This option allows the user to purchase an item.
 * This function implements requirement 5 of the assignment specification.
 **/
void purchaseItem(VmSystem * system)
{ 
    printf("Purchase Item \n");
    printf("------------- \n");
    while(TRUE) {
        char input[512];
        char * end;
        Node * node = system->itemList->head;
        int total;
        int value;
        int change = 0;
        int transaction = 0;
        
        printf("Please enter the id of the item you wish to purchase: ");
        if(fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        else {
            if(input[strlen(input) - 1] != '\n') {
                printf("Line entered was too long\n");
                readRestOfLine();
            }
            else {
                input[strlen(input) - 1] = '\0'; /*removes enter at end of string*/
            }
        }
        /* if input is empty then break out of while loop*/
        if(input[0] == '\0') {
            break;
        }

        while(node != NULL) {
            if(strcmp(node->data->id, input) == 0) {
                if(node->data->onHand == 0) {
                    printf("This item is not in stock\n");
                    total = -1;
                    transaction = 1;
                    break;
                }
                printf("You have selected %s %s. This will cost you $%d.%02d. \n", node->data->name, node->data->desc, node->data->price.dollars, node->data->price.cents);
                printf("Please hand over the money - type in the value of each note/coin in cents.\n");
                printf("Press enter on a new and empty line to cancel this purchase:\n");

                total = (node->data->price.dollars * 100) + node->data->price.cents;

                while (TRUE) {
                    printf("You still owe us $%d.%02d: ", total/100, total%100);
                    if(fgets(input, sizeof(input),stdin) == NULL) {
                        total = total -((node->data->price.dollars * 100) + node->data->price.cents);
                        total = total * -1;
                        printf("Purchase cancelled - here is your change: $%d.%02d. \n", total/100, total%100);
                        total = -1;
                        break;
                    }
                    else {
                        if(input[strlen(input) - 1] != '\n') {
                            printf("Line entered was too long. \n");
                            readRestOfLine();
                        }
                        else {
                            input[strlen(input-1) - 1] = '0'; /*removes enter at end of string*/
                        }
                    }
                    value = strtol(input, &end, 10);
                    if(value != 5 && value != 10 && value != 20 && value != 50 && value != 100 && value != 200 && value != 500 && value != 1000) {
                        printf("That is not a valid interger \n");
                        continue;
                    }

                    if(value != 0) {
                        if(total == 0) {
                            break;
                        }
                        total = total - value;
                        if(total < 0) {
                            change = total * -1;
                            break;
                        }
                        if(total == 0) {
                            break;
                        }
                    }
                }
                if(change != 0) {
                    printf("Thank you. Here is your %s and your change of $%d.%02d.\n", node->data->name, change/100, change%100);
                }
                printf("Pleae come back soon.\n");
                transaction = 1;
                break;
            }
            node = node->next;
        }
        if(transaction == 1) {
            if(total != -1) {
                node->data->onHand--;
            }
            break;
        }
        printf("You did not enter a valid I. \n");
    }
}

/**
 * You must save all data to the data files that were provided on the command
 * line when the program loaded up, display goodbye and free the system.
 * This function implements requirement 6 of the assignment specification.
 **/
void saveAndExit(VmSystem * system)
{ 
    if(saveStock(system) == FALSE) {
        printf("Unable to save stock data\n");
    }
    systemFree(system);
    exit(EXIT_SUCCESS);
}

/**
 * This option adds an item to the system. This function implements
 * requirement 7 of of assignment specification.
 **/
void addItem(VmSystem * system)
{ 
    Node * node = system->itemList->head;
    Stock stock;
    char id[5], newId[5], input[512], * tempId, * next, * token;
    char tempName[NAME_LEN + NULL_SPACE];
    char tempDesc[DESC_LEN + NULL_SPACE];
    char tempPrice[10];
    int a, i, outputNo, tempDollar, tempCents;
    int loops = 0;
    int j = 0;
    int highestId = 0;
    int errors = 0;
    int exit = 0;
    long value;

    /* finds the highest ID so the next one created is the iteration of it*/
    while(node != NULL) {
        a = 0;
        for(i = 1; i < 5; i++) {
            id[a] = node->data->id[i];
            a++;
        }
        id[5] = '\0';
        tempId = id;
        outputNo = strtol(tempId, &next, 10);
        if(outputNo > highestId) {
            highestId = outputNo;
        }
        node = node->next;
    }
    sprintf(newId, "I%04d", highestId + 1);
    printf("This new meal item will have the item ID of %s\n", newId);
    printf("Enter the item name: ");
    while(TRUE) {
        /* depending on how many times the while loop has been executed, input needed changes*/
        if(loops == 1) {
            printf("Enter the item description: ");
        }
        else if(loops == 2) {
            printf("Enter the price for this item: ");
        }
        if (fgets(input, sizeof(input), stdin) == NULL) {
            exit = 1;
            break;
        }
        else {
            input[strlen(input) - 1] = '\0'; /*removes enter at end of string*/
        }

        if(input[0] == '\0') {
            exit = 1;
            break;
        }

        if(loops == 0) {
            if(strlen(input) > NAME_LEN + NULL_SPACE) {
                printf("Name was too long \n");
                printf("Enter the item name: ");
                continue;
            }
            else {
                strcpy(tempName, input);
            }
        }
        else if(loops == 1) {
            if(strlen(input) > DESC_LEN + NULL_SPACE) {
                printf("Description was too long \n");
                continue;
            }
            else {
                strcpy(tempDesc, input);
            }
        }
        else if(loops == 2) {
            j = 0;
            errors = 0;
            token = strtok(input, ".");

            while(token != NULL) {
                if(j == 0) {
                    value = strtol(token, &next, 10);
                    if(*next) {
                        printf("The price is not valid. \n");
                        errors = 1;
                        break;
                    }
                    else {
                        tempDollar = value;
                    }
                }
                if(j == 1) {
                    value = strtol(token, &next, 10);
                    if(*next) {
                        printf("The cents are not valid\n");
                        errors = 1;
                        break;
                    }
                    if(strlen(token) == 2) {
                        /* checks cents entered are a multiple of 5*/
                        if(value % 5 != 0) {
                            printf("The cents must be a multiple of 5. \n");
                            errors = 1;
                            break;
                        }
                        tempCents = value;
                        break;
                    }
                    else {
                        printf("The cents are not valid\n");
                        errors = 1;
                        break;
                    }
                }
                token = strtok(NULL, ".");
                j++;
            }
            if(errors == 1) {
                continue;
            }
            break;
        }
        loops++;
    }
    if (exit != 1) {
        sprintf(tempPrice, "%d.%02d", tempDollar, tempCents);
        strcpy(stock.id, newId);
        strcpy(stock.name, tempName);
        strcpy(stock.desc,tempDesc);
        stock.price = initPrice(tempPrice);
        stock.onHand = DEFAULT_STOCK_LEVEL;
        insertNode(system, system->itemList, &stock);
        
        printf("This item %s - %s has now been added to the menu.\n", stock.name, stock.desc);
    }
    else {
        printf("Cancelling add item.\n");
    }
}

/**
 * Remove an item from the system, including free'ing its memory.
 * This function implements requirement 8 of the assignment specification.
 **/
void removeItem(VmSystem * system)
{ 
    char input[ID_LEN + NULL_SPACE + 1];
    Node * removedNode;
    char output[512];

    while(TRUE) {
        printf("Enter the item id of the item you want to remove from the menu: ");
        if(fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        else {
            input[strlen(input) - 1] = '\0'; /*removes enter at end of string*/
        }
        if(input[0] == '\0') {
            break;
        }
        break;
    }
    removedNode = searchNode(system, input);
    sprintf(output, "%s - %s %s", removedNode->data->id, removedNode->data->name, removedNode->data->desc);
    if(freeNode(system, input) == FALSE) {
        printf("Removed Item failed to run successfully \n");
    }
    else {
        printf("%s has been removed from the system.\n", output);
    }
}

/**
 * This option will require you to display the coins from lowest to highest
 * value and the counts of coins should be correctly aligned.
 * This function implements part 4 of requirement 18 in the assignment
 * specifications.
 **/
void displayCoins(VmSystem * system)
{ }

/**
 * This option will require you to iterate over every stock in the
 * list and set its onHand count to the default value specified in
 * the startup code.
 * This function implements requirement 9 of the assignment specification.
 **/
void resetStock(VmSystem * system)
{ 
    Node * node = system->itemList->head;

    while(node != NULL) {
        node->data->onHand = DEFAULT_STOCK_LEVEL;
        node = node->next;
    }
    printf("Stock has been reset to the default stock level");
}

/**
 * This option will require you to iterate over every coin in the coin
 * list and set its 'count' to the default value specified in the
 * startup code.
 * This requirement implements part 3 of requirement 18 in the
 * assignment specifications.
 **/
void resetCoins(VmSystem * system)
{ }

/**
 * This option will require you to display goodbye and free the system.
 * This function implements requirement 10 of the assignment specification.
 **/
void abortProgram(VmSystem * system)
{
    systemFree(system);
    exit(EXIT_SUCCESS);
}
