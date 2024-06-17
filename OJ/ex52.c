#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX_NUM 30  

typedef struct node {
    int vindex;     
    char val;       
    struct node *next;     
} NodeLink;

typedef struct {
    int vexnum, edgenum;   
    struct {
        int vertex;    
        char val;    
        NodeLink *first;   
    } v[MAX_VERTEX_NUM];
} AGraph;

void CreateGraph(AGraph *g, int n, char val[MAX_VERTEX_NUM], int left[MAX_VERTEX_NUM], int right[MAX_VERTEX_NUM]){
    g->vexnum = n;
    NodeLink *p,*q,*s;
    int i;
    for(i=0;i<n;i++){
        g->v[i].vertex = i;
        g->v[i].val = val[i];
        g->v[i].first = NULL;
    }
    for(i=0;i<n;i++){
        if(right[i]!=-1){
            s = (NodeLink *)malloc(sizeof(NodeLink));
            s->vindex = right[i];
            s->val = val[right[i]];
            s->next = g->v[i].first;
            g->v[i].first = s;
        }
        if(left[i]!=-1){
            s = (NodeLink *)malloc(sizeof(NodeLink));
            s->vindex = left[i];
            s->val = val[left[i]];
            s->next = g->v[i].first;
            g->v[i].first = s;
        }
    }
}

void DFS(AGraph *g, int node, int *visited, char *rpn, int *index){
    visited[node] = 1;

    NodeLink *current = g->v[node].first;
    while(current != NULL){
        if(!visited[current->vindex]){
            DFS(g, current->vindex, visited, rpn, index);
        }
        current = current->next;
    }

    rpn[(*index)++] = g->v[node].val;
}

void generateRPN(AGraph *g, char *rpn){
    int visited[MAX_VERTEX_NUM] = {0};
    int index = 0;

    for(int i = 0; i < g->vexnum; ++i){
        if(!visited[i]){
            DFS(g, i, visited, rpn, &index);
        }
    }
    rpn[index] = '\0';
}

int main(){
    int n,i;
    char c = 0;
    AGraph *g = (AGraph *)malloc(sizeof(AGraph)); 
    scanf("%d",&n);
    getchar(); // 读取换行符
    char val[MAX_VERTEX_NUM];
    int left[MAX_VERTEX_NUM];
    int right[MAX_VERTEX_NUM];
    for(i=0;i<n;i++){
        scanf("%c%c",&val[i],&c); // 读取节点值
        if(c == '\n'){
            right[i] = -1;
            left[i] = -1;
        }
        while(c!='\n'){
            scanf("%d%d%c",&right[i],&left[i],&c); // 读取左右节点索引
        }
    }
    CreateGraph(g,n,val,left,right);
    char rpn[MAX_VERTEX_NUM]; // 存储逆波兰表达式
    generateRPN(g, rpn);
    printf("%s\n", rpn);
    // 释放分配的内存
    for (i = 0; i < n; i++) {
        NodeLink *temp, *next;
        temp = g->v[i].first;
        while (temp != NULL) {
            next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(g);
    return 0;
}
