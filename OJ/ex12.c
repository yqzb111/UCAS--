#include <stdio.h>
#include <malloc.h>
#include<string.h>
#define OK 0
#define ERROR 1
#define MAX 100

typedef char ElemType;
typedef int Status;
typedef  struct  LNode {
 	ElemType  data;     /*数据域，保存结点的值 */
	struct   LNode  *next;      /*指针域*/
} LNode, LinkList;        /*结点的类型 */


LinkList *CreateList_L() {
//建立含头结点的单链表L
LinkList *L,*p; 
int i=0;
int count=0;
char value[MAX];
char c;
while ((scanf("%c%c", &value[i], &c) == 2) && i < MAX) {
        count++;
        i++;
        if (c != ',') break; // 如果是换行符，则退出循环
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

void DELETE(LinkList *L, char data) {
LinkList *p,*q;
p = L->next;
q = L;
int i = 0;
while (p) {
    if(p->data != data){
        p=p->next;
    }
    else{
        while(q->next!=p){
            q=q->next;
        }
        q->next = p->next; // 删除并释放结点
        free(p);
        p=q->next;
    } 
    }
}

Status GetElem_L(LinkList *L, ElemType data) {
// L为带头结点的单链表的头指针
// 当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
// 初始化，p指向第一个结点，j为计数器
LinkList *p;
 p = L->next;
while (p && (p->data!=data)) {
      p = p->next;
    }
if (!p) 
    return ERROR; // 第i个元素不存在
return OK;
} // GetElem_L

int main(){
    LinkList *A,*B,*C,*p,*q;
    A = CreateList_L();
    B = CreateList_L();
    C = CreateList_L();
    p = B->next;
    while(p!=NULL){
        if(GetElem_L(C,p->data) == OK){
            DELETE(A,p->data);
        }
        p = p->next;
    }
    q=A->next;
while(q->next != NULL){
  printf("%c,",q->data);
  q=q->next;
}
printf("%c\n",q->data);
    return 0;
}