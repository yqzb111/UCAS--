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

Status Pop(SqStack *s,ElemType *e){
if(s->top==0) return ERROR;
*e=s->base[--s->top];
return OK;
}


typedef struct Node{
        ElemType data;
        struct Node *next;
}QNode;
typedef struct{
    QNode *front;
    QNode *rear;
}LinkedQueue;

Status InitQueue(LinkedQueue *lq){
    lq->front = lq->rear = (QNode *)malloc(sizeof(QNode));
    if(!lq->front)
        return ERROR;
    lq->front->next = NULL;
    return OK;
}

Status Enqueue(LinkedQueue *lq,ElemType e){
    QNode *p;
    p = (QNode *)malloc(sizeof(QNode));
    if(!p)
        return ERROR;
    p->data = e;
    p->next = NULL;
    lq->rear->next = p;
    lq->rear = p;
    return OK;
}

Status Dequeue(LinkedQueue *lq,ElemType *e){
    QNode *p;
    if(lq->front == lq->rear)
        return  ERROR;
    p = lq->front->next;
    *e = p->data;
    lq->front->next = p->next;
    if(lq->rear == p)
        lq->rear = lq->front;
    free(p);
    return OK;
}


int main(){
    char c;
    int state;
    SqStack L;
    LinkedQueue M;
    InitStack(&L);
    InitQueue(&M);
    while((c=getchar())!='@'){
        Push(&L,c);
        Enqueue(&M,c);
    }
    char l,m;
    while(Dequeue(&M,&m)){
        Pop(&L,&l);
        if(l==m){
            state=1;
        }
        else{
            state=0;
            break;
        }
    }
    printf("%d\n",state);
    return 0;
}