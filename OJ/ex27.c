#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define CHUNKSIZE 80
#define OK 1
#define ERROR 0

typedef struct Chunk{
    char ch;
    struct Chunk *next;
    struct Chunk *prior;
}Chunk;

typedef struct{
    Chunk *head;
    Chunk *tail;
    int curLen;
}LString;

typedef int Status;

LString *InitStr() {
    LString *L = (LString *)malloc(sizeof(LString));
    if (L == NULL) {
        return ERROR;
    }
    L->head = NULL;
    L->tail = NULL;
    L->curLen = 0;
    return L;
}

Status InsertNode(LString *L, char str) {
    Chunk *newChunk = (Chunk *)malloc(sizeof(Chunk));
    if (newChunk == NULL) {
        return ERROR;
    }
    newChunk->ch = str;
    newChunk->prior = NULL;
    newChunk->next = NULL;
    if (L->head == NULL) {
        L->head = newChunk;
        L->tail = newChunk;
    } else {
        newChunk->prior = L->tail;
        L->tail->next = newChunk;
        L->tail = newChunk;
    }
    L->curLen++;
    return OK;
}

Status IsSymmetry(LString *L){
    Chunk *p,*q;
    p = L->head;
    q = L->tail;
    while(p!=q){
        if(p->ch == q->ch){
            p = p->next;
            q = q->prior;
        }
        else{
            return 0;
        }
    }
    return 1;
}

int main(){
    int length;
    int state;
    int i;
    scanf("%d", &length);
    char input[CHUNKSIZE];
    scanf("%s", input);
    LString *L = InitStr();
    if (L == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    for (i = 0; i < length; i++) {
        InsertNode(L, input[i]);
    }
    Chunk *p = L->head;
    state = IsSymmetry(L);
    printf("%d\n",state);
    free(L);
    return 0;
}