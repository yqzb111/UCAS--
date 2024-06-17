#include <stdio.h>
#include <stdbool.h>

#define MAX 1000

// 在二叉树中搜索节点的递归函数
bool isDescendant(int L[], int R[], int n, int u, int v) {
    // 如果v为空或者u等于v，则u不可能是v的子孙
    if (v == 0 || u == v)
        return false;

    // 在L和R数组中搜索v的左孩子和右孩子
    int leftChild = L[v];
    int rightChild = R[v];

    // 如果u等于v的左孩子或右孩子，则u是v的子孙
    if (u == leftChild || u == rightChild)
        return true;

    // 递归搜索左子树和右子树
    bool isLeftDescendant = (leftChild != 0) ? isDescendant(L, R, n, u, leftChild) : false;
    bool isRightDescendant = (rightChild != 0) ? isDescendant(L, R, n, u, rightChild) : false;

    return isLeftDescendant || isRightDescendant;
}

int main(){
    int L[MAX];
    int R[MAX];
    int i=0,j;
    int posL,posR;
    char c;
    int length = 0;
    int u,v;
    while(i<MAX){
        scanf("%d",&L[i]);
        i++;
        length++;
        if((c = getchar()) == '\n')
            break;
    }
    i = 0;
    while(i<length){
        scanf("%d",&R[i]);
        i++;
        if((c = getchar()) == '\n')
            break;
    }
    scanf("%d %d",&u,&v);
    // 判断节点u是否为节点v的子孙
    bool result = isDescendant(L, R, length, u, v);

    // 输出结果
    printf("%d\n", result ? 1 : 0);

    return 0;
}