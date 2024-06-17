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
    if (s->length >= s->strsize - 1) { // -1 为了留出空间给空字符结束符
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

void GetNextVal(HString *pattern,int nextval[]){
    int j=0,k=-1;
    nextval[0] = -1;
    while(j<pattern->length){
        if(k==-1 || pattern->ch[j] == pattern->ch[k]){
            j++;
            k++;
            if(pattern->ch[j] == pattern->ch[k])
                nextval[j] = nextval[k];
            else
                nextval[j] = k;
        }
        else
            k = nextval[k];
    }
}

int StrIndexKMP(HString *s,HString *t){
    int next[INITSTRLEN];
    GetNextVal(t,next);
    int i=0,j=0;
    while(i<s->length && j<t->length){
        if(j == -1 || s->ch[i] == t->ch[j]){
            i++;
            j++;
        }
        else
            j = next[j];
    }
    if(j>=t->length)
        return i-t->length;
    else 
        return -1;
}

int main() {
    int text_length, pattern_length;
    int i;
    char c;
    scanf("%d %d", &text_length,&pattern_length);
    HString *text = (HString *)malloc(sizeof(HString));
    HString *pattern = (HString *)malloc(sizeof(HString));
    StrInit(text);
    StrInit(pattern);
    // 读取输入并创建链表
    c = getchar();
    for (i = 0; i < text_length; ++i) {
        scanf("%c", &c);
        StrInsert(text,c);
    }
    c = getchar();
    for (i = 0; i < pattern_length; ++i) {
        char ch;
        scanf("%c", &c);
        StrInsert(pattern,c);
    }
    // 调用KMP算法进行匹配
    int result = StrIndexKMP(text,pattern);
    printf("%d\n",result);
    return 0;
}