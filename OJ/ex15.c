#include <stdio.h>
#include <malloc.h>
#include <string.h>

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

ElemType Pop(SqStack *s){
    ElemType e;
if(s->top==0) return ERROR;
e=s->base[--s->top];
return e;
}

void isReverse(SqStack *L){
    char c;
    int state=1;
    ElemType e;
    while((c=getchar())!='&' && c!='@'){
        Push(L,c);
    }
    while((c=getchar())!='@'){
        e = Pop(L);
        if(e==c){
            state=1;
        }
        else if(L->top == 0) {
                state = 0; // 序列2比序列1长
                break;
            }
        else if(e!=c){
            state=0;
            break;
        }
    }
        // 如果栈不为空，说明序列1比序列2长
    if (L->top != 0) {
        state = 0;
    }
    printf("%d\n",state);
}

int main(){
    SqStack L;
    InitStack(&L);
    isReverse(&L);
    return 0;
}