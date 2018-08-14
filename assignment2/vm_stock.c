/******************************************************************************
** Student name: 	Montana McCallum
** Student number: 	s3645635
:q
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm_stock.h"

/**
 * vm_stock.c this is the file where you will implement the
 * interface functions for managing the stock list.
 **/

/**
 * Some example functions:
 * create list, free list, create node, free node, insert node, etc...
 **/

List * createList() {
    List * stockList = malloc(sizeof(*stockList));

    stockList->head = NULL;
    stockList->size = 0;

    return stockList;
}

void freeList(VmSystem * system) {
    Node * node = system->itemList->head;

    while(node != NULL) {
        Node * freeNode = node;
        node = node->next;

        free(freeNode->data);
        free(freeNode);
    }
    free(system->itemList);
}

void insertNode(VmSystem * system, List * list, Stock * stock) {
    Node * previousNode,* currentNode;
    Node * newNode = malloc(sizeof(*newNode));

    newNode->data = malloc(sizeof(*newNode->data));
    *newNode->data  = *stock;
    newNode->next = NULL;
    previousNode = NULL;

    currentNode = system->itemList->head;

    while(currentNode != NULL) {
        if(strcmp(stock->name, currentNode->data->name) < 0)
        {
            system->itemList->size++;
            break;
        }
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    if(system->itemList->head == NULL) {
        system->itemList->head = newNode;
    }
    else if(previousNode == NULL) {
        newNode->next = system->itemList->head;
        system->itemList->head = newNode;
    }
    else {
        previousNode->next = newNode;
        newNode->next = currentNode;
    }
}

Node * searchNode(VmSystem * system, char * ID) {
    Node * previousNode, * currentNode;
    
    previousNode = NULL;
    currentNode = system->itemList->head;

    while(currentNode != NULL) {
        if(strcmp(ID, currentNode->data->id) == 0) {
            return currentNode;
        }
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    return previousNode;
}

Boolean freeNode(VmSystem * system, char * ID) {
    Node * previousNode, * currentNode;

    currentNode = system->itemList->head;
    previousNode = NULL;

    while(currentNode != NULL) {
        if(strcmp(ID, currentNode->data->id) == 0) {
            /*if item being deleted is the head of the list, make head next node*/
            if(previousNode == NULL) {
                system->itemList->head = currentNode->next;
            }
            /* make previous nodes 'next' variable equal deleted nodes 'next' variable to join the list*/
            else {
                previousNode->next = currentNode->next;
            }
            free(currentNode->data);
            free(currentNode);
            system->itemList->size--;
            return TRUE;
        }
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    return FALSE;
}

Price initPrice(char * cost) {
    int dollars, cents;
    char end;    
    Price price;
    
    sscanf(cost, "%d . %d%c", &dollars, &cents, &end);

    price.dollars = dollars;
    price.cents = cents;
    return price;
}
