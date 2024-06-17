#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define INITSIZE 100
#define INCREMENTSIZE 10  //栈空间分配增量
#define OK 1
#define ERROR 0

typedef int Status;
typedef char ElemType;

typedef struct {
    int top; //栈顶
    ElemType *base;
    int stacksize;//栈底
}SqStack; // 动态顺序栈

Status InitStack(SqStack *s){
    s->base=(ElemType *)malloc(INITSIZE * sizeof(ElemType));
    if (!s) return ERROR;
    s->top=0;
    s->stacksize=INITSIZE;
    return OK;
}

Status Push(SqStack *s,ElemType e){
if(s->top >= s->stacksize) { //若栈已满，则增加INCREMENTSIZE个存储单元
    s->base=(ElemType *)realloc(s->base,(s->stacksize+INCREMENTSIZE)*sizeof(ElemType));
    if(!s->base) return ERROR;
    s->stacksize+=INCREMENTSIZE;
}
s->base[s->top++]=e;
return OK;
}

Status Pop(SqStack *s,ElemType *e){
if(s->top==0) return ERROR;
*e=s->base[--s->top];
return OK;
}

Status GetTop(SqStack *s,ElemType *e) { //只看不取
if(s->top==0) return ERROR;
*e=s->base[s->top-1];
return OK;
}

int IsStackEmpty(SqStack *s){
    if(s->top == 0) return 1;
    else return 0;
}

Status MatchingBrackets(char *exps,int count){
int i=0;
Status state=OK;
ElemType e; SqStack s; InitStack(&s);
while(state && i<=count ){
    switch(exps[i]){
        case '(':
        case '[':
        case '{':Push(&s,exps[i]);
            break;
        case ')':
        case ']':
        case '}':if(!GetTop(&s,&e)) {state=ERROR; break;};
            if((e=='(' && exps[i]==')') ||  (e=='[' && exps[i]==']')
                ||  (e=='{' && exps[i]=='}'))
            Pop(&s,&e);
            else state=ERROR;
            break;
    }
i++;
}
if(IsStackEmpty(&s) && state) {
    printf("1\n"); return OK;}
else {
    printf("0\n");return ERROR;}
}

int main() {
    char exps[100];
    fgets(exps, sizeof(exps), stdin);
    int i = 0;
    while (exps[i] != '\0' && exps[i] != '\n') {
        i++;
    }
    int count = i;
    MatchingBrackets(exps, count);
    return 0;
}