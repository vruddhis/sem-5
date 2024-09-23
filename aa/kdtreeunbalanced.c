#include <stdio.h>
#include <stdlib.h>

typedef struct KDNode {
    int *point;             
    int depth;               
    struct KDNode *left;     
    struct KDNode *right;    
} KDNode;

KDNode* createNode(int *point, int depth, int k) {
    KDNode *newNode = (KDNode*)malloc(sizeof(KDNode));
    newNode->point = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        newNode->point[i] = point[i];
    }
    newNode->depth = depth;
    newNode->left = newNode->right = NULL;
    return newNode;
}

KDNode* insert(KDNode *root, int *point, int k) {
    if (root == NULL) {
        return createNode(point, 0, k);
    }

    int i = root->depth % k; 

    if (point[i] <= root->point[i]) {
        if (root->left == NULL) {
            root->left = createNode(point, root->depth + 1, k);
        } else {
            root->left = insert(root->left, point, k);
        }
    } else {
        if (root->right == NULL) {
            root->right = createNode(point, root->depth + 1, k);
        } else {
            root->right = insert(root->right, point, k);
        }
    }

    return root;
}

void printInorderKDTree(KDNode *root, int k) {

    if (root != NULL) {
        printInorderKDTree(root->left, k);
        for (int i = 0; i < k; i++) {
            printf("%d ", root->point[i]);
        }
        printf("\n");
        printInorderKDTree(root->right, k);
    }
}

int main() {
    int k = 2;
    KDNode *root = NULL;

    int point1[] = {3, 6};
    int point2[] = {17, 15};
    int point3[] = {13, 15};
    int point4[] = {6, 12};
    int point5[] = {9, 1};
    int point6[] = {2, 7};
    int point7[] = {10, 19};

    root = insert(root, point1, k);
    root = insert(root, point2, k);
    root = insert(root, point3, k);
    root = insert(root, point4, k);
    root = insert(root, point5, k);
    root = insert(root, point6, k);
    root = insert(root, point7, k);

    printInorderKDTree(root, k);

    return 0;
}
