#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE  100 //线性表初始大小
#define LISTINCREMENT 10 //线性表增量大小
#define OVERFLOW -1
#define OK 0
#define ERROR 1
#define LESS 1
#define GREATER 2

typedef char ElemType;
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

Status compare(ElemType a, ElemType b)
{
    if ((int)a < (int)b) return LESS;
    if ((int)a > (int)b) return GREATER;
    return 0;
}

int main(){
    SqList A,B;
    InitList_Sq(&A);
    InitList_Sq(&B);
    int i=0;
    int state;
    char c;
    while (scanf("%c%c", &A.elem[i],&c) == 2 && i < 100) {
        i++;
        A.length++;
        if(c!=',')
            break;
    }

    i=0;
    while (scanf("%c%c", &B.elem[i],&c) == 2 && i < 100) {
        i++;
        B.length++;
        if(c!=',')
            break;        
    }

    i=0;
    int min_length = A.length < B.length ? A.length : B.length;
    while(i < min_length){
        state = compare(A.elem[i], B.elem[i]);
        if(state == 0)
            i++;
        else
            break;
    }
    if(state==0 && B.length<A.length)
        state = 2;
    else if(state==0 && B.length>A.length)
        state = 1;
    printf("%d\n",state);
    //printf("%d %d\n",A.length,B.length);
    //printf("%c %c\n",A.elem[1],B.elem[2]);
    return 0;
}