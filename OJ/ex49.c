#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAX_VERTEX_NUM 30

typedef int ElemType;

typedef struct node
{
    int vindex;        // 邻接点在头结点数组中的位置(下标)
    struct node *next; // 指向下一个表结点
} NodeLink;            // 表结点类型定义

typedef struct
{
    // 图的顶点数、边数、种类标志
    int vexnum;
    struct
    {
        ElemType vertex;
        NodeLink *first; // 指向第一个表结点
    } v[MAX_VERTEX_NUM];
} AGraph;

void CreateGraph(AGraph *g,int n,int s[],int fst[],int lst[]){
    int i,j,e=0;
    NodeLink *p,*q,*t;
    char x,y;
    g->vexnum = n;
    for(i=0;i<=n;i++){
        g->v[i].vertex = i;
        g->v[i].first = NULL;
    }
    for(i=1;i<=n;i++){
        for(j=fst[i];j<lst[i];j++){
            t = (NodeLink *)malloc(sizeof(NodeLink));
            t->vindex = s[j];
            t->next = g->v[i].first;
            g->v[i].first = t;
        }
    }
}

void ListGraph(AGraph *g){
    int i;
    NodeLink *p;
    for(i=1;i<=g->vexnum;i++){
        printf("%d ",g->v[i].vertex);
        p = g->v[i].first;
        while(p!=NULL){
            printf("%d",p->vindex);
            if(p->next != NULL)
                printf(" ");
            p = p->next;
        }
        printf("\n");
    }
}

int DFSUtil(AGraph *g, int x, int y, int visited[]) {
    visited[x] = 1;
    NodeLink *p = g->v[x].first;
    if (x == y) return 1;
    while (p != NULL) {
        if (!visited[p->vindex] && DFSUtil(g, p->vindex, y, visited))
            return 1;
        p = p->next;
    }
    return 0;
}

int DFS(AGraph *g, int x, int y) {
    int visited[MAX_VERTEX_NUM] = {0};
    return DFSUtil(g, x, y, visited);
}

int IsCircle(AGraph *g){
    int i,state;
    NodeLink *p;
    for(i=1;i<=g->vexnum;i++){
        p = g->v[i].first;
        while(p){
        state = DFS(g,p->vindex,g->v[i].vertex);
        if(state == 1)
            return 1;
        else{
            p = p->next;
        }
        }
    }
    return 0;
}

int main(){
    int n,i=0;
    int state,count;
    char c,d;
    AGraph *g = (AGraph *)malloc(sizeof(AGraph));;
    scanf("%d%c",&n,&c);
    int s[MAX_VERTEX_NUM],fst[n+1],lst[n+1];
    while((scanf("%d%c",&s[i],&c) == 2)){
        i++;
        if(c == '\n')
            break;
    }
    count = i-1;
    for(i=0;i<=n;i++){
        scanf("%d%c",&fst[i],&c);
    }
    for(i=0;i<=n;i++){
        scanf("%d%c",&lst[i],&c);
    }
    CreateGraph(g,n,s,fst,lst);
    state = IsCircle(g);
    if(state == 1)
        printf("yes\n");
    else
        printf("no\n");
    return 0;
}