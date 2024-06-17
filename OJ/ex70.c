#include <stdio.h>
#include <stdlib.h>

#define MAX 10000

int main() {
    int count[MAX] = {0};  // 创建一个计数数组，用于存储每个元素的出现次数
    int num,i,max;
    // 使用for循环读取输入，并进行计数
    for (i = 0; i < 1000; i++) {
        scanf("%d", &num);
        count[num]++;
    }
    for(max = 9999;count[max] == 0;max--);
    // 根据计数数组生成排序后的序列
    for (i = 0; i < max; i++) {
        while (count[i]-- > 0) {
            printf("%d ", i);
        }
    }
    while (count[i]-- > 1) {
            printf("%d ", i);
    }
    printf("%d\n",i);
    return 0;
}
