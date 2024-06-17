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
    int vexnum, edgenum;
    struct
    {
        ElemType vertex;
        NodeLink *first; // 指向第一个表结点
    } v[MAX_VERTEX_NUM];
} AGraph;

void CreateGraph(AGraph *g,int n,int m,int a[],int b[]){
    int i,j,e=0;
    NodeLink *p,*q,*s;
    char x,y;
    g->vexnum = n;
    g->edgenum = m;
    for(i=0;i<=n;i++){
        g->v[i].vertex = i;
        g->v[i].first = NULL;
    }
    for(i=0;i<m;i++){
        s = (NodeLink *)malloc(sizeof(NodeLink));
        s->vindex = b[i];
        if(g->v[a[i]].first == NULL || g->v[a[i]].first->vindex < s->vindex){
            s->next = g->v[a[i]].first;
            g->v[a[i]].first = s;
        }
        else{
            p = g->v[a[i]].first;
            while(p!=NULL && b[i]<p->vindex)
                p = p->next;
            q = g->v[a[i]].first;
            while(q->next != p)
                q = q->next;
            s->next = q->next;
            q->next = s;
        }
    }
}

void ListGraph(AGraph *g,int a[],int b[]){
    int i;
    int state = 1;
    NodeLink *p;
    for(i=0;i<g->edgenum;i++){
        if(a[i]==0 || b[i]==0)
            state = 0;
    }
    if(state == 0){
    for(i=0;i<g->vexnum;i++){
        printf("%d ",g->v[i].vertex);
        p = g->v[i].first;
        while(p!=NULL){
            printf("%d",p->vindex);
            if(p->next != NULL)
                printf(",");
            p = p->next;
        }
        printf("\n");
    }
    }
    else{
    for(i=1;i<=g->vexnum;i++){
        printf("%d",g->v[i].vertex);
        p = g->v[i].first;
        if(p!=NULL)
            printf(" ");
        while(p!=NULL){
            printf("%d",p->vindex);
            if(p->next != NULL)
                printf(",");
            p = p->next;
        }
        printf("\n");
    }
    }
}

int main(){
    int n,m,i;
    char c,d;
    AGraph *g = (AGraph *)malloc(sizeof(AGraph));
    scanf("%d%c%d",&n,&c,&m);
    int a[m],b[m];
    c = getchar();
    for(i=0;i<m;i++){
        scanf("%d%c%d%c",&a[i],&c,&b[i],&d);
    }
    CreateGraph(g,n,m,a,b);
    ListGraph(g,a,b);
    return 0;
}
