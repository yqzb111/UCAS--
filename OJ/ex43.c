#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct Node {
    int data; // 在这个上下文中，data用于存储节点在L和R数组中的索引
    int pos;
    struct Node *lchild, *rchild;
} Node, *BTree;

// 初始化二叉树节点，参数data代表节点在数组中的索引
BTree InitBinaryTree(int data,int pos) {
    BTree node = (BTree)malloc(sizeof(Node));
    if (!node) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    node->data = data;
    node->lchild = NULL;
    node->rchild = NULL;
    node->pos = pos;
    return node;
}

// 构建二叉树
void BuildBinaryTree(BTree root, int L[], int R[], int length) {
    if (root == NULL) return;

    if (L[root->pos] != 0 && root->pos+1<length) {
        root->lchild = InitBinaryTree(L[root->pos],root->pos+1);
        BuildBinaryTree(root->lchild, L, R, length);
    }

    if (R[root->pos] != 0 && root->pos+2<length && root->pos!=1) {
        root->rchild = InitBinaryTree(R[root->pos],root->pos+2);
        BuildBinaryTree(root->rchild, L, R, length);
    }

    if (R[root->pos] != 0 && root->pos+1<length && root->pos==1) {
        root->rchild = InitBinaryTree(R[root->pos],root->pos+2);
        BuildBinaryTree(root->rchild, L, R, length);
    }
}

// 查找指定数据的节点
BTree Find(BTree root, int index) {
    if (root == NULL || root->data == index) {
        return root;
    }
    BTree found = Find(root->lchild, index);
    if (found) return found;
    return Find(root->rchild, index);
}

// 在*p节点下插入以*x为根的二叉树
void InsertTree(BTree p, BTree x) {
    if (p->lchild != NULL) {
        x->rchild = p->lchild;
    }
    p->lchild = x;
}

// 中序遍历
void InorderTraverse(BTree T) {
    if (T) {
        InorderTraverse(T->lchild);
        printf("%d ", T->data);
        InorderTraverse(T->rchild);
    }
}

int main() {
    int L1[MAX];
    int R1[MAX];
    int L2[MAX];
    int R2[MAX];
    int i = 0, j;
    int data;
    char c;
    int length1 = 0,length2 = 0;
    int temp;

    while (i < MAX)
    {
        scanf("%d", &L1[i]);
        i++;
        length1++;
        if ((c = getchar()) == '\n')
            break;
    }

    i = 0;
    while (i < length1)
    {
        scanf("%d", &R1[i]);
        i++;
        if ((c = getchar()) == '\n')
            break;
    }

    scanf("%d",&data);
    c = getchar();

    i = 0;
    while (i < MAX)
    {
        scanf("%d", &L2[i]);
        i++;
        length2++;
        if ((c = getchar()) == '\n')
            break;
    }

    i = 0;
    while (i < length2)
    {
        scanf("%d", &R2[i]);
        i++;
        if ((c = getchar()) == '\n')
            break;
    }

    // 初始化并构建第一棵树
    BTree root1 = InitBinaryTree(L1[0],1); // 根节点在数组中的索引为0
    BuildBinaryTree(root1, L1, R1, length1);

    // 初始化并构建第二棵树
    BTree root2 = InitBinaryTree(L2[0],1); // 假设第二棵树的根节点也在数组的开始位置
    BuildBinaryTree(root2, L2, R2, length2);

    // 在第一棵树的指定节点下插入第二棵树
    BTree p = Find(root1, data); // 查找指定的节点
    if (p) {
        InsertTree(p, root2); // 执行插入操作
    }

    // 输出插入后的中序遍历结果
    InorderTraverse(root1);
    printf("\n");

    return 0;
}