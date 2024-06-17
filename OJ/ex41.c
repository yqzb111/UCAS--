#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

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

int isCompleteTreeUtil(struct Node* root, int index, int num_nodes) {
    if (root == NULL)
        return 1;

    if (index >= num_nodes)
        return 0;

    // Recur for left and right subtrees
    return isCompleteTreeUtil(root->left, 2 * index + 1, num_nodes) &&
           isCompleteTreeUtil(root->right, 2 * index + 2, num_nodes);
}

int countNodes(struct Node* root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int isCompleteTree(struct Node* root) {
    int node_count = countNodes(root);
    return isCompleteTreeUtil(root, 0, node_count);
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

    int state = isCompleteTree(root);
    if(state==1)
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}