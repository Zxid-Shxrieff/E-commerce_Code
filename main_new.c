#include "base.h"
#include "cart.h"
#include "filter.h"
// #include "product.h"
#define MAX 20

int numProducts;

int getNumProducts(PRODUCT *products) {
    int count = 0;
    while (products[count].name[0] != '\0') {  // Check for empty name to determine end of list
        count++;
    }
    return count;
}

void printRecommendations(PRODUCT *products, int numProducts) {
    if (numProducts == 0) {
        printf("\033[1;31m\nNo Recommended Products To Display.\033[0m\n");
        return;
    }

    for (int i = 0; i < numProducts; i++) {
        printf("Product Name: %-20s Price: ₹%.2f Rating: %.1f Sales: %d Discount: %.2f%%\n", 
               products[i].name, 
               products[i].price,       // For price, use %.2f for double
               products[i].rating,      // For rating, use %.1f for double
               products[i].sales,       // For sales, use %d for int
               products[i].discount);   // For discount, use %d for int
    }
}

// Function to compare products based on rating
int compareByRating(const void *a, const void *b) {
    PRODUCT *productA = (PRODUCT *)a;
    PRODUCT *productB = (PRODUCT *)b;
    if (productB->rating < productA->rating) return -1;
    if (productB->rating > productA->rating) return 1;
    return 0;
}

// Function to compare products based on sales
int compareBySales(const void *a, const void *b) {
    PRODUCT *productA = (PRODUCT *)a;
    PRODUCT *productB = (PRODUCT *)b;
    return (productB->sales - productA->sales);  // Sort in descending order
}

// Function to compare products based on discount
int compareByDiscount(const void *a, const void *b) {
    PRODUCT *productA = (PRODUCT *)a;
    PRODUCT *productB = (PRODUCT *)b;
    return (productB->discount - productA->discount);  // Sort in descending order
}

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
            printf("\nMemory Allocation Failed For Adj_list[%d].\n", i);
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
                printf("\nMemory Allocation Failed For Node.\n");
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
            printf("\n\033[1;32mRecommendations For %s:\033[0m\n", product);
            struct node *current = adj_list[i]->head;
            while (current) {
                printf("  %s\n", current->data);
                current = current->next;
            }
            return;
        }
    }
    printf("\033[1;31m\nProduct '%s' Not Found.\033[0m\n", product);
}

// Function to display the main menu
int menu() {
    printf("\033[2J\033[H"); // Clear the screen (optional)
    printf("**********************************************************************************************\n");
    printf("*\033[1;32m                         WELCOME TO THE MENU           \033[0m*\n");
    printf("**********************************************************************************************\n");
    printf("                       \033[1;33m 1 ADD PRODUCT TO CART 📦\033[0m                           \n");
    printf("                       \033[1;34m 2 FILTER PRODUCTS BASED ON PRICE 💰\033[0m                \n");
    printf("                       \033[1;36m 3 VIEW TRENDING PRODUCTS 📈\033[0m                        \n");
    printf("                       \033[1;36m 4 VIEW RECOMMENDATIONS 📈\033[0m                          \n");
    printf("                       \033[1;35m 5 PROCEED FOR PAYMENT 💳\033[0m                           \n");
    printf("                       \033[1;35m 6 VIEW AND EDIT CART 💳\033[0m                            \n");
    printf("                       \033[1;31m 7 EXIT ❌\033[0m                                          \n");
    printf("**********************************************************************************************\n");
    printf("\033[1;34mEnter your choice (1-7):\033[0m ");
    int n;
    scanf("%d", &n);
    while (getchar() != '\n'); // Clear the input buffer
    return n;
}

// Helper function to get the size of the cart
int getCartSize(LLNODE *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}
// Function to display the cart details in tabular format
void displayCartDetails(LLNODE *head) {
    printf("\n\033[1;33mItems in your cart:\033[0m\n");
    printf("------------------------------------------------------------------------------------------------------------\n");
    printf("| Index | Product Name           | Price      |\n");
    printf("------------------------------------------------------------------------------------------------------------\n");
    
    LLNODE *current = head;
    int index = 1; // Start from 1
    while (current != NULL) {
        printf("| %-5d | %-22s | ₹%-9.2f |\n", index, current->product.name, current->product.price);
        current = current->next;
        index++; // Increment index to match the sequence in the cart
    }
    printf("------------------------------------------------------------------------------------------------------------\n");
}

// Main function
void main() {
    int choice, lowerLimit, upperLimit, index;
    char back;
    PRODUCT *products = loadProducts("electronics.csv");
    LLNODE *head = NULL;

    intro:
        choice = menu(); 
        switch (choice) {
            case 1: // Add product to cart
                printProducts(products); //
                printf("\033[1;33m\nEnter Product Index: \033[0m");
                scanf("%d", &index);
                if(index>15){
                    printf("\033[1;31m\nInvalid Index. Please Try Again.\033[0m\n");
                    goto intro;
                }
                else{
                    while (getchar() != '\n'); // Clear the input buffer
                    head = enqueue(head, products, index);
                    printf("\n\033[1;32mProduct Added Successfully To Cart!\033[0m\n");
                    displayCartDetails(head);
                goto intro;
                }

            case 2: // Filter products based on price
                priceFilterMenu:
                printf("\033[2J\033[H"); // Clear the screen
                printf("\033[0;32mEnter Lower Price Limit: \033[0m");
                scanf("%d", &lowerLimit);
                printf("\033[1;31mEnter Upper Price Limit: \033[0m");
                scanf("%d", &upperLimit);
                while (getchar() != '\n'); // Clear the input buffer
            
                // Perform filtering
                numProducts = getNumProducts(products); // Get the number of products
            
                // Create a temporary array to hold filtered products
                PRODUCT *filteredProducts = malloc(numProducts * sizeof(PRODUCT));
                if (filteredProducts == NULL) {
                    printf("\033[1;31m\nMemory Allocation Failed.\033[0m\n");
                    goto intro; // Go back to the main menu
                }
            
                int filteredCount = 0;
                for (int i = 0; i < numProducts; i++) {
                    if (products[i].price >= lowerLimit && products[i].price <= upperLimit) {
                        filteredProducts[filteredCount++] = products[i];
                    }
                }
            
                if (filteredCount == 0) {
                    printf("\033[1;31m\nNo Products Found In The Specified Price Range.\033[0m\n");
                    free(filteredProducts); // Free allocated memory
                    goto intro; // Return to the main menu
                } else {
                    printf("\033[1;33m\nFiltered Products In The Price Range ₹%d - ₹%d:\033[0m\n", lowerLimit, upperLimit);
                    printRecommendations(filteredProducts, filteredCount); // Display filtered products
            
                    recommendationsMenu:
                    printf("\n\033[1;35mDo You Want To See Recommendations Based On:\033[0m\n");
                    printf("\033[1;33m1. Rating \033[0m\n");
                    printf("\033[1;32m2. Sales \033[0m\n");
                    printf("\033[1;31m3. Discount \033[0m\n");
                    printf("\033[1;34m4. Go Back to Price Filter Menu\033[0m\n");
                    printf("\033[1;31m5. Return to Main Menu\033[0m\n");
                    printf("\033[1;34mEnter Your Choice (1-5):\033[0m ");
            
                    int recommendChoice;
                    scanf("%d", &recommendChoice);
                    while (getchar() != '\n'); // Clear the input buffer
            
                    PRODUCT *recommendedProducts = malloc(filteredCount * sizeof(PRODUCT));
                    if (recommendedProducts == NULL) {
                        printf("\033[1;31m\nMemory Allocation Failed.\033[0m\n");
                        free(filteredProducts);
                        goto intro;
                    }
            
                    memcpy(recommendedProducts, filteredProducts, filteredCount * sizeof(PRODUCT)); // Copy filtered products
            
                    switch (recommendChoice) {
                        case 1:
                            qsort(recommendedProducts, filteredCount, sizeof(PRODUCT), compareByRating);
                            printf("\033[1;33m\nTop Recommended Products Based on Rating:\033[0m\n");
                            printRecommendations(recommendedProducts, filteredCount);
                            goto recommendationsMenu;
            
                        case 2:
                            qsort(recommendedProducts, filteredCount, sizeof(PRODUCT), compareBySales);
                            printf("\033[1;33m\nTop Recommended Products Based on Sales:\033[0m\n");
                            printRecommendations(recommendedProducts, filteredCount);
                            goto recommendationsMenu;
            
                        case 3:
                            qsort(recommendedProducts, filteredCount, sizeof(PRODUCT), compareByDiscount);
                            printf("\033[1;33m\nTop Recommended Products Based on Discount:\033[0m\n");
                            printRecommendations(recommendedProducts, filteredCount);
                            goto recommendationsMenu;
            
                        case 4:
                            // Go back to price filter menu
                            free(recommendedProducts);
                            free(filteredProducts);
                            printf("\n");
                            printf("\n");
                            goto priceFilterMenu;
            
                        case 5:
                            // Return to main menu
                            free(recommendedProducts);
                            free(filteredProducts);
                            printf("\033[1;31m\nReturning To The Main Menu\033[0m\n");
                            goto intro;
            
                        default:
                            printf("\033[1;31m\nInvalid Choice. Please Try Again.\033[0m\n");
                            free(recommendedProducts);
                            goto recommendationsMenu;
                    }
                }
            
                free(filteredProducts); // Free memory for filtered products
                goto intro; // Return to the main menu
            
            
            case 3: // Top trending products based on rating, sales, discount
                trendingMenu:
                printf("\033[2J\033[H"); // Clear the screen
                printf("\033[1;35m\nSort Products by:\033[0m\n");
                printf("\033[1;33m1. Rating \033[0m\n");
                printf("\033[1;32m2. Sales \033[0m\n");
                printf("\033[1;31m3. Discount \033[0m\n");
                printf("\033[1;36miv). Revert Back to Original Order\033[0m\n");
                printf("\033[1;31mv). Return to Main Menu\033[0m\n");
                printf("\033[1;34mEnter Your Choice ( 1-3 / 4(iv) / 5(v) ):\033[0m ");
                
                int sortChoice;
                scanf("%d", &sortChoice);
                while (getchar() != '\n'); // Clear the input buffer
            
                numProducts = getNumProducts(products); // Get the number of products
            
                // Backup original order
                PRODUCT *originalProducts = malloc(numProducts * sizeof(PRODUCT));
                if (originalProducts == NULL) {
                    printf("\033[1;31m\nMemory Allocation Failed.\033[0m\n");
                    break;
                }
                memcpy(originalProducts, products, numProducts * sizeof(PRODUCT));
            
                switch (sortChoice) {
                    case 1:
                        qsort(products, numProducts, sizeof(PRODUCT), compareByRating);
                        printf("\033[1;33m\nTop Trending Products Based on Rating:\033[0m\n");
                        printProducts(products);
            
                        printf("\n\033[1;31mPress 'b' to Go Back to Trending Menu:\033[0m ");
                        char back1 = getchar();
                        while (getchar() != '\n'); // Clear the input buffer
                        if (back1 != 'b') {
                            printf("\033[1;31m\nInvalid option. Returning to the trending menu.\033[0m\n");
                        }
                        goto trendingMenu;
            
                    case 2:
                        qsort(products, numProducts, sizeof(PRODUCT), compareBySales);
                        printf("\033[1;33m\nTop Trending Products Based on Sales:\033[0m\n");
                        printProducts(products);
            
                        printf("\n\033[1;31mPress 'b' to Go Back to Trending Menu:\033[0m ");
                        char back2 = getchar();
                        while (getchar() != '\n'); // Clear the input buffer
                        if (back2 != 'b') {
                            printf("\033[1;31m\nInvalid option. Returning to the trending menu.\033[0m\n");
                        }
                        goto trendingMenu;
            
                    case 3:
                        qsort(products, numProducts, sizeof(PRODUCT), compareByDiscount);
                        printf("\033[1;33m\nTop Trending Products Based on Discount:\033[0m\n");
                        printProducts(products);
            
                        printf("\n\033[1;31mPress 'b' to Go Back to Trending Menu:\033[0m ");
                        char back3 = getchar();
                        while (getchar() != '\n'); // Clear the input buffer
                        if (back3 != 'b') {
                            printf("\033[1;31m\nInvalid option. Returning to the trending menu.\033[0m\n");
                        }
                        goto trendingMenu;
            
                    case 4:
                        // Revert back to the original order
                        products = loadProducts("electronics.csv");
                        if (!products) {
                            printf("\033[1;31m\nFailed to Reload Products from File.\033[0m\n");
                            free(originalProducts);
                            goto intro; // Return to the main menu
                        }
                        printf("\033[1;33m\nReverted Back to Original Order:\033[0m\n");
                        printProducts(products);
            
                        printf("\n\033[1;31mPress 'b' to Go Back to Trending Menu:\033[0m ");
                        char back4 = getchar();
                        while (getchar() != '\n'); // Clear the input buffer
                        if (back4 != 'b') {
                            printf("\033[1;31m\nInvalid option. Returning to the trending menu.\033[0m\n");
                        }
                        goto trendingMenu;
            
                    case 5:
                        // Return to main menu
                        printf("\033[1;31m\nReturning to Main Menu...\033[0m\n");
                        free(originalProducts);
                        goto intro;
            
                    default:
                        printf("\033[1;31m\nInvalid Choice. Please Try Again.\033[0m\n");
                        free(originalProducts);
                        goto trendingMenu;
                }
      
            
                free(originalProducts); // Free memory for the backup
                goto intro; // Return to the main menu
            
            case 4://recommendations
                initializeAdjList();
                
                int choice;
                char productName[256];
                char newRecommendations[5][256];
                while(1){
                    printf("\033[1;35m\nMenu:\033[0m\n");
                    printf("\033[1;32m1. Search Recommendations For A Product\033[0m\n");
                    printf("\033[1;31m2. Exit\033[0m\n");
                    printf("\033[1;34mEnter Your Choice (1-2): \033[0m");
                    scanf("%d", &choice);
                    getchar(); // Consume newline after integer input
            
                    switch (choice) {
                        case 1:
                            // Get the product name from user
                            printf("\033[1;32m\nEnter Product Name To Search: \033[0m");
                            fgets(productName, sizeof(productName), stdin);
                            productName[strcspn(productName, "\n")] = '\0'; // Remove the newline character
                            searchRecommendations(productName);
                            break;
                        case 2:
                                // Exit the loop
                                printf("\033[1;31m\nReturning To The Menu\033[0m\n");
                                goto intro;
                        default:
                            printf("\033[1;31m\nInvalid Choice. Please Try Again\033[0m");
                            printf("\n");
                    }
                }
                                    
            case 5: // Proceed for payment
                printf("\033[2J\033[H"); // Clear the screen
                
                if (head == NULL) {
                    printf("\033[1;31m\nYour Cart Is Empty! Add Some Products Before Proceeding To Payment.\033[0m\n");
                    goto intro;
                }
                
                // Display items in the cart (the table)
                printf("\033[1;33m\nItems In Your Cart:\033[0m\n");
                printf("------------------------------------------------------------------------------------------------------------\n");
                printf("| Index | Product Name           | Price      |\n");
                printf("------------------------------------------------------------------------------------------------------------\n");
                float totalAmount = 0.0;
                LLNODE *current = head;
                int itemNo = 1;
                
                while (current != NULL) {
                    PRODUCT product = current->product;
                    printf("| %-5d | %-20s | ₹%-9.2f |\n", itemNo, product.name, product.price);
                    totalAmount += product.price;
                    current = current->next;
                    itemNo++;
                }
                printf("------------------------------------------------------------------------------------------------------------\n");
            
                // Display the total amount after the table
                printf("\n\033[1;32mTotal Amount To Be Paid: ₹%.2lf\033[0m\n", totalAmount);

                
                // Ask whether to proceed with payment
                printf("\033[1;33m\nDo You Want To Proceed With The Payment?\033[0m ( \033[1;32mY\033[0m / \033[1;31mN\033[0m ): ");
                char confirm = getchar();
                while (getchar() != '\n'); // Clear the input buffer
                
                if (confirm == 'y' || confirm == 'Y') {
                    printf("\n");
                    printf("\033[1;33mProcessing Your Request\033[0m");

                    for (int i = 0; i < 5; i++) {
                        printf(".");
                        fflush(stdout);  // Ensure the output is printed immediately
                        sleep(1);         // Sleep for 1 second
                    }
                    printf("\n");
                    printf("\n");
                    // Clear the cart after successful payment
                    while (head != NULL) {
                        head = dequeue(head);
                        goto intro;
                    }
                    
                } else {
                    printf("\n\033[1;31mPayment Cancelled. Returning To The Menu.\033[0m\n");
                    goto intro;
                }

            case 6: // View and edit cart
                viewEditMenu:
                if (head == NULL) {
                    printf("\033[1;31m\nYour Cart Is Empty! Add Some Products First.\033[0m\n");
                    goto intro;
                }
            
                printf("\033[1;32m\nEnter 'e' To Edit\033[0m || \033[1;33m'v' To View\033[0m || \033[1;31m'b' To Go Back \033[0m: ");
                back = getchar();
                while (getchar() != '\n'); // Clear the input buffer
            
                if (back == 'e') {
                    // Edit option
                    printf("\033[1;31m\nEnter Product Index To Remove: \033[0m");
                    scanf("%d", &index);
                    while (getchar() != '\n'); // Clear the input buffer
            
                    int cartSize = getCartSize(head);
                    if (index < 1 || index > cartSize) { // Check for valid index range
                        printf("\033[1;31m\nInvalid Index. Please Enter A Valid Index.\033[0m\n");
                        goto viewEditMenu; // Return to the same menu
                    } else {
                        head = deleteAt(head, index); // Remove the item at the given index
                        displayCartDetails(head);    // Display the updated cart
                        goto viewEditMenu;
                    }
            
                } else if (back == 'v') {
                    // View option
                    displayCartDetails(head); // Display cart details
                    goto viewEditMenu;        // Return to the menu after viewing
            
                } else if (back == 'b') {
                    // Go back to the main menu
                    printf("\033[1;31m\nReturning To The Main Menu.\033[0m\n");
                    goto intro;
            
                } else {
                    // Invalid input
                    printf("\033[1;31m\nInvalid Input. Please Try Again.\033[0m\n");
                    goto viewEditMenu; // Return to the same menu
                }
            
                //goto intro; // Return to the main menu after completing operations
            
            
            case 7://Exiting
            printf("\033[1;32m\nThank You For Using Our Service!!\033[0m\n");
            printf("\n");
            exit(1);
            break;

            default:
            printf("\033[1;31m\nInvalid Choice! Please Enter A Number Between 1 and 7.\033[0m\n");
            goto intro;
        }
}