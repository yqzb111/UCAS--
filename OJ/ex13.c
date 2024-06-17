#include "stdio.h"
#include "stdlib.h"

int t = 1;

typedef int ElemType;
typedef struct node {
    ElemType data;
    ElemType freq;
    ElemType time;
    struct node* prior;
    struct node* next;
} DoubleLinkedList;

DoubleLinkedList* CreateDoubleLinkedList(int n) {
    DoubleLinkedList* head, * p, * s;
    int i;
    head = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
    head->next = NULL;
    head->prior = NULL;
    p = head;
    p->time = 0;
    p->freq = 0; // 将初始化频率设为0
    for (i = 1; i <= n; i++) {
        s = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
        scanf("%d", &s->data);
        s->freq = 0;
        s->time = 0; // 将初始化时间设为0
        s->prior = p;
        s->next = NULL;
        p->next = s;
        p = s;
    }
    return head;
}

void PrintList(DoubleLinkedList* head) {
    DoubleLinkedList* p;
    p = head->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void insert(DoubleLinkedList* pa, DoubleLinkedList* pb) {
    pb->prior = pa->prior;
    pb->next = pa;
    if (pa->prior != NULL) {
        pa->prior->next = pb;
    }
    pa->prior = pb;
}

void Locate(DoubleLinkedList* L, ElemType x) {
    DoubleLinkedList* p, * q, * tail;
    // 获取待移动节点
    p = L->next;
    while (p != NULL && p->data != x) {
        p = p->next;
    }
    if (p == NULL) {
        return;
    }
    else if (p->data == x) {
        if (p->freq == 0) {
            p->time = t;
            t++;
        }
        p->freq++;
    }
    q = p;
    tail = L;
    // 删除待移动的结点
    if (q->prior != NULL) {
        q->prior->next = q->next;
    }
    if (q->next != NULL) {
        q->next->prior = q->prior;
    }
    for (p = L->next; p != NULL; p = p->next) {
        if (p->freq < q->freq || (p->freq == q->freq && p->time > q->time)) {
            insert(p, q);
            break;
        }
        tail = p;
    }
    // 如果没有找到合适的位置，将节点插入尾部
    if (p == NULL) {
        q->prior = tail;
        tail->next = q;
        q->next = NULL;
    }
}

int main() {
    DoubleLinkedList* L;
    int n;
    int x;
    scanf("%d", &n);
    L = CreateDoubleLinkedList(n);
    while (scanf("%d", &x) == 1) {
        Locate(L, x);
        char c = getchar(); // 读取换行符
        if (c == '\n') break; // 如果是换行符，则退出循环
    }
    PrintList(L);
    return 0;
}