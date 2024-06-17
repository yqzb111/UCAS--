#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

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
    if (val == '#' || val == '\0')
        return NULL;

    struct Node* root = createNode(val);
    root->left = buildBinaryTree(preorder, index);
    root->right = buildBinaryTree(preorder, index);

    return root;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int getPriority(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void InorderTraverse(struct Node* T, char result[], int* index, char parentOp, int parentPriority) {
    if (T) {
        int currentPriority = getPriority(T->data);
        if (T->left) {
            if (isOperator(T->left->data) && getPriority(T->left->data) < currentPriority) {
                result[(*index)++] = '(';
            }
            InorderTraverse(T->left, result, index, T->data, currentPriority);
            if (isOperator(T->left->data) && getPriority(T->left->data) < currentPriority) {
                result[(*index)++] = ')';
            }
        }
        result[(*index)++] = T->data;
        if (T->right) {
            if (isOperator(T->right->data) && getPriority(T->right->data) <= currentPriority) {
                result[(*index)++] = '(';
            }
            InorderTraverse(T->right, result, index, T->data, currentPriority);
            if (isOperator(T->right->data) && getPriority(T->right->data) <= currentPriority) {
                result[(*index)++] = ')';
            }
        }
    }
}

int main() {
    char preorder[100];
    scanf("%s", preorder);

    int index = 0;
    struct Node* root = buildBinaryTree(preorder, &index);

    char result[MAX_SIZE];
    int length = 0;
    InorderTraverse(root, result, &length, '\0', 0);

    // 输出中序遍历结果（包含括号）
    for (int i = 0; i < length; ++i) {
        printf("%c", result[i]);
    }
    printf("\n");

    return 0;
}