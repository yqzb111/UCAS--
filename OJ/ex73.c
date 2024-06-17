#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int* global_b;  // 创建一个全局变量，用于在比较函数中访问原始数组

// 定义比较函数，用于比较原数组中对应索引的元素
int compare(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    if (global_b[arg1] < global_b[arg2]) return -1;
    else if (global_b[arg1] > global_b[arg2]) return 1;
    else return 0;
}

int main() {
    int b[MAX];  // 创建一个数组，用于存储待排序的元素
    int a[MAX];  // 创建一个数组，用于存储排序后的元素
    int n;
    scanf("%d", &n);  // 读取数据元素的个数
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);  // 读取数据元素
        a[i] = i;  // 初始化索引数组
    }
    global_b = b;  // 将全局变量设置为原始数组
    qsort(a, n, sizeof(int), compare);  // 对索引数组进行排序
    for (int i = 0; i < n; i++) {  // 打印排序后的序列
        printf("%d ", b[a[i]]);
    }
    printf("\n");
    return 0;
}
