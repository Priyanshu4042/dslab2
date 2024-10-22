#include <stdio.h>
#include <stdlib.h>

// Define the structure for a doubly linked list node
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Function prototypes
struct Node* createNode(int data);
void insertAtRear(struct Node** head, int newData);
void concatenateLists(struct Node** X1, struct Node** X2);
void traverseList(struct Node* node);

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert an element at the rear end of the list
void insertAtRear(struct Node** head, int newData) {
    struct Node* newNode = createNode(newData);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* last = *head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
    newNode->prev = last;
}

// Function to concatenate two doubly linked lists
void concatenateLists(struct Node** X1, struct Node** X2) {
    if (*X1 == NULL) {
        *X1 = *X2; // If X1 is empty, point it to X2
    } else if (*X2 != NULL) {
        struct Node* last = *X1;
        while (last->next != NULL) {
            last = last->next; // Traverse to the end of X1
        }
        last->next = *X2; // Link the last node of X1 to the head of X2
        (*X2)->prev = last; // Set the previous pointer of X2's head to last
    }
}

// Function to traverse the list
void traverseList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

// Main function
int main() {
    struct Node* X1 = NULL;
    struct Node* X2 = NULL;

    // Insert elements into the first list (X1)
    insertAtRear(&X1, 1);
    insertAtRear(&X1, 2);
    insertAtRear(&X1, 3);
    
    // Insert elements into the second list (X2)
    insertAtRear(&X2, 4);
    insertAtRear(&X2, 5);
    insertAtRear(&X2, 6);

    printf("List X1 before concatenation: ");
    traverseList(X1);
    
    printf("List X2 before concatenation: ");
    traverseList(X2);

    // Concatenate X1 and X2
    concatenateLists(&X1, &X2);

    printf("List X1 after concatenation: ");
    traverseList(X1);

    return 0;
}