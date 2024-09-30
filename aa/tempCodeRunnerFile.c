while (x != *root && x->colour == 'B') {
        if (x == x->parent->left_child) {
            Node* s = x->parent->right_child;
            
            if (s->colour == 'R') {
                s->colour = 'B';
                x->parent->colour = 'R';
                left_rotate(root, x->parent);
                s = x->parent->right_child;
            }
            
            if (s->left_child->colour == 'B' && s->right_child->colour == 'B') {
                s->colour = 'R';
                x = x->parent;
            } else {
                if (s->right_child->colour == 'B') {
                    s->left_child->colour = 'B';
                    s->colour = 'R';
                    right_rotate(root, s);
                    s = x->parent->right_child;
                }
                
                s->colour = x->parent->colour;
                x->parent->colour = 'B';
                s->right_child->colour = 'B';
                left_rotate(root, x->parent);
                x = *root;
            }
        } else {
            Node* s = x->parent->left_child;
            
            if (s->colour == 'R') {
                s->colour = 'B';
                x->parent->colour = 'R';
                right_rotate(root, x->parent);
                s = x->parent->left_child;
            }
            
            if (s->right_child->colour == 'B' && s->left_child->colour == 'B') {
                s->colour = 'R';
                x = x->parent;
            } else {
                if (s->left_child->colour == 'B') {
                    s->right_child->colour = 'B';
                    s->colour = 'R';
                    left_rotate(root, s);
                    s = x->parent->left_child;
                }
                
                s->colour = x->parent->colour;
                x->parent->colour = 'B';
                s->left_child->colour = 'B';
                right_rotate(root, x->parent);
                x = *root;
            }
        }
    }
    x->colour = 'B';
}


Node* delete_node(Node* root, Node* z) {
    Node* y = z;
    Node* x;
    char y_original_colour = y->colour;

    if (z->left_child == NULL) {
        x = z->right_child;

        if (z->parent == NULL) {
            root = z->right_child;  
        } else if (z == z->parent->left_child) {
            z->parent->left_child = z->right_child;
        } else {
            z->parent->right_child = z->right_child;
        }
        if (x != NULL) {
            x->parent = z->parent;
        }
    } else if (z->right_child == NULL) {
        x = z->left_child;
        if (z->parent == NULL) {
            root = z->left_child;  
        } else if (z == z->parent->left_child) {
            z->parent->left_child = z->left_child;
        } else {
            z->parent->right_child = z->left_child;
        }
        if (x != NULL) {
            x->parent = z->parent;
        }
    } else {
        y = minimum(z->right_child);
        y_original_colour = y->colour;
        x = y->right_child;

        if (y->parent == z) {
            if (x != NULL) x->parent = y; 
        } else {
            
            if (y->parent != NULL) {
                if (y == y->parent->left_child) {
                    y->parent->left_child = y->right_child;
                } else {
                    y->parent->right_child = y->right_child;
                }
            }
            if (y->right_child != NULL) {
                y->right_child->parent = y->parent;
            }
            y->right_child = z->right_child;
            y->right_child->parent = y;
        }

        if (z->parent == NULL) {
            root = y;  
        } else if (z == z->parent->left_child) {
            z->parent->left_child = y;
        } else {
            z->parent->right_child = y;
        }
        y->parent = z->parent;
        y->left_child = z->left_child;
        y->left_child->parent = y;
        y->colour = z->colour;
    }

    if (y_original_colour == 'B') {
        delete_fix(&root, x);  
    }

    return root; 
}

Node* delete(Node* root, int val) {
    Node* node_to_delete = search(root, val);  

    if (node_to_delete == NULL) {
        printf("Node with value %d not found.\n", val);
        return root; 
    }

    return delete_node(root, node_to_delete);  
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

    int delete_values[] = {15, 30, 10};  
    
    

    for (int j = 0; j < 3; j++) {
        printf("After deleting %d", delete_values[j]);
        
        root = delete(root, delete_values[j]);

        printf(" Inorder: ");
        inorder(root);
        printf("\n");

        printf(" Postorder: ");
        postorder(root);
        printf("\n");
    }

    return 0;
}







