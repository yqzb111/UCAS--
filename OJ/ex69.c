#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 合并两个有序序列的函数
void merge(int* arr, int m, int n) {
    int i = 0, j = m, k = 0;  // 初始化索引
    int* buffer = (int*)malloc(m * sizeof(int));  // 创建一个缓冲区，用于存储较短的序列
    memcpy(buffer, arr, m * sizeof(int));  // 将较短的序列复制到缓冲区

    // 当两个序列都还有剩余元素时，选择较小的元素添加到结果序列
    while (k < m && j < n) {
        if (buffer[k] <= arr[j]) {
            arr[i++] = buffer[k++];
        } else {
            arr[i++] = arr[j++];
        }
    }

    // 如果较短的序列还有剩余元素，将它们添加到结果序列
    while (k < m) {
        arr[i++] = buffer[k++];
    }

    free(buffer);  // 释放缓冲区
}

int main() {
    int arr[1000000];  // 创建一个数组，用于存储待排序的元素
    char line[4000000];  // 创建一个字符数组，用于存储输入的一行数据
    fgets(line, sizeof(line), stdin);  // 读取一行输入
    char *token = strtok(line, " ");  // 使用空格分隔每个元素
    int i = 0;
    // 遍历每个元素，将它们添加到待排序数组中
    while (token != NULL) {
        arr[i++] = atoi(token);
        token = strtok(NULL, " ");
    }
    int m = i;  // 获取第一个序列的元素数量

    fgets(line, sizeof(line), stdin);  // 读取第二行输入
    token = strtok(line, " ");  // 使用空格分隔每个元素
    // 遍历每个元素，将它们添加到待排序数组中
    while (token != NULL) {
        arr[i++] = atoi(token);
        token = strtok(NULL, " ");
    }
    int n = i;  // 获取总的元素数量

    merge(arr, m, n);  // 对两个有序序列进行合并

    // 打印合并后的序列
    for (i = 0; i < n-1; i++) {
        printf("%d ", arr[i]);
    }
    printf("%d\n",arr[i]);

    return 0;
}
