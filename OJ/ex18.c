#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define INITSIZE 100
#define INCREMENTSIZE 10  // 栈空间分配增量
#define OK 1
#define ERROR 0
#define OPSETSIZE 7

char OPSET[OPSETSIZE]={'+' , '-' , '*' , '/' ,'(' , ')' , '#'};
unsigned char Prior[OPSETSIZE][OPSETSIZE] = {
    {'>','>','<','<','<','>','>'},
    {'>','>','<','<','<','>','>'},
    {'>','>','>','>','<','>','>'},
    {'>','>','>','>','<','>','>'},
    {'<','<','<','<','<','=',' '},
    {'>','>','>','>',' ','>','>'},
    {'<','<','<','<','<',' ','='} 
};

typedef int Status;
typedef char ElemType;

typedef struct{
    int top; // 栈顶
    ElemType *base;
    int stacksize; // 栈底
} SqStack;          // 动态顺序栈

Status InitStack(SqStack *s){
    s->base = (ElemType *)malloc(INITSIZE * sizeof(ElemType));
    if (!s->base)
        return ERROR;
    s->top = 0;
    s->stacksize = INITSIZE;
    return OK;
}

Status Push(SqStack *s, ElemType e){
    if (s->top >= s->stacksize){ // 若栈已满，则增加INCREMENTSIZE个存储单元
        s->base = (ElemType *)realloc(s->base, (s->stacksize + INCREMENTSIZE) * sizeof(ElemType));
        if (!s->base)
            return ERROR;
        s->stacksize += INCREMENTSIZE;
    }
    s->base[s->top++] = e;
    return OK;
}

Status Pop(SqStack *s, ElemType *e){
    if (s->top == 0)
        return ERROR;
    *e = s->base[--s->top];
    return OK;
}

Status GetTop(SqStack *s, ElemType *e){ // 只看不取
    if (s->top == 0)
        return ERROR;
    *e = s->base[s->top - 1];
    return OK;
}

// 测试Test是否是运算符
Status In(char Test, char *TestOp){
    for (int i = 0; i < OPSETSIZE; i++){
        if (Test == TestOp[i])
            return OK;
    }
    return ERROR;
}

int ReturnOpOrd(char op, char *TestOp){
    for (int i = 0; i < OPSETSIZE; i++){
        if (op == TestOp[i])
            return i;
    }
    return 0;
}

// 返回两算符之间的优先关系
void Precede(char Aop, char Bop, char *result){
    int i, j;
    i = ReturnOpOrd(Aop, OPSET);
    j = ReturnOpOrd(Bop, OPSET);
    *result = Prior[i][j];
    return;
}

void RPN(char *MyExp){
    SqStack OptrStack;
    InitStack(&OptrStack);
    char rpn[100];
    int rpnindex = 0;
    Push(&OptrStack,'#');
    for (int i = 0; i < strlen(MyExp); i++){
        char c = MyExp[i];
        if(In(c, OPSET)){
            char top;
            GetTop(&OptrStack, &top);
            char result;
            Precede(top, c, &result);
            switch (result){
                case '<':
                    Push(&OptrStack, c);
                    break;
                case '=':
                    Pop(&OptrStack, &top);
                    break;
                case '>':
                    Pop(&OptrStack, &top);
                    rpn[rpnindex++] = top;
                    i--;
                    break;
                case ' ':
                    printf("Input Error\n");
                    break;
            }
        }
        else{
            rpn[rpnindex++] = c;
        }
    }
    while (OptrStack.top > 1){
        char top;
        Pop(&OptrStack, &top);
        rpn[rpnindex++] = top;
    }
    rpn[rpnindex] = '\0';
    printf("%s\n", rpn);
}

int main(){
    char *str;
    str = (char *)malloc(20 * sizeof(char));
    scanf("%s", str);
    RPN(str);
    free(str);
    return 0;
}