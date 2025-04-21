#include "base.h"

PRODUCT *loadProducts(const char *category){
    FILE *fptr = fopen(category, "r");
    if (!fptr){
        printf("Error: Could not open file %s\n", category);
        return NULL;
    }

    PRODUCT *products = (PRODUCT *)malloc(MAX_PRODUCTS * sizeof(PRODUCT));
    if (!products){
        printf("Error: Memory allocation failed.\n");
        fclose(fptr);
        return NULL;
    }

    char line[256]; // Buffer to store each line
    int i = 0;
    while (fgets(line, sizeof(line), fptr))    // Read each line from the file
    {
        // Remove the trailing newline character if it exists
        line[strcspn(line, "\n")] = 0;
        // Tokenize the line by commas
        char *token = strtok(line, ",");
        if (token)  products[i].index = atoi(token); // Read index
        token = strtok(NULL, ",");
        if (token)  strncpy(products[i].name, token, sizeof(products[i].name) - 1); // Read name
        token = strtok(NULL, ",");
        if (token)  strncpy(products[i].description, token, sizeof(products[i].description) - 1); // Read description
        token = strtok(NULL, ",");
        if (token)  products[i].rating = atof(token); // Read rating
        token = strtok(NULL, ",");
        if (token)  products[i].price = atof(token); // Read price
        token = strtok(NULL, ",");
        if (token)  products[i].discount = atof(token); // Read discount
        token = strtok(NULL, ",");
        if (token)  products[i].sales = atoi(token); // Read sales
        token = strtok(NULL, ",");
        if (token)  strncpy(products[i].firstBrought, token, sizeof(products[i].firstBrought) - 1); // Read firstBrought
        token = strtok(NULL, ",");
        if (token)  strncpy(products[i].secondBrought, token, sizeof(products[i].secondBrought) - 1); // Read secondBrought
        token = strtok(NULL, ",");
        if (token)  strncpy(products[i].thirdBrought, token, sizeof(products[i].thirdBrought) - 1); // Read thirdBrought
        i++;
    }

    fclose(fptr);
    return products;
}
void printProducts(PRODUCT *products){
    if (!products)
    {
        printf("No products to display.\n");
        return;
    }

    // Print the header row
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-5s | %-20s | %-40s | %-7s | %-10s | %-10s | %-10s | %-20s | %-20s | %-20s |\n",
           "Index", "Name", "Description", "Rating", "Price", "Discount", "Sales", "First Bought", "Second Bought", "Third Bought");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    // Print each product in a row
    for (int i = 0; i < MAX_PRODUCTS; i++)
    {
        if(products[i].index==0 && products[i].rating==0) break;
        printf("| %-5d | %-20s | %-40s | %-7.2f | %-10.2f | %-10.2f | %-10d | %-20s | %-20s | %-20s |\n",
               products[i].index, products[i].name, products[i].description,
               products[i].rating, products[i].price, products[i].discount, products[i].sales,
               products[i].firstBrought, products[i].secondBrought, products[i].thirdBrought);
    }

    // Print the footer
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}


             