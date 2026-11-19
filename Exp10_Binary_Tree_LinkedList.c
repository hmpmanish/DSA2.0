/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO2
 * Experiment 10: Implementation of Binary Tree using Linked List
 * Node creation, subtree attachments, and structural display
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createNode(int value) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void printTree2D(TreeNode *root, int space) {
    const int COUNT = 6;
    if (root == NULL) {
        return;
    }

    space += COUNT;

    // Process right child first
    printTree2D(root->right, space);

    // Print current node after spaces
    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    printf("[%d]\n", root->data);

    // Process left child
    printTree2D(root->left, space);
}

void freeTree(TreeNode *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    printf("=====================================================\n");
    printf(" Experiment 10: Binary Tree using Linked List\n");
    printf("=====================================================\n");

    /*
            1
          /   \
         2     3
        / \   / \
       4   5 6   7
    */
    TreeNode *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    printf("Constructed Binary Tree with 7 nodes successfully.\n");
    printf("2D Visual Representation of the Binary Tree (rotated 90 degrees counter-clockwise):\n");
    printTree2D(root, 0);
    printf("\n");

    freeTree(root);
    return 0;
}
