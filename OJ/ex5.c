#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE  100 //线性表初始大小
#define LISTINCREMENT 10 //线性表增量大小
#define OVERFLOW -1
#define OK 0
#define ERROR 1

typedef int ElemType;
typedef int Status;

typedef struct {
    ElemType *elem;
    int listsize;
    int length;
} SqList;

Status InitList_Sq(SqList *va) {
    //构造一个空的、容量为LIST_INIT_SIZE的线性表va
    va->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!va->elem) return OVERFLOW;    //存储分配失败
    va->length = 0;                    //空表长度为0
    va->listsize = LIST_INIT_SIZE;     //初始存储容量
    return OK;
} // InitList_Sq

Status ListInsert_Sq(SqList *va, ElemType x) {
    ElemType *p, *q;
    int i = 0;
    if (va->length >= va->listsize) {
        // 当前存储空间已满，增加容量
        ElemType *newbase =
                (ElemType *) realloc(va->elem, (va->listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase) return ERROR; // 存储分配失败
        va->elem = newbase; //新的基地址
        va->listsize += LISTINCREMENT; //新的存储容量
    }

    while (i < va->length && va->elem[i] < x)
        i++;

    q = &(va->elem[i]);
    //插入位置及之后的元素右移
    for (p = &(va->elem[va->length - 1]); p >= q; --p)
        *(p + 1) = *p;
    *q = x;         //插入x
    ++va->length;    //表长增1
    return OK;
}//ListInsert_Sq

int main() {
    SqList va;
    int i = 0;
    int x;
    InitList_Sq(&va);

    while (scanf("%d", &va.elem[i]) == 1 && i < 100) {
        i++;
        va.length++;
        char c = getchar(); // 读取换行符
        if (c == '\n') break; // 如果是换行符，则退出循环
    }

    // 读取待插入的元素
    scanf("%d", &x);

    // 插入元素到顺序表
    ListInsert_Sq(&va, x);

    // 输出插入后的结果
    for (i = 0; i < va.length; i++)
        printf("%d ", va.elem[i]);

    return 0;
}