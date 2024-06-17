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

Status StrComp(HString *s,HString *t){
    for(int i=0;i<s->length && i<t->length;i++){
        if(s->ch[i]!=t->ch[i])
            return s->ch[i]-t->ch[i];
    }
    return s->length-t->length;
}

int main(){
    HString *s = (HString *)malloc(sizeof(HString));
    HString *t = (HString *)malloc(sizeof(HString));
    StrInit(s);
    StrInit(t);
    // 输入串s和串t
    char c;
    while((c=getchar())!=' '){
        StrInsert(s,c);
    }
    while((c=getchar())!='\n'){
        StrInsert(t,c);
    }
    int state;
    state = StrComp(s,t);
    if(state==0){
        printf("0\n");
    }
    else if(state<0){
        printf("-1\n");
    }
    else{
        printf("1\n");
    }
    return 0;
}