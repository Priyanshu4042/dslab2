#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};



struct node* createNode(int data) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct node* createBinaryTree() {
    int data;
    printf("Enter data for the node (or 0 to stop): ");
    scanf("%d", &data);

    if (data == 0) {
        return NULL;
    }

    struct node *newNode = createNode(data);

    printf("Creating left child of %d\n", data);
    newNode->left = createBinaryTree();
    printf("Creating right child of %d\n", data);
    newNode->right = createBinaryTree();

    return newNode;
}

void printBinaryTree(struct node *root) {
    if (root != NULL) {
        printBinaryTree(root->left);  
        printf("%d ", root->data);     
        printBinaryTree(root->right); 
    }
}

int main() {
    struct node *root = createBinaryTree(); 

    printf("In-order traversal of the binary tree: ");
    printBinaryTree(root); 
    printf("\n");

    return 0;
}
