#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAXINT 9999999

// 定义链表节点结构体
typedef struct {
    int key;
    int next;
} SLNode;

// 定义链表结构体
typedef struct {
    SLNode r[MAX + 1];
    int length;
} SLinkListType;

// 交换两个整数的值
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// 对数组进行分割，并返回分割点
int partition(SLinkListType *SL, int low, int high) {
    int pivot = SL->r[high].key;  // 选择最后一个元素作为枢轴
    int i = (low - 1);  // 初始化小于枢轴元素的索引

    // 遍历数组，将小于枢轴的元素放到左边
    for (int j = low; j <= high - 1; j++) {
        if (SL->r[j].key < pivot) {
            i++;
            swap(&SL->r[i].key, &SL->r[j].key);
        }
    }
    // 将枢轴放到正确的位置
    swap(&SL->r[i + 1].key, &SL->r[high].key);
    return (i + 1);
}

// 对数组进行插入排序
void insertionSort(SLinkListType *SL, int low, int high) {
    int i, key, j;
    for (i = low + 1; i <= high; i++) {
        key = SL->r[i].key;
        j = i - 1;
        // 将大于key的元素向右移动
        while (j >= low && SL->r[j].key > key) {
            SL->r[j + 1].key = SL->r[j].key;
            j = j - 1;
        }
        // 将key插入到正确的位置
        SL->r[j + 1].key = key;
    }
}

// 使用非递归方式实现快速排序
void quickSortIterative(SLinkListType *SL, int l, int h) {
    int stack[MAX];  // 创建一个栈来保存待排序子序列的上、下界

    int top = -1;  // 初始化栈顶

    // 将整个数组的上、下界入栈
    stack[++top] = l;
    stack[++top] = h;

    // 当栈不为空时，执行循环
    while (top >= 0) {
        // 从栈中取出一个子序列的上、下界
        h = stack[top--];
        l = stack[top--];

        // 如果子序列的长度小于等于3，直接使用插入排序
        if (h - l <= 3) {
            insertionSort(SL, l, h);
            continue;
        }

        // 对子序列进行分割，并获取分割点
        int p = partition(SL, l, h);

        // 比较两个子序列的长度，优先对长度较短的子序列进行排序
        if (p - l < h - p) {
            if (p + 1 < h) {
                stack[++top] = p + 1;
                stack[++top] = h;
            }

            stack[++top] = l;
            stack[++top] = p - 1;
        } else {
            if (l < p - 1) {
                stack[++top] = l;
                stack[++top] = p - 1;
            }

            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }
}

// 打印链表
void printSL(SLinkListType *SL) {
    int i;
    for (i = 1; i < SL->length; i++) {
        printf("%d ", SL->r[i].key);
    }
    printf("%d\n",SL->r[i].key);
}

int main() {
    SLinkListType SL;
    char line[400];
    fgets(line, sizeof(line), stdin);
    char *token = strtok(line, " ");
    int i = 1;
    while (token != NULL) {
        SL.r[i++].key = atoi(token);
        token = strtok(NULL, " ");
    }
    SL.length = i - 1;
    quickSortIterative(&SL, 1, SL.length);
    printSL(&SL);
    return 0;
}
