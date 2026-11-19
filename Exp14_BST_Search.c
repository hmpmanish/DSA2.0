/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO2
 * Experiment 14: Searching in Binary Search Tree (Recursive vs Iterative)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BSTNode {
    int key;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

BSTNode* createNode(int key) {
    BSTNode *node = (BSTNode *)malloc(sizeof(BSTNode));
    if (!node) {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BSTNode* insert(BSTNode *root, int key) {
    if (root == NULL) return createNode(key);
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    return root;
}

// Recursive Search with comparison step count
BSTNode* searchRecursive(BSTNode *root, int key, int *comparisons) {
    if (root == NULL) {
        return NULL;
    }
    (*comparisons)++;
    if (root->key == key) {
        return root;
    }
    if (key < root->key) {
        return searchRecursive(root->left, key, comparisons);
    }
    return searchRecursive(root->right, key, comparisons);
}

// Iterative Search with comparison step count
BSTNode* searchIterative(BSTNode *root, int key, int *comparisons) {
    BSTNode *curr = root;
    while (curr != NULL) {
        (*comparisons)++;
        if (curr->key == key) {
            return curr;
        }
        if (key < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return NULL;
}

void inorder(BSTNode *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void freeTree(BSTNode *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    BSTNode *root = NULL;
    int dataset[] = {45, 15, 79, 10, 20, 55, 90, 12, 50};
    int n = sizeof(dataset) / sizeof(dataset[0]);

    printf("=================================================================\n");
    printf(" Experiment 14: Searching in Binary Search Tree\n");
    printf("=================================================================\n");

    for (int i = 0; i < n; i++) {
        root = insert(root, dataset[i]);
    }

    printf("BST Inorder Traversal: ");
    inorder(root);
    printf("\n\n");

    int testKeys[] = {50, 12, 79, 100};
    int numTests = sizeof(testKeys) / sizeof(testKeys[0]);

    for (int i = 0; i < numTests; i++) {
        int key = testKeys[i];
        int compRec = 0;
        int compIter = 0;

        BSTNode *resRec = searchRecursive(root, key, &compRec);
        BSTNode *resIter = searchIterative(root, key, &compIter);

        printf("Searching for Key [%3d]:\n", key);
        if (resRec != NULL && resIter != NULL) {
            printf("  -> Status: FOUND in BST!\n");
        } else {
            printf("  -> Status: NOT FOUND in BST!\n");
        }
        printf("  -> Recursive Comparisons: %d\n", compRec);
        printf("  -> Iterative Comparisons: %d\n\n", compIter);
    }

    freeTree(root);
    return 0;
}
