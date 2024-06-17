#include <stdio.h>
#include <stdlib.h>

#define INFINITY 1000
#define MAX_VERTEX_NUM 30

typedef struct
{
    int vexnum;                       // 顶点数
    int vexs[MAX_VERTEX_NUM];                // 存放顶点信息
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 存放边的信息
} MGraph;

void CreateGraph(MGraph *g,int n){
	g->vexnum = n;
	int i,j;
	for(i = 0;i<n;i++){
		g->vexs[i] = i+1;
	}
	for (i = 0; i < g->vexnum; i++)
        for (j = 0; j < g->vexnum; j++)
        {
            if (i == j)
                g->arcs[i][j] = 0;
            else
                g->arcs[i][j] = INFINITY;
        }
	int x,y,val;
	char c,d,e;
	while(scanf("%d%c%d%c%d%c",&x,&c,&y,&d,&val,&e)==6){
		g->arcs[x-1][y-1] = val;
	}
}

void ShortestPath_DIJ(MGraph *g, int v0, int P[][MAX_VERTEX_NUM], int dist[])
{
	int i = 0, j, v, w, min;
	int final[MAX_VERTEX_NUM];
	for (v = 0; v < g->vexnum; v++)
	{
		final[v] = 0;
		dist[v] = g->arcs[v0][v];
		for (w = 0; w < g->vexnum; w++)
			P[v][w] = 0; // 设空路径
		if (dist[v] < INFINITY)
		{
			P[v][v0] = 1;
			P[v][v] = 1;
		}
	}
	dist[v0] = 0;
	final[v0] = 1; // 初始化，v0顶点属于S集
	// 主循环：每次求得v0到某个v顶点的最短路径并加v到S集
	for (i = 1; i < g->vexnum; i++)
	{					// 其余g->vexnum-1个顶点
		min = INFINITY; // 当前所知离v0顶点的最近距离
		for (w = 0; w < g->vexnum; ++w)
			if (!final[w])		   // w顶点在V-S中
				if (dist[w] < min) // w顶点离v0顶点更近
				{
					v = w;
					min = dist[w];
				}
		final[v] = 1; // 离v0顶点最近的v加入S集
		// 更新当前最短路径及距离
		for (w = 0; w < g->vexnum; w++)
			if (!final[w] && (min + g->arcs[v][w] < dist[w]))
			{
				// 修改dist[w]和P[w], w∈V-S
				dist[w] = min + g->arcs[v][w];
				for (j = 0; j < g->vexnum; j++)
					P[w][j] = P[v][j];
				// 第v行赋值于第w行
				P[w][w] = 1; // P[w] = P[v]+[w]
			}				 // if
	}						 // for
	for (i = 0; i < v0; i++)
		printf("%d,", dist[i]);
	for(i = v0+1; i < g->vexnum-1; i++)
		printf("%d,", dist[i]);
	printf("%d\n",dist[i]);
}

int main(){
    int n,v0;
    scanf("%d %d",&n,&v0);
    MGraph *g = (MGraph *)malloc(sizeof(MGraph));
    CreateGraph(g,n);
    int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int D[MAX_VERTEX_NUM];
	ShortestPath_DIJ(g, v0-1, P, D);
	free(g);
	return 0;
}