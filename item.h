#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#define MAX_ITEM_NAME_LEN 10

typedef struct item
{
	int item_ID;
	char itemName[MAX_ITEM_NAME_LEN];
} item;

#endif
