#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

// Node structure for the adjacency list
struct node {
    char data[256];
    struct node *next;
};

// List structure for the adjacency list
struct list {
    char item[256];
    struct node *head;
};

// Array of pointers to list
struct list *adj_list[MAX];

// Product recommendations data
struct productRecommendations {
    char product[256];
    char recommendations[5][256];
} data[MAX] = {
    {"Samsung", {"Smartphone A12", "Laptop L14", "4K TV P7", "Soundbar S3", "Smart Speaker G3"}},
    {"Smartphone A12", {"Smartwatch A88", "Wireless Earbuds X1", "Portable Power Bank X8", "Tablet T8", "Laptop L15"}},
    {"Smartphone B12", {"Smartwatch A88", "Smart Speaker G3", "Soundbar S3", "Wireless Mouse M3", "Streaming Stick X1"}},
    {"Smartwatch A88", {"Wireless Earbuds X1", "Tablet T8", "Laptop L15", "Smartphone B12", "Portable Power Bank X8"}},
    {"Wireless Earbuds X1", {"Smartphone A12", "Smart Speaker G3", "Tablet T9", "Streaming Stick X1", "Laptop L14"}},
    {"Laptop L14", {"Laptop L15", "4K TV P7", "Wireless Mouse M3", "Tablet T8", "Smartwatch A88"}},
    {"Laptop L15", {"Laptop L14", "Wireless Keyboard K2", "Tablet T9", "Soundbar S3", "Portable Power Bank X8"}},
    {"Wireless Mouse M3", {"Wireless Keyboard K2", "Streaming Stick X1", "Tablet T8", "Smart Speaker G3", "Laptop L15"}},
    {"Wireless Keyboard K2", {"Wireless Mouse M3", "Tablet T8", "Tablet T9", "Streaming Stick X1", "Smartwatch A88"}},
    {"Tablet T8", {"Tablet T9", "Smart Speaker G3", "Smartwatch A88", "Wireless Mouse M3", "Portable Power Bank X8"}},
    {"Tablet T9", {"Tablet T8", "Laptop L14", "4K TV P7", "Smart Speaker G3", "Wireless Earbuds X1"}},
    {"4K TV P7", {"Soundbar S3", "Streaming Stick X1", "Smart Speaker G3", "Laptop L15", "Tablet T8"}},
    {"Soundbar S3", {"4K TV P7", "Streaming Stick X1", "Portable Power Bank X8", "Smartwatch A88", "Wireless Earbuds X1"}},
    {"Streaming Stick X1", {"Soundbar S3", "Smart Speaker G3", "Wireless Keyboard K2", "Smartphone B12", "Tablet T9"}},
    {"Smart Speaker G3", {"Portable Power Bank X8", "Smartwatch A88", "Tablet T8", "Wireless Earbuds X1", "Soundbar S3"}},
    {"Portable Power Bank X8", {"Wireless Earbuds X1", "Smartphone B12", "Laptop L14", "Tablet T9", "Streaming Stick X1"}}
};

// Initialize the adjacency list
void initializeAdjList() {
    for (int i = 0; i < MAX && data[i].product[0] != '\0'; i++) {
        adj_list[i] = (struct list *)malloc(sizeof(struct list));
        if (!adj_list[i]) {
            printf("Memory allocation failed for adj_list[%d]\n", i);
            exit(1);
        }

        // Copy product name
        strncpy(adj_list[i]->item, data[i].product, sizeof(adj_list[i]->item) - 1);
        adj_list[i]->item[sizeof(adj_list[i]->item) - 1] = '\0';

        // Create linked list for recommendations
        adj_list[i]->head = NULL;
        struct node *prev = NULL;

        for (int j = 0; j < 5; j++) {
            struct node *newNode = (struct node *)malloc(sizeof(struct node));
            if (!newNode) {
                printf("Memory allocation failed for node\n");
                exit(1);
            }

            // Copy recommendation data
            strncpy(newNode->data, data[i].recommendations[j], sizeof(newNode->data) - 1);
            newNode->data[sizeof(newNode->data) - 1] = '\0';
            newNode->next = NULL;

            if (!adj_list[i]->head) {
                adj_list[i]->head = newNode;
            } else {
                prev->next = newNode;
            }
            prev = newNode;
        }
    }
}

// Search for recommendations of a product
void searchRecommendations(const char *product) {
    for (int i = 0; i < MAX && adj_list[i]; i++) {
        if (strcmp(adj_list[i]->item, product) == 0) {
            printf("Recommendations for %s:\n", product);
            struct node *current = adj_list[i]->head;
            while (current) {
                printf("  %s\n", current->data);
                current = current->next;
            }
            return;
        }
    }
    printf("Product '%s' not found.\n", product);
}

// Add a new product to the recommendations list
void addProduct(const char *product, char newRecommendations[5][256]) {
    for (int i = 0; i < MAX; i++) {
        if (data[i].product[0] == '\0') {
            strncpy(data[i].product, product, sizeof(data[i].product) - 1);
            for (int j = 0; j < 5; j++) {
                strncpy(data[i].recommendations[j], newRecommendations[j], sizeof(data[i].recommendations[j]) - 1);
            }
            initializeAdjList();
            printf("Product '%s' added successfully!\n", product);
            return;
        }
    }
    printf("Error: Unable to add new product. Array is full.\n");
}

 int main() {
     initializeAdjList();
  
     int choice;
     char productName[256];
     char newRecommendations[5][256];
     while (1) {
         printf("\nMenu:\n");
         printf("1. Search recommendations for a product\n");
         printf("2. Add a new product with recommendations\n");
         printf("3. Exit\n");
         printf("Enter your choice: ");
         scanf("%d", &choice);
         getchar(); // Consume newline after integer input
         switch (choice) {
             case 1:
                 // Get the product name from user
                 printf("Enter product name to search: ");
                 fgets(productName, sizeof(productName), stdin);
                 productName[strcspn(productName, "\n")] = '\0'; // Remove the newline character
                 searchRecommendations(productName);
                 break;
             case 2:
                 // Get the new product name and recommendations from user
                 printf("Enter new product name: ");
                 fgets(productName, sizeof(productName), stdin);
                 productName[strcspn(productName, "\n")] = '\0'; // Remove the newline character
                 printf("Enter 5 recommendations for the product:\n");
                 for (int i = 0; i < 5; i++) {
                     printf("Recommendation %d: ", i + 1);
                     fgets(newRecommendations[i], sizeof(newRecommendations[i]), stdin);
                     newRecommendations[i][strcspn(newRecommendations[i], "\n")] = '\0'; // Remove the newline character
                 }
                 addProduct(productName, newRecommendations);
                 break;
             case 3:
                 // Exit the program
                 printf("Exiting program.\n");
                 return 0;
             default:
                 printf("Invalid choice! Please try again.\n");
         }
     }
     return 0;
 }