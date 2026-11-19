/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO2
 * Experiment 15: Implementation of AVL Tree (Self-Balancing BST)
 * Operations: Insertion with LL, RR, LR, RL Rotations, Inorder Traversal
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(AVLNode *node) {
    if (node == NULL) return 0;
    return node->height;
}

int getBalanceFactor(AVLNode *node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

AVLNode* createNode(int key) {
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    if (!node) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // New node initially at height 1
    return node;
}

// Right Rotation (for LL imbalance)
AVLNode* rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x; // New root
}

// Left Rotation (for RR imbalance)
AVLNode* leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; // New root
}

AVLNode* insertAVL(AVLNode *node, int key) {
    // 1. Perform normal BST insertion
    if (node == NULL) {
        return createNode(key);
    }

    if (key < node->key) {
        node->left = insertAVL(node->left, key);
    } else if (key > node->key) {
        node->right = insertAVL(node->right, key);
    } else {
        return node; // Duplicate keys not allowed
    }

    // 2. Update height of current node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // 3. Get balance factor to check if node became unbalanced
    int balance = getBalanceFactor(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key) {
        printf("  [LL Imbalance at %d -> Applying Right Rotation]\n", node->key);
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && key > node->right->key) {
        printf("  [RR Imbalance at %d -> Applying Left Rotation]\n", node->key);
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        printf("  [LR Imbalance at %d -> Applying Left-Right Rotation]\n", node->key);
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        printf("  [RL Imbalance at %d -> Applying Right-Left Rotation]\n", node->key);
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inorder(AVLNode *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d(BF=%d, H=%d) ", root->key, getBalanceFactor(root), root->height);
        inorder(root->right);
    }
}

void freeAVL(AVLNode *root) {
    if (root == NULL) return;
    freeAVL(root->left);
    freeAVL(root->right);
    free(root);
}

int main(void) {
    AVLNode *root = NULL;

    printf("=====================================================\n");
    printf(" Experiment 15: AVL Tree (Self-Balancing BST)\n");
    printf("=====================================================\n");

    int keys[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        printf("Inserting key %d:\n", keys[i]);
        root = insertAVL(root, keys[i]);
        printf("Current Inorder: ");
        inorder(root);
        printf("\n\n");
    }

    printf("Final AVL Tree Root: %d (Height: %d)\n", root->key, root->height);
    freeAVL(root);
    return 0;
}
