#include <stdio.h>
#include <stdlib.h>

struct Node {
    char data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* buildBinaryTree(char preorder[], int* index) {
    char val = preorder[(*index)++];
    if (val == '^' || val == '\0')
        return NULL;

    struct Node* root = createNode(val);
    root->left = buildBinaryTree(preorder, index);
    root->right = buildBinaryTree(preorder, index);

    return root;
}

struct Node* findLowestCommonAncestor(struct Node* root, char node1, char node2) {
    if (root == NULL)
        return NULL;

    if (root->data == node1 || root->data == node2)
        return root;

    struct Node* left = findLowestCommonAncestor(root->left, node1, node2);
    struct Node* right = findLowestCommonAncestor(root->right, node1, node2);

    if (left != NULL && right != NULL)
        return root;

    return (left != NULL) ? left : right;
}

struct Node* findParent(struct Node* root, char child) {
    if (root == NULL)
        return NULL;

    if ((root->left != NULL && root->left->data == child) || (root->right != NULL && root->right->data == child))
        return root;

    struct Node* left = findParent(root->left, child);
    if (left != NULL)
        return left;

    return findParent(root->right, child);
}

int main() {
    char preorder[100];
    scanf("%s", preorder);

    int index = 0;
    struct Node* root = buildBinaryTree(preorder, &index);

    char node1, node2;
    scanf(" %c %c", &node1, &node2);

    struct Node* ancestor = findLowestCommonAncestor(root, node1, node2);

    if (ancestor == NULL)
        printf("-1\n");
    else {
        struct Node* parent1 = findParent(root, node1);
        struct Node* parent2 = findParent(root, node2);
        if (parent1->data == node2)
            printf("%c\n",parent2->data);
        else if (parent2->data == node1)
            printf("%c\n",parent1->data);
        else
            printf("%c\n",ancestor->data);
    }

    return 0;
}