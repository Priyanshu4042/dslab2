#include <stdio.h>
#include <stdlib.h>

// Define the structure for a binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function prototypes
struct Node* createNode(int data);
void inorderTraversal(struct Node* root);
void postorderTraversal(struct Node* root);
void preorderTraversal(struct Node* root);
struct Node* findParent(struct Node* root, int key);
int findDepth(struct Node* root);
void printAncestors(struct Node* root, int key);
int countLeafNodes(struct Node* root);

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// In-order traversal (Iterative)
void inorderTraversal(struct Node* root) {
    struct Node* stack[100]; // Stack for iterative traversal
    int top = -1;
    struct Node* current = root;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current; // Push current node to stack
            current = current->left; // Move to left child
        }
        current = stack[top--]; // Pop from stack
        printf("%d ", current->data); // Visit the node
        current = current->right; // Move to right child
    }
    printf("\n");
}

// Post-order traversal (Iterative)
void postorderTraversal(struct Node* root) {
    struct Node* stack[100];
    int top = -1;
    struct Node* current = root;
    struct Node* lastVisited = NULL;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current; // Push current node to stack
            current = current->left; // Move to left child
        }
        current = stack[top]; // Peek the top node
        if (current->right == NULL || current->right == lastVisited) {
            printf("%d ", current->data); // Visit the node
            lastVisited = current; // Mark this node as last visited
            top--; // Pop from stack
            current = NULL; // Set current to NULL
        } else {
            current = current->right; // Move to right child
        }
    }
    printf("\n");
}

// Pre-order traversal (Iterative)
void preorderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top != -1) {
        struct Node* current = stack[top--]; // Pop from stack
        printf("%d ", current->data); // Visit the node

        // Push right and then left child to stack
        if (current->right != NULL) {
            stack[++top] = current->right;
        }
        if (current->left != NULL) {
            stack[++top] = current->left;
        }
    }
    printf("\n");
}

// Function to find the parent of a given key
struct Node* findParent(struct Node* root, int key) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) {
        return NULL; // No parent found
    }
    if ((root->left != NULL && root->left->data == key) || 
        (root->right != NULL && root->right->data == key)) {
        return root; // Parent found
    }
    struct Node* leftParent = findParent(root->left, key);
    if (leftParent != NULL) {
        return leftParent; // Return parent from left subtree
    }
    return findParent(root->right, key); // Search in right subtree
}

// Function to find the depth of the tree
int findDepth(struct Node* root) {
    if (root == NULL) {
        return 0; // Depth of empty tree is 0
    }
    int leftDepth = findDepth(root->left);
    int rightDepth = findDepth(root->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1; // Return max depth
}

// Function to print ancestors of a given key
 void printAncestors(struct Node* root, int key) {
    if (root == NULL) return;

    if (root->data == key) {
        return; // Key found, no ancestors to print
    }
    if ((root->left != NULL && root->left->data == key) || 
        (root->right != NULL && root->right->data == key)) {
        printf("%d ", root->data); // Print the parent
    }
    printAncestors(root->left, key);
    printAncestors(root->right, key);
}

// Function to count leaf nodes
int countLeafNodes(struct Node* root) {
    if (root == NULL) {
        return 0; // No leaf nodes in an empty tree
    }
    if (root->left == NULL && root->right == NULL) {
        return 1; // This node is a leaf node
    }
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

// Main function
int main() {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("In-order Traversal: ");
    inorderTraversal(root);

    printf("Post-order Traversal: ");
    postorderTraversal(root);

    printf("Pre-order Traversal: ");
    preorderTraversal(root);

    struct Node* parent = findParent(root, 5);
    if (parent != NULL) {
        printf("Parent of 5 is %d\n", parent->data);
    } else {
        printf("No parent found for 5\n");
    }

    printf("Depth of the tree: %d\n", findDepth(root));

    printf("Ancestors of 5: ");
    printAncestors(root, 5);
    printf("\n");

    printf("Number of leaf nodes: %d\n", countLeafNodes(root));

    return 0;
}