#include "product.h"

int getNumProducts(PRODUCT *products) {
    int count = 0;
    while (products[count].name[0] != '\0') {  // Check for empty name to determine end of list
        count++;
    }
    return count;
}