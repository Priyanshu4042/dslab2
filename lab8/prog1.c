#include <stdio.h>
#include <stdlib.h>

// Define the structure for a doubly linked list node
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};


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

// Function to delete an element from the rear end of the list
void deleteFromRear(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* last = *head;
    while (last->next != NULL) {
        last = last->next;
    }
    if (last->prev != NULL) {
        last->prev->next = NULL;
    } else {
        *head = NULL; // List becomes empty
    }
    free(last);
}

// Function to insert an element at a given position
void insertAtPosition(struct Node** head, int newData, int position) {
    struct Node* newNode = createNode(newData);
    if (position == 0) {
        newNode->next = *head;
        if (*head != NULL) {
            (*head)->prev = newNode;
        }
        *head = newNode;
        return;
    }
    struct Node* current = *head;
    for (int i = 0; current != NULL && i < position - 1; i++) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Position out of bounds.\n");
        free(newNode);
        return;
    }
    newNode->next = current->next;
    newNode->prev = current;
    if (current->next != NULL) {
        current->next->prev = newNode;
    }
    current->next = newNode;
}

// Function to delete an element from a given position
void deleteFromPosition(struct Node** head, int position) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* current = *head;
    if (position == 0) {
        *head = current->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        free(current);
        return;
    }
    for (int i = 0; current != NULL && i < position; i++) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Position out of bounds.\n");
        return;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    if (current->prev != NULL) {
        current->prev->next = current->next;
    }
    free(current);
}

// Function to insert an element after another element
void insertAfter(struct Node** head, int newData, int existingData) {
    struct Node* current = *head;
    while (current != NULL && current->data != existingData) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Element %d not found.\n", existingData);
        return;
    }
    struct Node* newNode = createNode(newData);
    newNode->next = current->next;
    newNode->prev = current;
    if ( current->next != NULL) {
        current->next->prev = newNode;
    }
    current->next = newNode;
}

// Function to insert an element before another element
void insertBefore(struct Node** head, int newData, int existingData) {
    struct Node* current = *head;
    while (current != NULL && current->data != existingData) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Element %d not found.\n", existingData);
        return;
    }
    struct Node* newNode = createNode(newData);
    newNode->next = current;
    newNode->prev = current->prev;
    if (current->prev != NULL) {
        current->prev->next = newNode;
    } else {
        *head = newNode; // Update head if inserting before the first element
    }
    current->prev = newNode;
}

// Function to traverse the list
void traverseList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

// Function to reverse the list
void reverseList(struct Node** head) {
    struct Node* prev = NULL;
    struct Node* current = *head;
    struct Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        current->prev = next;
        prev = current;
        current = next;
    }
    *head = prev;
}

// Main function
int main() {
    struct Node* head = NULL;
    int choice, data, position, existingData;

    do {
        printf("\nMenu:\n");
        printf("1. Insert an element at the rear end of the list\n");
        printf("2. Delete an element from the rear end of the list\n");
        printf("3. Insert an element at a given position of the list\n");
        printf("4. Delete an element from a given position of the list\n");
        printf("5. Insert an element after another element\n");
        printf("6. Insert an element before another element\n");
        printf("7. Traverse the list\n");
        printf("8. Reverse the list\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to insert: ");
                scanf("%d", &data);
                insertAtRear(&head, data);
                break;
            case 2:
                deleteFromRear(&head);
                break;
            case 3:
                printf("Enter the element to insert: ");
                scanf("%d", &data);
                printf("Enter the position: ");
                scanf("%d", &position);
                insertAtPosition(&head, data, position);
                break;
            case 4:
                printf("Enter the position: ");
                scanf("%d", &position);
                deleteFromPosition(&head, position);
                break;
            case 5:
                printf("Enter the element to insert: ");
                scanf("%d", &data);
                printf("Enter the existing element after which to insert: ");
                scanf("%d", &existingData);
                insertAfter(&head, data, existingData);
                break;
            case 6:
                printf("Enter the element to insert: ");
                scanf("%d", &data);
                printf("Enter the existing element before which to insert: ");
                scanf("%d", &existingData);
                insertBefore(&head, data, existingData);
                break;
            case 7:
                printf("Traversing the list: ");
                traverseList(head);
                break;
            case 8:
                reverseList(&head);
                printf("List reversed.\n");
                break;
            case 9:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);

    return 0;
}