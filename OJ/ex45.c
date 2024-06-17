#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

int n = 1;

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

struct Node* buildBinaryTree(char DATA[], int LChild[], int RChild[], int index, int n) {
    if (index < 0 || index >= n)
        return NULL;

    struct Node* root = createNode(DATA[index]);
    root->left = buildBinaryTree(DATA, LChild, RChild, LChild[index], n);
    root->right = buildBinaryTree(DATA, LChild, RChild, RChild[index], n);

    return root;
}

void preorderTraversal(struct Node* root,int count) {
    if (root == NULL)
        --n;
    if (root != NULL) {
        if(count == 1)
            printf("%c\n", root->data);
        else if(count == 2)
            printf("-%c\n",root->data);
        else if(count == 3)
            printf("--%c\n",root->data);
        preorderTraversal(root->left,++n);
        preorderTraversal(root->right,n);
    }
}

int main() {
    char DATA[MAX];
    int LChild[MAX];
    int RChild[MAX];
    DATA[0] = 0;
    LChild[0] = 0;
    RChild[0] = 0;
    int count = 1;
    // 读取输入
    while (scanf(" %c %d %d", &DATA[count], &LChild[count], &RChild[count]) == 3) {
        count++;
    }
    struct Node* root = buildBinaryTree(DATA, LChild, RChild, 1, count);

    preorderTraversal(root,n);
    return 0;
}