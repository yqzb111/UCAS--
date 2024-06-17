#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define MIN -10000
int num = 0;

typedef struct BiTreeNode {
    int data;
    struct BiTreeNode *lchild, *rchild;
} BiTreeNode;

// 创建新节点
BiTreeNode* createNode(int data) {
    BiTreeNode* node = (BiTreeNode*)malloc(sizeof(BiTreeNode));
    node->data = data;
    node->lchild = node->rchild = NULL;
    return node;
}

// 构建二叉排序树
BiTreeNode* insert(BiTreeNode* root, int data) {
    if (root == NULL) return createNode(data);
    if (data < root->data)
        root->lchild = insert(root->lchild, data);
    else if (data > root->data)
        root->rchild = insert(root->rchild, data);
    return root;
}

// 从大到小输出大于等于x的元素
void printGreaterOrEqual(BiTreeNode* root, int x, int y, int res[]) {
    if (root == NULL) return;
    
    // 先递归处理右子树
    printGreaterOrEqual(root->lchild, x, y, res);
    
    // 输出满足条件的当前节点
    if (root->data > x && root->data <y)
        res[num++] = root->data;
    
    // 再递归处理左子树
    printGreaterOrEqual(root->rchild, x, y, res);
}

int main() {
    BiTreeNode* root = NULL;
    int x,y;
    int res[MAX];
    char buffer[1024];
    for(int i=0;i<MAX;i++){
        res[i] = MIN;
    }
    // 读取输入的二叉排序树元素
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char *ptr = buffer;
        int value;
        while (sscanf(ptr, "%d", &value) == 1) {
            root = insert(root, value);
            while (*ptr != ' ' && *ptr != '\0') ptr++;
            if (*ptr == ' ') ptr++;
        }
    }

    // 读取判断条件x
    if (scanf("%d", &x) != 1) return 1;
    // 读取判断条件x
    if (scanf("%d", &y) != 1) return 1;

    // 从大到小输出大于等于x的元素
    printGreaterOrEqual(root, x, y, res);
    int j=0;
    while(res[j] > MIN){
        printf("%d",res[j]);
        if(res[j+1] > MIN)
            printf(" ");
        j++;
    }
    printf("\n");

    return 0;
}
