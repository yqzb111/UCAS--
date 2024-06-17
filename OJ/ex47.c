#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX_NUM 20

typedef struct {
    int matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum;  // 当前顶点数
} Graph;

// 在指定位置插入新顶点
void InsertVex(Graph *G, int v) {
    if (G->vexnum >= MAX_VERTEX_NUM) {
        printf("Error: Exceeding maximum vertex number.\n");
        return;
    }
    if (v > G->vexnum) v = G->vexnum;  // 确保不会在非连续的位置插入
    // 移动行
    for (int i = G->vexnum; i > v; i--) {
        for (int j = 0; j < G->vexnum; j++) {
            G->matrix[i][j] = G->matrix[i-1][j];
        }
    }
    // 移动列
    for (int j = G->vexnum; j > v; j--) {
        for (int i = 0; i <= G->vexnum; i++) {  // <= 因为新行已经被增加
            G->matrix[i][j] = G->matrix[i][j-1];
        }
    }
    // 初始化新顶点的行和列
    for (int i = 0; i <= G->vexnum; i++) {
        G->matrix[v][i] = 0;
        G->matrix[i][v] = 0;
    }
    G->vexnum++;
}

// 插入新边
void InsertArc(Graph *G, int v, int w) {
    if (v >= G->vexnum || w >= G->vexnum) {
        printf("Error: Vertex index out of bound.\n");
        return;
    }
    G->matrix[v][w] = 1;
    G->matrix[w][v] = 1;
}

// 删除顶点
void DeleteVex(Graph *G, int v) {
    if (v >= G->vexnum) {
        printf("Error: Vertex index out of bound.\n");
        return;
    }
    int n = G->vexnum;
    // 移除行和列
    for (int i = v; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            G->matrix[i][j] = G->matrix[i + 1][j];
        }
    }
    for (int j = v; j < n - 1; j++) {
        for (int i = 0; i < n; i++) {
            G->matrix[i][j] = G->matrix[i][j + 1];
        }
    }
    G->vexnum--;
}

// 删除边
void DeleteArc(Graph *G, int v, int w) {
    if (v >= G->vexnum || w >= G->vexnum) {
        printf("Error: Vertex index out of bound.\n");
        return;
    }
    G->matrix[v][w] = 0;
    G->matrix[w][v] = 0;
}

// 打印邻接矩阵
void PrintMatrix(Graph *G) {
    int i,j;
    for (i = 0; i < G->vexnum; i++) {
        for (j = 0; j < G->vexnum-1; j++) {
            printf("%d ", G->matrix[i][j]);
        }
        printf("%d\n",G->matrix[i][j]);
    }
}

int main() {
    Graph G = {0};
    int initialVertexCount;
    scanf("%d", &initialVertexCount);
    G.vexnum = initialVertexCount;

    for (int i = 0; i < G.vexnum; i++) {
        for (int j = 0; j < G.vexnum; j++) {
            scanf("%d", &G.matrix[i][j]);
        }
    }

    char operation[3];
    int v, w;
    while (scanf("%s", operation) != EOF) {
        if (strcmp(operation, "IV") == 0) {
            scanf("%d", &v);
            InsertVex(&G, v);
        } else if (strcmp(operation, "IA") == 0) {
            scanf("%d %d", &v, &w);
            InsertArc(&G, v, w);
        } else if (strcmp(operation, "DV") == 0) {
            scanf("%d", &v);
            DeleteVex(&G, v);
        } else if (strcmp(operation, "DA") == 0) {
            scanf("%d %d", &v, &w);
            DeleteArc(&G, v, w);
        }
    }

    PrintMatrix(&G);
    return 0;
}
