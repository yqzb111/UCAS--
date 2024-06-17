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


void *Reverse_L() {
//建立含头结点的单链表L
LinkList *L,*p,*q; 
int i=0,j;
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
  p->data = value[count-i];
  p->next = L->next;
  L->next = p;  // 插入到表头
 }
 q=L->next;
 while(q->next!=NULL){
    printf("%c,",q->data);
    q=q->next;
 }
printf("%c\n",q->data);
}

int main(){
    Reverse_L();
    return 0;
}