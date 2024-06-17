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

int longestPathUtil(AGraph *g, int u, int *longestPath, int *visited) {
    if (visited[u]) 
        return longestPath[u];  
    visited[u] = 1; 
    int max_length = 0;  
    NodeLink *p = g->v[u].first; 
    while (p) {
        int length = longestPathUtil(g, p->vindex, longestPath, visited);  // 递归计算
        if (length > max_length) 
            max_length = length;  // 更新最长路径长度
        p = p->next; 
    }
    longestPath[u] = max_length + 1;  // 计算当前节点的最长路径长度
    return longestPath[u];
}

void LongestPath(AGraph *g) {
    int longestPath[MAX_VERTEX_NUM] = {0};  // 存储每个顶点的最长路径长度
    int visited[MAX_VERTEX_NUM] = {0};  
    int i;
    for (int i = 0; i < g->vexnum; i++) {
        if (!visited[i]) {  // 如果未访问
            longestPathUtil(g, i, longestPath, visited);  // 计算最长路径
        }
    }
    for (i = 0; i < g->vexnum-1; i++) {
        printf("%d,", longestPath[i] - 1);  // 输出最长路径长度，减1是因为包含了起始节点
    }
    printf("%d\n", longestPath[i]-1);  // 输出最后一个顶点的最长路径长度
}

int main() {
    int n, m = 0;
    scanf("%d", &n);  
    getchar(); 
    char buffer[1024];
    fgets(buffer, 1024, stdin);  
    AGraph *g = (AGraph *)malloc(sizeof(AGraph)); 
    int a[MAX_VERTEX_NUM], b[MAX_VERTEX_NUM];
    char *token = strtok(buffer, ",");  
    while (token != NULL) {
        sscanf(token, "%d-%d", &a[m], &b[m]);  
        a[m]--; b[m]--; 
        m++;
        token = strtok(NULL, ",");
    }
    CreateGraph(g, n, m, a, b);  
    LongestPath(g);  
    return 0;
}
