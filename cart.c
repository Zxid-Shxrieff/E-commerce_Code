#include "cart.h"


LLNODE *enqueue(LLNODE *head, PRODUCT *products, int index) {
  PRODUCT product = products[index];
  if (head == NULL) {
    LLNODE *newnode = (LLNODE *)malloc(sizeof(LLNODE));
    newnode->next = NULL;
    newnode->product = product;
    head = newnode;
  } else {
    LLNODE *temp = head;
    while (temp->next) {
      temp = temp->next;
    }
    temp->next = (LLNODE *)malloc(sizeof(LLNODE));
    temp->next->next = NULL;
    temp->next->product = product;
  }
  return head;
}
LLNODE *deleteAt(LLNODE *head, int index) {
    if (head == NULL) {
        printf("🛒Cart Is Empty\n");
        return NULL;
    }

    LLNODE *temp = head;
    int currentIndex = 1;

    // Special case for deleting the first item
    if (index == 1) {
        printf("\n%s Is Removed From Cart.\n", head->product.name);
        head = head->next;
        free(temp); // Free the removed node
        printf("\033[1;32m\nProduct Removed Successfully!\033[0m\n");
    } else {
        // Traverse the list to find the item at the given index
        while (temp != NULL && currentIndex < index - 1) {
            temp = temp->next;
            currentIndex++;
        }

        // If temp is NULL or the next node is NULL, index is invalid
        if (temp == NULL || temp->next == NULL) {
            printf("\nInvalid Index. Please Enter A Valid Index.\n");
            return head;
        }

        // Remove the node at the specified index
        LLNODE *nodeToDelete = temp->next;
        temp->next = temp->next->next;
        printf("\n%s Is Removed From Cart.\n", nodeToDelete->product.name);
        free(nodeToDelete); // Free the removed node
    }

    if (head == NULL) {
        printf("\033[1;31m\nYour Cart Is Empty Now.\033[0m\n");
    }

    return head;
}
void viewCart(LLNODE *head) {
    LLNODE *temp = head;
    printf("--------------------------------------------------------------"
           "---------------------------------------------------------------------------\n");
    printf("| %-5s | %-20s | %-40s | %-7s | %-10s | %-10s | %-10s | %-10s |\n",
           "Index", "Name", "Description", "Rating", "Price", "Discount", "Sales",
           "Final Price");
    printf("--------------------------------------------------------------"
           "---------------------------------------------------------------------------\n");
    float sum = 0;
    int currentIndex = 1;  // Ensure correct indexing starts from 1
    while (temp) {
        sum += temp->product.price * (1 - (temp->product.discount) / 100);
        printf("| %-5d | %-20s | %-40s | %-7.2f | %-10.2f | %-10.2f | %-10d | %-10.2f |\n",
               currentIndex, temp->product.name, temp->product.description, temp->product.rating, temp->product.price, temp->product.discount, temp->product.sales,
               temp->product.price * (1 - (temp->product.discount) / 100));
        temp = temp->next;
        currentIndex++;  // Increment index
    }

    // Print the footer
    printf("---------------------------------------------------------------------"
           "-------------------------------------------------------------------\n");
    printf("\033[1;32mYour Total Price Is : %.2f\033[0m\n", sum);
}
LLNODE *dequeue(LLNODE *head) {
    if (head == NULL) {
        printf("\033[1;31mCart Is Empty!\033[0m\n");
        return head;
    }

    viewCart(head);  // Display the current cart before payment
    printf("\033[1;33m\nProceed For Payment?\033[0m ( \033[1;32mY\033[0m / \033[1;31mN\033[0m ): ");
    char choice;
    scanf(" %c", &choice);  // Add a space before %c to skip any leftover newline character

    if (choice == 'y' || choice == 'Y') {
        printf("\033[1;32m\nPayment Successful!\033[0m\n");
        printf("\n");
        printf("\033[1;32mProcessing\033[0m");

        // Add a small delay to simulate payment processing
        for (int i = 0; i < 5; i++) {
            printf(".");
            fflush(stdout);  // Ensure the output is printed immediately
            sleep(1);         // Sleep for 1 second
        }
        printf("\n");

        // Process each item in the cart (delete and simulate product processing)
        LLNODE *temp = head;
        printf("\n");
        while (temp != NULL) {
            printf("%s Is Processed.\n", temp->product.name);  // Simulate product processing
            temp = temp->next;
        }

        // Clear the cart after successful payment
        while (head != NULL) {
            LLNODE *temp = head;
            head = head->next;
            free(temp);  // Free the first item in the list
        }
        printf("\033[\n1;32mCart Cleared Successfully After Payment.\033[0m\n");
        printf("\033[1;32mProcessed Successfully! Thank You For Shopping With Us.\033[0m\n");
        printf("\n");
    } else {
        printf("\033[1;31m\nPayment Canceled. Returning To The Menu.\033[0m\n");
    }
    return head;
}