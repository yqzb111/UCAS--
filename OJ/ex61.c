#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define MIN -10000
int num = 0;

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

// 创建新节点
TreeNode* createNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// 按照先序序列构建二叉排序树
TreeNode* buildTree(int** arr) {
    if (**arr == -1) {
        (*arr)++;
        return NULL;
    }
    TreeNode* root = createNode(**arr);
    (*arr)++;
    root->left = buildTree(arr);
    root->right = buildTree(arr);
    return root;
}

// 插入节点到二叉排序树
TreeNode* insert(TreeNode* root, int data) {
    if (root == NULL) return createNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

// 合并两棵二叉排序树
void mergeTrees(TreeNode* root1, TreeNode* root2) {
    if (root2 == NULL) return;
    mergeTrees(root1, root2->left);
    mergeTrees(root1, root2->right);
    root1 = insert(root1, root2->data);
}

// 中序遍历并输出二叉排序树
void inorderTraversal(TreeNode* root, int res[]) {
    if (root == NULL) return;
    inorderTraversal(root->left,res);
    res[num++] = root->data;
    inorderTraversal(root->right,res);
}

int main() {
    char buffer[1024];
    int arr1[1024], arr2[1024];
    int *ptr1 = arr1, *ptr2 = arr2;
    int res[MAX];
    for(int i=0;i<MAX;i++){
        res[i] = MIN;
    }
    // 读取第一棵二叉排序树的先序序列
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char *ptr = buffer;
        while (sscanf(ptr, "%d", ptr1) == 1) {
            while (*ptr != ' ' && *ptr != '\0') ptr++;
            if (*ptr == ' ') ptr++;
            ptr1++;
        }
    }

    // 读取第二棵二叉排序树的先序序列
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char *ptr = buffer;
        while (sscanf(ptr, "%d", ptr2) == 1) {
            while (*ptr != ' ' && *ptr != '\0') ptr++;
            if (*ptr == ' ') ptr++;
            ptr2++;
        }
    }

    // 构建两棵二叉排序树
    ptr1 = arr1;
    ptr2 = arr2;
    TreeNode* tree1 = buildTree(&ptr1);
    TreeNode* tree2 = buildTree(&ptr2);

    // 合并两棵二叉排序树
    mergeTrees(tree1, tree2);

    // 中序遍历并输出合并后的二叉排序树
    inorderTraversal(tree1,res);
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
