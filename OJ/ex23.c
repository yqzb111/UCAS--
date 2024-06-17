#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void strinverse(char *s, int i, int len) {
    if (i < len / 2) {
        char tmp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = tmp;
        strinverse(s, i + 1, len);
    }
}

int main() {
    char *s = NULL;
    size_t bufsize = 100; // 初始缓冲区大小
    s = (char *)malloc(bufsize * sizeof(char));
    if (s == NULL) {
        fprintf(stderr, "内存分配失败\n");
        return 1;
    }

    if (fgets(s, bufsize, stdin) == NULL) {
        free(s); // 退出前释放分配的内存
        return 1;
    }

    // 如果存在换行符，则删除
    if (strchr(s, '\n') != NULL)
        s[strcspn(s, "\n")] = '\0';

    int len = strlen(s);
    strinverse(s, 0, len);
    printf("%s\n", s);

    free(s); // 释放分配的内存
    return 0;
}
