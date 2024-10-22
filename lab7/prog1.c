#include <stdio.h>
#include <stdlib.h>

// Define the structure for a linked list node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function implementations
void insertBefore(struct Node** head, int newData, int existingData) {
    struct Node* newNode = createNode(newData);
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }
    if ((*head)->data == existingData) {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    struct Node* current = *head;
    while (current->next != NULL && current->next->data != existingData) {
        current = current->next;
    }
    if (current->next == NULL) {
        printf("Element %d not found.\n", existingData);
        free(newNode);
    } else {
        newNode->next = current->next;
        current->next = newNode;
    }
}

void insertAfter(struct Node** head, int newData, int existingData) {
    struct Node* newNode = createNode(newData);
    struct Node* current = *head;
    while (current != NULL && current->data != existingData) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Element %d not found.\n", existingData);
        free(newNode);
    } else {
        newNode->next = current->next;
        current->next = newNode;
    }
}

void deleteNode(struct Node** head, int key) {
    struct Node* temp = *head, *prev;
    if (temp != NULL && temp->data == key) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Element %d not found.\n", key);
    } else {
        prev->next = temp->next;
        free(temp);
    }
}

void traverseList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void reverseList(struct Node** head) {
    struct Node* prev = NULL;
    struct Node* current = *head;
    struct Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void sortList(struct Node** head) {
    int swapped;
    struct Node* ptr1;
    struct Node* lptr = NULL;
    if (*head == NULL)
        return;
    do {
        swapped = 0;
        ptr1 = *head;
        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void deleteAlternateNodes(struct Node** head) {
    struct Node* current = *head;
    while (current != NULL && current->next != NULL) {
        struct Node* next = current->next;
        current->next = next->next;
        free(next);
        current = current->next;
    }
}

void insertInSortedList(struct Node** head, int newData) {
    struct Node* newNode = createNode(newData);
    if (*head == NULL || (*head)->data >= newData) {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    struct Node* current = *head;
    while (current->next != NULL && current->next->data < newData) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

int main() {
    struct Node* head = NULL;
    int choice, data, existingData;

    do {
        printf("\nMenu:\n");
        printf("1. Insert before an element\n");
        printf("2. Insert after an element\n");
        printf("3. Delete an element\n");
        printf("4. Traverse the list\n");
        printf("5. Reverse the list\n");
        printf("6. Sort the list\n");
        printf("7. Delete every alternate node\n");
        printf("8. Insert in a sorted list\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to insert: ");
                scanf("%d", &data);
                printf("Enter the existing element before which to insert: ");
                scanf("%d", &existingData);
                insertBefore(&head, data, existingData);
                break;
            case 2:
                printf("Enter the element to insert: ");
                scanf("%d", &data);
                printf("Enter the existing element after which to insert: ");
                scanf("%d", &existingData);
                insertAfter(&head, data, existingData);
                break;
            case 3:
                printf("Enter the element to delete: ");
                scanf("%d", &data);
                deleteNode(&head, data);
                break;
            case 4:
                printf("Traversing the list: ");
                traverseList(head);
                break;
            case 5:
                reverseList(&head);
                printf("List reversed.\n");
                break;
            case 6:
                sortList(&head);
                printf("List sorted.\n");
                break;
            case 7:
                deleteAlternateNodes(&head);
                printf("Deleted every alternate node.\n");
                break;
            case 8:
                printf("Enter the element to insert in sorted order: ");
                scanf("%d", &data);
                insertInSortedList(&head, data);
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