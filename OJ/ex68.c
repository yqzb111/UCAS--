#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAXINT 9999999

// 定义交换函数，用于交换两个整数的值
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// 定义堆调整函数，用于调整堆的结构以保持堆的性质
void heapify(int arr[], int n, int i) {
    int largest = i;  // 初始化最大元素的索引为i
    int l = 3*i + 1;  // 左孩子的索引
    int m = 3*i + 2;  // 中间孩子的索引
    int r = 3*i + 3;  // 右孩子的索引

    // 如果左孩子存在且大于当前最大元素，则更新最大元素的索引
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // 如果中间孩子存在且大于当前最大元素，则更新最大元素的索引
    if (m < n && arr[m] > arr[largest])
        largest = m;

    // 如果右孩子存在且大于当前最大元素，则更新最大元素的索引
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // 如果最大元素的索引不是i，说明需要调整堆的结构
    if (largest != i) {
        swap(&arr[i], &arr[largest]);  // 交换当前元素和最大元素
        heapify(arr, n, largest);  // 对交换后的子树进行调整
    }
}

// 定义三叉堆排序函数
void ternaryHeapSort(int arr[], int n) {
    // 构建初始堆，从最后一个非叶子节点开始，自下而上进行调整
    for (int i = n / 3 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // 从堆中取出最大元素（堆顶元素），并将其放到数组的末尾
    for (int i=n-1; i>=0; i--) {
        swap(&arr[0], &arr[i]);  // 交换堆顶元素和当前最后一个元素
        heapify(arr, i, 0);  // 对剩余的元素进行调整，保持堆的性质
    }
}

// 定义打印数组的函数
void printArray(int arr[], int n) {
    for (int i=0; i<n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[MAX];
    char line[400];
    fgets(line, sizeof(line), stdin);  // 读取一行输入
    char *token = strtok(line, " ");  // 使用空格分隔每个元素
    int i = 0;
    while (token != NULL) {
        arr[i++] = atoi(token);  // 将元素添加到数组中
        token = strtok(NULL, " ");
    }
    int n = i;  // 获取元素的数量
    ternaryHeapSort(arr, n);  // 对数组进行三叉堆排序
    printArray(arr, n);  // 打印排序后的数组
    return 0;
}

