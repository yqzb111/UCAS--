#include <stdio.h>
#include <malloc.h>
#include<string.h>
#define OK 0
#define ERROR 1
#define MAX 100

typedef int ElemType;
typedef int Status;
typedef  struct  LNode {
 	ElemType  data;     /*数据域，保存结点的值 */
	struct   LNode  *next;      /*指针域*/
} LNode, LinkList;        /*结点的类型 */


LinkList *CreateList_L() {
//建立无头结点的单链表L
LinkList *L,*p; 
int i=0;
int count=0;
int value[MAX];
while (scanf("%d", &value[i]) == 1 && i < MAX) {
        i++;
        count++;
        char c = getchar(); // 读取换行符
        if (c == '\n') break; // 如果是换行符，则退出循环
    }
//先建立一个带头结点的空单链表
L = (LinkList *)malloc(sizeof(LNode));
L->next = NULL;
for (i=count; i>0; --i) {
  p = (LinkList *)malloc(sizeof(LNode)); // 生成新结点
  p->data = value[i-1];
  p->next = L->next;
  L->next = p;  // 插入到表头
 }
return L;
} // CreateList_L

Status DELETE(LinkList *L, int mink, int maxk) {
//在带头结点的单链表L中删除第i个元素，并返回剩余元素
LinkList *p,*q;
p = L->next;
q = L;
int i = 0;
while (p) {
    if((p->data<=mink || p->data>=maxk)){
        p = p->next; ++i;
    }
    else if(p->data>mink && p->data<maxk){
        while(q->next!=p){
            q=q->next;
        }
        q->next = p->next; // 删除并释放结点
        free(p);
        p=q->next; 
    }
	}
q=L->next;
while(q != NULL){
  printf("%d ",q->data);
  q=q->next;
}
printf("\n");
return OK;
} // ListDelete_L

int main(){
    int mink,maxk;
    LinkList *L;
    L = CreateList_L();
    scanf("%d %d",&mink,&maxk);
    DELETE(L,mink,maxk);
    return 0;
}