/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO2
 * Experiment 13: Implementation of Binary Search Tree (BST)
 * Operations: Insertion, Searching, and Deletion
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
    if (root == NULL) {
        return createNode(key);
    }
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    } else {
        printf("Duplicate key %d ignored.\n", key);
    }
    return root;
}

BSTNode* search(BSTNode *root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    if (key < root->key) {
        return search(root->left, key);
    }
    return search(root->right, key);
}

BSTNode* findMin(BSTNode *root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

BSTNode* deleteNode(BSTNode *root, int key) {
    if (root == NULL) {
        printf("Key %d not found in BST!\n", key);
        return NULL;
    }

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            BSTNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BSTNode *temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get inorder successor (min in right subtree)
        BSTNode *temp = findMin(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
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

    printf("=================================================================\n");
    printf(" Experiment 13: BST with Insertion, Searching, and Deletion\n");
    printf("=================================================================\n");

    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);

    printf("Inserting values into BST: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        root = insert(root, values[i]);
    }
    printf("\n\nInorder traversal (Sorted): ");
    inorder(root);
    printf("\n");

    // Search tests
    int searchKeys[] = {40, 99};
    for (int i = 0; i < 2; i++) {
        BSTNode *found = search(root, searchKeys[i]);
        if (found) {
            printf("Search key %d: FOUND in tree.\n", searchKeys[i]);
        } else {
            printf("Search key %d: NOT FOUND in tree.\n", searchKeys[i]);
        }
    }

    // Deletion tests
    printf("\nDeleting leaf node (20)...\n");
    root = deleteNode(root, 20);
    printf("Inorder after deleting 20: ");
    inorder(root);
    printf("\n");

    printf("\nDeleting node with one child (30)...\n");
    root = deleteNode(root, 30);
    printf("Inorder after deleting 30: ");
    inorder(root);
    printf("\n");

    printf("\nDeleting node with two children (50 - root)...\n");
    root = deleteNode(root, 50);
    printf("Inorder after deleting 50: ");
    inorder(root);
    printf("\n");

    freeTree(root);
    return 0;
}
