#ifndef BASE_H
#define BASE_H
#define MAX_PRODUCTS 16
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct product {
    int index;
    char name[20];
    char description[40];
    float rating;
    float price;
    float discount;
    int sales;
    char firstBrought[20];
    char secondBrought[20];
    char thirdBrought[20];
} PRODUCT;
//FUNCTIONS USED
PRODUCT *loadProducts(const char *category);
void printProducts(PRODUCT *products);

#endif