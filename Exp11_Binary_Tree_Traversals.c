/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO2
 * Experiment 11: Binary Tree Traversals (Preorder, Inorder, Postorder)
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createNode(int value) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (!node) {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Preorder: Root -> Left -> Right
void preorder(TreeNode *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Inorder: Left -> Root -> Right
void inorder(TreeNode *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Postorder: Left -> Right -> Root
void postorder(TreeNode *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void freeTree(TreeNode *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    printf("=====================================================\n");
    printf(" Experiment 11: Preorder, Inorder, Postorder Traversals\n");
    printf("=====================================================\n");

    /*
               50
             /    \
            30    70
           /  \   /  \
          20  40 60  80
    */
    TreeNode *root = createNode(50);
    root->left = createNode(30);
    root->right = createNode(70);
    root->left->left = createNode(20);
    root->left->right = createNode(40);
    root->right->left = createNode(60);
    root->right->right = createNode(80);

    printf("Preorder Traversal  (Root, Left, Right): ");
    preorder(root);
    printf("\n");

    printf("Inorder Traversal   (Left, Root, Right): ");
    inorder(root);
    printf("\n");

    printf("Postorder Traversal (Left, Right, Root): ");
    postorder(root);
    printf("\n");

    freeTree(root);
    return 0;
}
