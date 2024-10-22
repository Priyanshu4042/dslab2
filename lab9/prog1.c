#include <stdio.h>
#include <stdlib.h>

// Define the structure for a doubly linked circular list node
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Function prototypes
struct Node* createNode(int data);
void insertIntoCircularList(struct Node** head, int newData);
void deleteFromCircularList(struct Node** head, int key);
void traverseCircularList(struct Node* head);

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = newNode; // Point to itself
    newNode->prev = newNode; // Point to itself
    return newNode;
}

// Function to insert an element into a doubly linked circular list
void insertIntoCircularList(struct Node** head, int newData) {
    struct Node* newNode = createNode(newData);
    if (*head == NULL) {
        *head = newNode; // If the list is empty, set head to new node
    } else {
        struct Node* tail = (*head)->prev; // Get the last node
        tail->next = newNode; // Link the last node to new node
        newNode->prev = tail; // Link new node back to last node
    }
    newNode->next = *head; // Link new node to head
    (*head)->prev = newNode; // Link head back to new node
}

// Function to delete an element from a doubly linked circular list
void deleteFromCircularList(struct Node** head, int key) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }
    
    struct Node* current = *head;
    do {
        if (current->data == key) {
            if (current->next == current) { // Only one node in the list
                free(current);
                *head = NULL; // List becomes empty
                return;
            } else {
                struct Node* prevNode = current->prev;
                struct Node* nextNode = current->next;
                prevNode->next = nextNode; // Link previous node to next node
                nextNode->prev = prevNode; // Link next node back to previous node
                if (current == *head) {
                    *head = nextNode; // Update head if necessary
                }
                free(current);
                return;
            }
        }
        current = current->next;
    } while (current != *head);
    
    printf("Element %d not found in the list.\n", key);
}

// Function to traverse the circular list
void traverseCircularList(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* current = head;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);
    printf("\n");
}

// Main function
int main() {
    struct Node* head = NULL;
    int choice, data;

    do {
        printf("\nMenu:\n");
        printf("1. Insert an element into the circular list\n");
        printf("2. Delete an element from the circular list\n");
        printf("3. Traverse the circular list\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to insert: ");
                scanf("%d", &data);
                insertIntoCircularList(&head, data);
                break;
            case 2:
                printf("Enter the element to delete: ");
                scanf("%d", &data);
                deleteFromCircularList(&head, data);
                break;
            case 3:
                printf("Traversing the circular list: ");
                traverseCircularList(head);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}