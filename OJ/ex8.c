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

LinkList *CreateList_L(int n) {
//逆序输入随机生成的n个元素的值
//建立带表头结点的单链表L
LinkList *L,*p; 
int i=0;
int value[n];
while (scanf("%d", &value[i]) == 1 && i < MAX) {
        i++;
        char c = getchar(); // 读取换行符
        if (c == '\n') break; // 如果是换行符，则退出循环
    }
//先建立一个带头结点的空单链表
L = (LinkList *)malloc(sizeof(LNode));
L->next = NULL;
for (i=n; i>0; --i) {
  p = (LinkList *)malloc(sizeof(LNode)); // 生成新结点
  p->data = value[i-1];
  // p->data =random(200);//随机生成一个200以内的数字
  p->next = L->next;
  L->next = p;  // 插入到表头
 }
return L;
} // CreateList_L

int main(){
    LinkList *ha,*hb,*p,*q;
    int m,n;
    scanf("%d %d",&m,&n);
    ha=CreateList_L(m);
    hb=CreateList_L(n);
    p=hb;
    while(p->next!=NULL)
        p=p->next;
    q=ha->next;
    p->next=q;
    q=hb->next;
    while(q!=NULL){
        printf("%d ",q->data);
        q=q->next;
    }
    return 0;
}