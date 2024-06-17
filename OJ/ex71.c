#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

void countSort(int arr[], int n) {
    int c[MAX] = {0};  // 创建一个计数数组，用于存储每个元素小于当前元素的元素个数
    int output[MAX];  // 创建一个输出数组，用于存储排序后的序列
    int i;

    // 遍历待排序数组，统计每个元素小于当前元素的元素个数
    for (i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[i]) {
                c[i]++;
            } else {
                c[j]++;
            }
        }
    }

    // 根据计数数组生成排序后的序列
    for (i = 0; i < n; i++) {
        output[c[i]] = arr[i];
    }

    // 打印计数数组
    for (i = 0; i < n-1; i++) {
        printf("%d ", c[i]);
    }
    printf("%d\n",c[i]);
}

int main() {
    int arr[MAX];
    char line[4000];
    fgets(line, sizeof(line), stdin);
    char *token = strtok(line, " ");
    int i = 0;
    while (token != NULL) {
        arr[i++] = atoi(token);
        token = strtok(NULL, " ");
    }
    int n = i;
    countSort(arr, n);
    return 0;
}
