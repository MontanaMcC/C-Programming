/******************************************************************************
** Student name: 	Montana McCallum
** Student number: 	s3645635
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#ifndef VM_STOCK_H
#define VM_STOCK_H

#include "vm_coin.h"

/**
 * The default stock level that all new stock should start with and the value
 * to use when restting stock.
 **/
#define DEFAULT_STOCK_LEVEL 20

#define STOCK_DELIM "|"

#endif

List * createList();
void freeList(VmSystem * system);
void insertNode(VmSystem * system, List * list, Stock * stock);
Node * searchNode(VmSystem * system, char * ID);
Boolean freeNode(VmSystem * system, char * ID);
Price initPrice(char * cost);
