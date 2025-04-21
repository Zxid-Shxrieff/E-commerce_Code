#ifndef CART_H
#define CART_H
#include "base.h"
#include<unistd.h>
typedef struct llnode {
  struct llnode *next;
  PRODUCT product;
} LLNODE;
//FUNCTIONS USED
LLNODE *enqueue(LLNODE *head, PRODUCT *products, int index);
LLNODE *deleteAt(LLNODE *head, int index);
void viewCart(LLNODE *head);
LLNODE *dequeue(LLNODE *head);
#endif