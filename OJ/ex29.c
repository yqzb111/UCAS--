#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INITSTRLEN 100
#define INCREASE 10
#define ERROR 0
#define OK 1

typedef struct {
    char *ch;
    int strsize;
    int length;
} HString;

typedef int Status;

Status StrInit(HString *s) {
    s->ch = (char *)malloc(INITSTRLEN * sizeof(char));
    if (!s->ch)
        return ERROR;
    s->ch[0] = '\0';
    s->length = 0;
    s->strsize = INITSTRLEN;
    return OK;
}

Status StrInsert(HString *s, char x) {
    if (s->length >= s->strsize - 1) { // 若字符串即将溢出，进行扩容
        s->strsize += INCREASE;
        s->ch = (char *)realloc(s->ch, s->strsize * sizeof(char));
        if (!s->ch)
            return ERROR;
    }
    s->ch[s->length] = x;
    s->length++;
    s->ch[s->length] = '\0'; // 在字符串末尾添加空字符结束符
    return OK;
}

// 比较函数，用于字符串排序
int cmpfunc(const void * a, const void * b) {
   return strcmp(*(char **)a, *(char **)b);
}

// 求两个字符串的公共前缀长度
int commonPrefix(char *s1, char *s2) {
    int i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return i;
}

Status StrSubstr(HString *subs,HString *s,int i,int j){
    int k;
    if(i<=0 || i>s->length || j<0 || j>s->length-i+1)
        return ERROR;
    if(subs->strsize<j+1){
        subs->ch = (char *)realloc(subs->ch,(j+1)*sizeof(char));
        if(!subs->ch)
            return ERROR;
        subs->strsize = j+1;
    }
    for(k=0;k<j;k++)
        subs->ch[k] = s->ch[i-1+k];
    subs->ch[j]='\0';
    subs->length = j;
    return OK;
}

Status IsStrEqual(HString *s1,HString *s2){
    int i;
    for(i=0;i<s1->length && i<s2->length;i++){
        if(s1->ch[i]!=s2->ch[i])
            return ERROR;
    }
    if(i<s1->length || i<s2->length)
        return ERROR;
    else
        return OK;
}

Status StrIndex(HString *s,int i,HString *t){
    int m,n;
    HString sub;
    StrInit(&sub);
    n=s->length;
    m=t->length;
    while(i<=n-m+1){
        StrSubstr(&sub,s,i,m);
        if(!IsStrEqual(&sub,t))
            i++;
        else
            return i;
    }
    return 0;
}

// 获取最长重复子串及其位置
void GetLargest(HString *s){
    int n = s->length;
    char *suffixes[n]; // 存储所有后缀的指针数组
    int positions[n]; // 存储所有后缀的起始位置

    // 初始化后缀数组和位置数组
    for (int i = 0; i < n; i++) {
        suffixes[i] = &(s->ch[i]);
    }

    // 对后缀数组进行排序
    qsort(suffixes, n, sizeof(char *), cmpfunc);

    char *res = ""; // 最长重复子串的指针
    int res_length = 0; // 最长重复子串的长度

    // 遍历排序后的后缀数组，查找最长重复子串
    for (int i = 0; i < n - 1; i++) {
        int length = commonPrefix(suffixes[i], suffixes[i+1]); // 计算公共前缀长度

        if (length > res_length) { // 若当前公共前缀长度大于记录的最长重复子串长度
            res_length = length; // 更新最长重复子串长度
            res = suffixes[i]; // 更新最长重复子串指针
        }
    }
    HString q;
    StrInit(&q); // 初始化子串 q

    // 将 res 中的字符插入到子串 q 中
    for (int i = 0; i < res_length; i++) {
        StrInsert(&q, res[i]);
    }

    // 调用 StrIndex 函数求取最长重复子串的首次出现位置
    int pos = StrIndex(s, 0, &q);

    // 输出最长重复子串及其首次出现位置
    if (res_length > 0) {
        for (int i = 0; i < res_length; i++)
            printf("%c", res[i]);
        printf(" %d\n", pos-1); // 输出最长重复子串的首次出现位置
    } else {
        printf("-1\n"); // 若不存在重复子串，输出-1
    }
}

int main(){
    HString *s;
    s = (HString *)malloc(sizeof(HString));
    StrInit(s); // 初始化串

    char c;
    while((c=getchar())!='\n'){
        StrInsert(s,c); // 逐字符插入串
    }

    GetLargest(s); // 获取最长重复子串及其位置

    // 释放内存
    free(s->ch);
    free(s);
    return 0;
}