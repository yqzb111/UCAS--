#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX_NUM 30

typedef struct node {
    int vindex;
    struct node *next;
} NodeLink;

typedef struct {
    int vexnum, edgenum;
    struct {
        int vertex;
        NodeLink *first;
    } v[MAX_VERTEX_NUM];
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

int DFSUtil(AGraph *g, int x, int y, int visited[], int step) {
    if (x == y) {
        return step; // Return the number of steps if target is reached
    }
    visited[x] = 1;
    NodeLink *p = g->v[x].first;
    while (p != NULL) {
        if (!visited[p->vindex]) {
            int result = DFSUtil(g, p->vindex, y, visited, step + 1);
            if (result != 0) return result; // Return step count if path is found
        }
        p = p->next;
    }
    return 0; // No path found
}

int DFS(AGraph *g, int x, int y, int k) {
    int visited[MAX_VERTEX_NUM] = {0};
    int result = DFSUtil(g, x, y, visited, 0);
    return result == k;
}

int main() {
    int n, m, x, y, k;
    char c;
    scanf("%d%c%d",&n,&c,&k);
    c = getchar();
    scanf("%d%c%d",&x,&c,&y);
    c = getchar();
    x--; y--; 

    char buffer[1024];
    scanf("%s", buffer);

    AGraph *g = (AGraph *)malloc(sizeof(AGraph));
    int a[MAX_VERTEX_NUM], b[MAX_VERTEX_NUM], edgeCount = 0;
    char *token = strtok(buffer, ",");
    while (token != NULL) {
        sscanf(token, "%d-%d", &a[edgeCount], &b[edgeCount]);
        a[edgeCount]--;  
        b[edgeCount]--;  
        edgeCount++;
        token = strtok(NULL, ",");
    }
    CreateGraph(g, n, edgeCount, a, b);

    int state = DFS(g, x, y, k);
    if (state)
        printf("yes\n");
    else
        printf("no\n");

    return 0;
}