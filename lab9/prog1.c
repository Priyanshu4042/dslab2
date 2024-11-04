#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};


struct Node* createNode(int data);
void insertIntoCircularList(struct Node** head, int newData);
void deleteFromCircularList(struct Node** head, int key);
void traverseCircularList(struct Node* head);


struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = newNode; 
    newNode->prev = newNode; 
    return newNode;
}


void insertIntoCircularList(struct Node** head, int newData) {
    struct Node* newNode = createNode(newData);
    if (*head == NULL) {
        *head = newNode; 
    } else {
        struct Node* tail = (*head)->prev;
        tail->next = newNode; 
        newNode->prev = tail; 
    }
    newNode->next = *head; 
    (*head)->prev = newNode; 
}


void deleteFromCircularList(struct Node** head, int key) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }
    
    struct Node* current = *head;
    do {
        if (current->data == key) {
            if (current->next == current) {
                free(current);
                *head = NULL;
                return;
            } else {
                struct Node* prevNode = current->prev;
                struct Node* nextNode = current->next;
                prevNode->next = nextNode; 
                nextNode->prev = prevNode; 
                if (current == *head) {
                    *head = nextNode; 
                }
                free(current);
                return;
            }
        }
        current = current->next;
    } while (current != *head);
    
    printf("Element %d not found in the list.\n", key);
}


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
