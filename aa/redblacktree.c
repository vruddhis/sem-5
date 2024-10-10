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
    return *root;    
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
    return *root;   
}

int is_root(Node* node) {
    return (node != NULL && node->parent == NULL);
}


Node* insert_node(Node* root, int x) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = x;
    newNode->colour = 'R'; 
    newNode->left_child = NULL;
    newNode->right_child = NULL;
    newNode->parent = NULL;

    if (root == NULL) {
        newNode->colour = 'B';
        return newNode;
    }

    Node* curr = root;
    Node* parent = NULL;
    
    while (curr != NULL) {
        parent = curr;
        if (x < curr->val) {
            curr = curr->left_child;
        } else {
            curr = curr->right_child;
        }
    }
    newNode->parent = parent;
    if (x < parent->val) {
        parent->left_child = newNode;
    } else {
        parent->right_child = newNode;
    }

    while (newNode != root && newNode->parent->colour == 'R') {
        Node* grandparent = newNode->parent->parent;

        if (newNode->parent == grandparent->left_child) { 
            Node* uncle = grandparent->right_child;

            if (uncle != NULL && uncle->colour == 'R') { // Case 1
                grandparent->colour = 'R';
                newNode->parent->colour = 'B';
                uncle->colour = 'B';
              
            } else {
                if (newNode == newNode->parent->right_child) { // Case 2A
                    newNode = newNode->parent;
                    left_rotate(&root, newNode);
                }
                // Case 3A
                newNode->parent->colour = 'B';
                grandparent->colour = 'R';
                right_rotate(&root, grandparent);
            }
        } else { 
            Node* uncle = grandparent->left_child;

            if (uncle != NULL && uncle->colour == 'R') { // Case 1
                grandparent->colour = 'R';
                newNode->parent->colour = 'B';
                uncle->colour = 'B';
                
            } else {
                if (newNode == newNode->parent->left_child) { // Case 2B
                    newNode = newNode->parent;
                    right_rotate(&root, newNode);
                }
                // Case 3B
                newNode->parent->colour = 'B';
                grandparent->colour = 'R';
                left_rotate(&root, grandparent);
            }
        }
    }

    root->colour = 'B'; 
    return root;
}

Node* search(Node* root, int key) {
    Node* curr = root;
    while (curr != NULL) {
        if (key == curr->val) {
            return curr;
        } else if (key < curr->val) {
            curr = curr->left_child;
        } else {
            curr = curr->right_child;
        }
    }
    return NULL;
}
Node* inorder_successor(Node* root, Node* x){
    if (x->right_child != NULL) {
        Node* curr = x->right_child;
        while (curr->left_child != NULL) {
            curr = curr->left_child;
        }
        return curr;
    }

    return NULL;
}

Node* delete(Node* root, int value){
    if (search(root, value) == NULL){return root;}
    
    Node* to_delete = search(root, value);
    Node* y = to_delete;
    Node* x;
    char original_colour = y->colour;
    Node* successor = inorder_successor(root, to_delete);


}

void inorder(Node* root) {
    if (root == NULL) {
        return;
    }

    inorder(root->left_child); 
    printf("%d (%c) ", root->val, root->colour); 
    inorder(root->right_child); 
}

void postorder(Node* root) {
    if (root == NULL) {
        return;
    }

    postorder(root->left_child); 
    postorder(root->right_child); 
    printf("%d (%c) ", root->val, root->colour); 
}

int main() {
    Node* root = NULL;
    int values[] = {10, 20, 30, 15, 25, 5, 1};  

    for (int i = 0; i < 7; i++) {
        printf("After inserting %d:", values[i]);
        root = insert_node(root, values[i]);

        printf("Inorder: ");
        inorder(root);
        printf("\n");

        printf("Postorder: ");
        postorder(root);
        printf("\n");
    }
    return 0;
}