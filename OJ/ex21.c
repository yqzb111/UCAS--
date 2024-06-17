#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INITSIZE 100
#define INCREMENTSIZE 10  //栈空间分配增量
#define OK 1
#define ERROR 0

typedef int Status;
typedef int ElemType;

typedef struct QNode{
	ElemType data;       //数据域
	struct QNode *next;  //指针域
}QNode;
typedef struct{  //不设头指针
	QNode *rear;//尾指针
}LinkQueue;

Status InitQueue(LinkQueue *Q){
	Q->rear=(QNode *)malloc(sizeof(QNode));
	if(!Q->rear){
		return ERROR;
	}
	Q->rear->next=Q->rear;
	return OK;
}

Status InQueue(LinkQueue *Q,ElemType e){  //将数据e插入队列（尾部）
	struct QNode *p;
	p=(QNode *)malloc(sizeof(QNode));  //开辟一个空间，结点记为p
	if(!p){
		return ERROR; //存储空间分配失败
	}
	p->data=e;  //p的数据域存放e
	p->next=Q->rear->next;  //p指向头结点
	Q->rear->next=p;  //尾结点指向p
	Q->rear=p;  //p为尾结点
	return OK;
}

Status OutQueue(LinkQueue *Q,ElemType *e){  //删除头结点并把头结点数据域中的值赋给e
	if(Q->rear->next==Q->rear){
		return ERROR; //队空
	}
	struct QNode *p;
	p=Q->rear->next->next;    //p指向头结点
	*e=p->data;     //e取头结点数据域的值
	if(p==Q->rear){     //头结点和尾结点相等，即队列中只有一个元素
		Q->rear=Q->rear->next;    
		Q->rear->next=p->next;   
	}else{    //队列中有多个元素
		Q->rear->next->next=p->next; 
	}
	free(p);
	return OK;
}

void DestroyQueue(LinkQueue *Q) {
    while(Q->rear->next != Q->rear) {
        ElemType e;
        OutQueue(Q, &e);
    }
    free(Q->rear);
}

int main(){
    int n,i=0;
    scanf("%d",&n);
    LinkQueue L;
    if(InitQueue(&L) == ERROR) {
        printf("Failed to initialize queue.\n");
        return 1;
    }
    int data[n];
    char c;
    while (scanf("%d%c", &data[i],&c) == 2 && i < n) {
        i++;
        if(InQueue(&L,data[i-1]) == ERROR) {
            printf("Failed to insert data into queue.\n");
            DestroyQueue(&L);
            return 1;
        }
        if(c!=',')
            break;
    }
    ElemType e;
    for(i=0;i<n-1;i++){
        if(OutQueue(&L,&e) == ERROR) {
            printf("Failed to remove data from queue.\n");
            DestroyQueue(&L);
            return 1;
        }
        printf("%d,",e);
    }
    if(OutQueue(&L,&e) == ERROR) {
        printf("Failed to remove data from queue.\n");
        DestroyQueue(&L);
        return 1;
    }
    printf("%d\n",e);
    DestroyQueue(&L);
    return 0;
}