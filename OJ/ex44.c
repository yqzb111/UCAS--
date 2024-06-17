#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int search(char arr[], int start, int end, char value) {
    int i;
    for (i = start; i <= end; i++) {
        if (arr[i] == value)
            return i;
    }
    return -1;
}

struct Node* buildTree(char preorder[], char inorder[], int inStart, int inEnd) {
    static int preIndex = 0;

    if (inStart > inEnd)
        return NULL;

    struct Node* newNode = createNode(preorder[preIndex++]);

    if (inStart == inEnd)
        return newNode;

    int inIndex = search(inorder, inStart, inEnd, newNode->data);

    newNode->left = buildTree(preorder, inorder, inStart, inIndex - 1);
    newNode->right = buildTree(preorder, inorder, inIndex + 1, inEnd);

    return newNode;
}

void postorder(struct Node* root) {
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    printf("%c", root->data);
}

int main() {
    char preorder[100], inorder[100];
    scanf("%s", preorder);
    scanf("%s", inorder);

    int len = strlen(preorder);
    struct Node* root = buildTree(preorder, inorder, 0, len - 1);

    postorder(root);
    printf("\n");

    return 0;
}
