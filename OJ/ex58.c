#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 20

typedef struct BiTreeNode {
    int data;
    struct BiTreeNode *lchild, *rchild;
} BiTreeNode;

// 初始化二叉树节点
BiTreeNode* createNode(int data) {
    BiTreeNode* node = (BiTreeNode*)malloc(sizeof(BiTreeNode));
    node->data = data;
    node->lchild = node->rchild = NULL;
    return node;
}

// 构建二叉树
BiTreeNode* buildBiTree(int data[], int lchild[], int rchild[], int len, int index) {
    if (index == -1 || index >= len) return NULL;
    BiTreeNode* node = createNode(data[index]);
    node->lchild = buildBiTree(data, lchild, rchild, len, lchild[index]);
    node->rchild = buildBiTree(data, lchild, rchild, len, rchild[index]);
    return node;
}

// 中序遍历判断是否为二叉排序树的辅助函数
int isBSTUtil(BiTreeNode* node, int* prev) {
    if (node == NULL) return 1;
    if (!isBSTUtil(node->lchild, prev)) return 0;
    // 如果当前节点的值小于等于前一个节点的值，则违反了二叉排序树的性质,二叉排序树的性质要求：中序遍历结果是严格递增的
    if (node->data <= *prev) return 0;
    // 更新前一个节点的值为当前节点的值,确保下一个节点（右子树中的节点）将会被正确地比较
    *prev = node->data;
    return isBSTUtil(node->rchild, prev);
}

//判断二叉树是否为二叉排序树
int isBST(BiTreeNode* root) {
    int prev = INT_MIN;
    return isBSTUtil(root, &prev);
}

int main() {
    int data[MAX];
    int lchild[MAX];
    int rchild[MAX];
    int i = 0, len;
    while (scanf("%d %d %d", &data[i], &lchild[i], &rchild[i]) == 3 && i < MAX) {
        i++;
    }
    len = i;

    BiTreeNode* tree = buildBiTree(data, lchild, rchild, len, 0);

    int result = isBST(tree);
    printf("%d\n", result);

    return 0;
}
