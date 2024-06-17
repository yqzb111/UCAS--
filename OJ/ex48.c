#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct node {
    int vindex;
    struct node *next;
} NodeLink;

typedef struct {
    int vexnum, edgenum;
    struct {
        int vertex;
        NodeLink *first;
    } v[MAX];
} AGraph;

void CreateGraph(AGraph *g, int n, int m, int a[], int b[]) {
    g->vexnum = n;
    g->edgenum = m;
    for (int i = 0; i < n; i++) {
        g->v[i].vertex = i;
        g->v[i].first = NULL;
    }
    for (int i = 0; i < m; i++) {
        NodeLink *s = (NodeLink *)malloc(sizeof(NodeLink));
        s->vindex = b[i];
        s->next = g->v[a[i]].first;
        g->v[a[i]].first = s;
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
    int visited[MAX] = {0};
    return DFSUtil(g, x, y, visited);
}

int main(){
    int n,i,m;
    char c,d;
    AGraph *g = (AGraph *)malloc(sizeof(AGraph));;
    scanf("%d",&n);
    int a[MAX],b[MAX];
    c = getchar();
    for(i=0;i<MAX;i++){
        a[i] = -1;
    }
    i=0;
    while(scanf("%d%c%d%c",&a[i],&c,&b[i],&d)==4){
        i++;
    }
    m = i-1;
    CreateGraph(g,n,m,a,b);
    int state = DFS(g,a[m],b[m]);
    if(state == 1)
        printf("yes\n");
    else
        printf("no\n");
    return 0;
}