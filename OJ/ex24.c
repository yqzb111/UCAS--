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

Status Find(HString *s, char x) {
    for (int i = 0; i < s->length; i++) {
        if (x == s->ch[i]) {
            return i;
        }
    }
    return -1;
}

void GetAllUniqueChars(HString *s, HString *t, HString *r) {
    for (int i = 0; s->ch[i]!='\0'; i++) {
        char currentChar = s->ch[i];
        int charFoundInT = Find(t, currentChar);
        if (charFoundInT == -1) { // Character not found in t
            int charFoundInR = Find(r, currentChar);
            if (charFoundInR == -1) { // Character not found in r
                StrInsert(r, currentChar);
            }
        }
    }
}

void PrintResult(HString *s, HString *r) {
    if (r->length == 0) {
        printf("-1\n");
        return;
    }

    printf("%s ", r->ch);
    for (int i = 0; r->ch[i]!='\0'; i++) {
        int firstOccurrence = Find(s, r->ch[i]);
        printf("%d", firstOccurrence);
    }
    printf("\n");
}

int main() {
    HString *s = (HString *)malloc(sizeof(HString));
    HString *t = (HString *)malloc(sizeof(HString));
    HString *r = (HString *)malloc(sizeof(HString));

    StrInit(s);
    StrInit(t);
    StrInit(r);

    char c;
    while((c=getchar())!=' '){
        StrInsert(s,c);
    }
    while((c=getchar())!='\n'){
        StrInsert(t,c);
    }

    GetAllUniqueChars(s, t, r);
    PrintResult(s, r);

    free(s->ch);
    free(t->ch);
    free(r->ch);
    free(s);
    free(t);
    free(r);

    return 0;
}