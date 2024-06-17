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
return p;
} // CreateList_L

Status DELETE(LinkList *L, int i) {
//在带头结点的单链表L中删除第i个元素，并返回剩余元素
LinkList *p,*q;
p = L; int j = 0;
if(p->next == NULL){
  printf("NULL\n");
}
if(i==0){
  L = L->next;
  free(p);
}
while (p->next && j < i-1 && p) {
	// 寻找第i个结点，并令p指向其前趋
	p = p->next; ++j;
	}
// i小于1(导致j>i-1成立)或者大于表长(导致p->next为NULL)
if (!(p->next) || j > i-1 || !p) return ERROR;
q = p->next; p->next = q->next; // 删除并释放结点
free(q); 
q=L;
while(q != NULL){
  printf("%d ",q->data);
  q=q->next;
}
printf("\n");
return OK;
} // ListDelete_L

int main(){
    int i;
    LinkList *L;
    L = CreateList_L();
    scanf("%d",&i);
    DELETE(L,i);
    return 0;
}