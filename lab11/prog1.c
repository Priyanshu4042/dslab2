#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
  int data ;
  struct node *left,*right;
};

struct node* createNode(int element) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = element;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct node* insert(struct node *root, int element) {
    if (root == NULL) {
        return createNode(element); 
    }
    if (element < root->data) {
        root->left = insert(root->left, element); 
    } else {
        root->right = insert(root->right, element); 
    }
    return root; 
}

void printBinaryTree(struct node *root) {
    if (root != NULL) {
        printBinaryTree(root->left);  
        printf("%d ", root->data);     
        printBinaryTree(root->right); 
    }
}

bool search (struct node *root , int item ){
    if (root == NULL) {printf("BST empty"); return false ;}
    else if (item == root->data) {
       return true ;
    }
    else if (item >root->data ) {
        if (root->right != NULL){
            search(root->right ,item);
        }else{
            printf("item not found");
            return false;
        }
    } 
    else if (item < root->data ) {
        if (root->left != NULL){
            search(root->left ,item);
        }else{
            printf("item not found");
            return false;
        }
    }  
}

struct node* minValueNode(struct node* node) {
    struct node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

struct node* delete(struct node *root, int item) {
    if (root == NULL) {
        printf("Item not found\n");
        return root;
    }

    if (item < root->data) {
        root->left = delete(root->left, item);
    } else if (item > root->data) {
        root->right = delete(root->right, item);
    } else {
        
        if (root->left == NULL) {
            struct node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

       
        struct node *temp = minValueNode(root->right);
        root->data = temp->data; 
        root->right = delete(root->right, temp->data);
    }
    return root;
}

int main(){
  struct node *root = NULL;
  int choice = 1 ;
  while (true){
    printf("Enter 0 to exit or enter element ");
    scanf("%d", &choice );
    if (choice == 0) break;
    root = insert(root,choice) ;
  }
  printBinaryTree(root); 
  printf("\n %d",search(root,9) );
  printf("\n");
  return 0;
}
