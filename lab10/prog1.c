#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};


struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


void inorderTraversal(struct Node* root) {
    struct Node* stack[100]; 
    int top = -1;
    struct Node* current = root;

    while (true) {
        while (current != NULL) {
            stack[++top] = current; 
            current = current->left; 
        }

        if (top == -1) break;

        current = stack[top--]; 
        printf("%d ", current->data); 

        current = current->right; 
    }
}


void postorderTraversal(struct Node* root) {
    struct Node* stack[100];
    int top = -1;
    struct Node* current = root;
    struct Node* lastVisited = NULL;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current; 
            current = current->left; 
        }
        current = stack[top]; 
        if (current->right == NULL || current->right == lastVisited) {
            printf("%d ", current->data); 
            lastVisited = current; 
            top--; 
            current = NULL; 
        } else {
            current = current->right; 
        }
    }
    
}


void preorderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top != -1) {
        struct Node* current = stack[top--]; 
        printf("%d ", current->data); 

    
        if (current->right != NULL) {
            stack[++top] = current->right;
        }
        if (current->left != NULL) {
            stack[++top] = current->left;
        }
    }

}

struct Node* findParent(struct Node* root, int key) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) {
        return NULL; 
    }
    if ((root->left != NULL && root->left->data == key) || 
        (root->right != NULL && root->right->data == key)) {
        return root; 
    }
    struct Node* leftParent = findParent(root->left, key);
    if (leftParent != NULL) {
        return leftParent; 
    }
    return findParent(root->right, key); 
}

int findDepth(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftDepth = findDepth(root->left);
    int rightDepth = findDepth(root->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1; 
}

 void printAncestors(struct Node* root, int key) {
    if (root == NULL) return;

    if (root->data == key) {
        return; 
    }
    if ((root->left != NULL && root->left->data == key) || 
        (root->right != NULL && root->right->data == key)) {
        printf("%d ", root->data); 
    }
    printAncestors(root->left, key);
    printAncestors(root->right, key);
}

int countLeafNodes(struct Node* root) {
    if (root == NULL) {
        return 0; 
    }
    if (root->left == NULL && root->right == NULL) {
        return 1; 
    }
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

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