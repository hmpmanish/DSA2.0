/*
 * Course Code: CSCR2501 - Advanced Data Structures Lab
 * Course Outcome: CO2
 * Experiment 12: Count Total Nodes, Leaf Nodes, and Height of Binary Tree
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

int countTotalNodes(TreeNode *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countTotalNodes(root->left) + countTotalNodes(root->right);
}

int countLeafNodes(TreeNode *root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

int countInternalNodes(TreeNode *root) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) {
        return 0;
    }
    return 1 + countInternalNodes(root->left) + countInternalNodes(root->right);
}

int treeHeight(TreeNode *root) {
    if (root == NULL) {
        return 0; // Height of empty tree is 0 (or -1 if measured by edges)
    }
    int leftH = treeHeight(root->left);
    int rightH = treeHeight(root->right);
    return (leftH > rightH ? leftH : rightH) + 1;
}

void freeTree(TreeNode *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    printf("=================================================================\n");
    printf(" Experiment 12: Count Total Nodes, Leaf Nodes & Height of Tree\n");
    printf("=================================================================\n");

    /*
                 10
               /    \
              20     30
             /  \      \
            40   50     60
                /
               70
    */
    TreeNode *root = createNode(10);
    root->left = createNode(20);
    root->right = createNode(30);
    root->left->left = createNode(40);
    root->left->right = createNode(50);
    root->right->right = createNode(60);
    root->left->right->left = createNode(70);

    printf("Tree Metrics Summary:\n");
    printf("  -> Total Nodes    : %d\n", countTotalNodes(root));
    printf("  -> Leaf Nodes     : %d\n", countLeafNodes(root));
    printf("  -> Internal Nodes : %d\n", countInternalNodes(root));
    printf("  -> Height of Tree : %d (levels)\n", treeHeight(root));

    freeTree(root);
    return 0;
}
