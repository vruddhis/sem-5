#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int val;                  
    struct Node* parent;       
    struct Node* left_child;   
    struct Node* right_child;  
    char colour;               
} Node;

Node* right_rotate(Node** root, Node* x) {
    Node* y = x->left_child;  
    x->left_child = y->right_child; 
    
    if (y->right_child != NULL) {
        y->right_child->parent = x;  
    }
    
    y->parent = x->parent;  
    
    if (x->parent == NULL) {
        *root = y;  
    } else if (x == x->parent->right_child) {
        x->parent->right_child = y;  
    } else {
        x->parent->left_child = y;   
    }
    
    y->right_child = x;  
    x->parent = y;   
    return root;    
}

Node* left_rotate(Node** root, Node* x) {
    Node* y = x->right_child;  
    x->right_child = y->left_child;  
    
    if (y->left_child != NULL) {
        y->left_child->parent = x;  
    }
    
    y->parent = x->parent;  
    
    if (x->parent == NULL) {
        *root = y;  
    } else if (x == x->parent->left_child) {
        x->parent->left_child = y;  
    } else {
        x->parent->right_child = y; 
    }
    
    y->left_child = x;  
    x->parent = y;  
    return root;   
}

int is_root(Node* node) {
    return (node != NULL && node->parent == NULL);
}

Node* insert_node(Node* root, int x){
    Node *newNode = (Node*)malloc(sizeof(Node));
    Node* parent; Node* grandparent; Node* uncle; Node* temp;
    char uncle_color;
    newNode -> val = x;
    newNode -> colour = 'R';
    newNode -> left_child = NULL;
    newNode -> right_child = NULL;
    if (root == NULL){
        root = newNode;
        root -> colour = 'B';
        return root;
    }
    Node* curr = root;
    while (curr != NULL){
        if (curr -> val > x){
            if(curr->right_child==NULL){
                curr->right_child = newNode;
                parent = curr;
                grandparent = curr -> parent;
                if (parent == grandparent -> left_child){
                    uncle = grandparent -> right_child;
                }
                else{
                    uncle = grandparent -> left_child;
                }
                if (uncle == NULL){
                    uncle_color = 'B';
                }
                else{
                    uncle_color = uncle -> colour;
                }
                if (uncle_color == 'R'){
                    grandparent -> colour = 'R';
                    parent -> colour = 'B';
                    uncle -> colour = 'B';
                    if (is_root(grandparent)){
                        grandparent -> colour = 'B';
                    }
                    return root;
                } //case 1 over
                else{ 
                    if (parent == grandparent -> left_child && newNode == parent -> right_child){// case 2A
                        left_rotate(root, parent);
                        temp = parent;
                        parent = newNode;
                        newNode = temp;
                        //go to case 3
                    }
                    if (parent == grandparent -> right_child && newNode == parent -> left_child){//case 2B
                        right_rotate(root, parent);
                        temp = parent;
                        parent = newNode;
                        newNode = temp;
                        //go to case 3
                    }
                }
                //case 3
                if (parent == grandparent -> left_child && newNode == parent -> left_child) { // Case 3A: Left-Left
                    right_rotate(&root, grandparent);
                    parent->colour = 'B';
                    grandparent->colour = 'R';
                } else if (parent == grandparent -> right_child && newNode == parent -> right_child) { // Case 3B: Right-Right
                    left_rotate(&root, grandparent);
                    parent->colour = 'B';
                    grandparent->colour = 'R';
                }
                return root;
                
            }
            else{
                curr = curr->right_child;
            }
            }
        else{
                if(curr -> left_child == NULL){
                    curr -> left_child = newNode;
                }
                else{
                    curr = curr -> left_child;
                }
        }
    }
    }









