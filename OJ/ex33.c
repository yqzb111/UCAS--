#include <stdio.h>
#include <stdlib.h>

#define OVERFLOW -1

typedef int Status;
typedef int ElemType;

// 十字链表节点结构
typedef struct OLNode {
    int i, j;
    ElemType e;
    struct OLNode *right, *down;
} OLNode, *Olink;

// 十字链表结构
typedef struct {
    Olink *rhead, *chead;
    int mu, nu;
} CrossList;

int m, n;

// 创建十字链表 时间复杂度: O(s)，其中 s 是稀疏矩阵中的非零元素数量
Status CreateCrossList(CrossList *M, int m, int n, int *V, int B[][n]) {
    M->mu = m;
    M->nu = n;
    if (!(M->rhead = (Olink *)malloc((m + 1) * sizeof(Olink))))
        return OVERFLOW;
    if (!(M->chead = (Olink *)malloc((n + 1) * sizeof(Olink))))
        return OVERFLOW;
    // 初始化行和列链表头指针向量
    for (int i = 0; i < m; i++)
        M->rhead[i] = NULL;
    for (int j = 0; j < n; j++)
        M->chead[j] = NULL;
    // 读入稀疏矩阵元素
    int k = 0; // V数组的索引
    OLNode *p, *q;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (B[i][j] != 0 && V[k] != 0) {
                if (!(p = (OLNode *)malloc(sizeof(OLNode))))
                    exit(OVERFLOW);
                p->i = i;
                p->j = j;
                p->e = V[k];
                p->right = NULL;
                p->down = NULL;
                // 插入到行链表
                if (M->rhead[i] == NULL || M->rhead[i]->j > j) {
                    p->right = M->rhead[i];
                    M->rhead[i] = p;
                } else {
                    for (q = M->rhead[i]; (q->right) && q->right->j < j; q = q->right)
                        ;
                    p->right = q->right;
                    q->right = p;
                }
                // 插入到列链表
                if (M->chead[j] == NULL || M->chead[j]->i > i) {
                    p->down = M->chead[j];
                    M->chead[j] = p;
                } else {
                    for (q = M->chead[j]; (q->down) && q->down->i < i; q = q->down)
                        ;
                    p->down = q->down;
                    q->down = p;
                }
                k++;
            }
        }
    }
    return 0;
}

// 输出十字链表 时间复杂度: O(s)，其中 s 是稀疏矩阵中的非零元素数量
void ChangeCrossList(CrossList *M, int *V, int B[][n]) {
    int k = 0;
    for (int i = 0; i < M->mu; i++) {
        OLNode *p = M->rhead[i];
        for (int j = 0; j < M->nu; j++) {
            if (p != NULL && p->j == j) {
                B[i][j] = 1;
                V[k++] = p->e;
                p = p->right;
            } else {
                B[i][j] = 0;
            }
        }
    }
}

// 矩阵相加 时间复杂度: O(s1 + s2)，其中 s1 和 s2 分别是两个稀疏矩阵中的非零元素数量
void MatrixAddition(CrossList *M1, CrossList *M2, CrossList *Sum) {
    Sum->mu = M1->mu;
    Sum->nu = M1->nu;
    Sum->rhead = (Olink *)malloc((M1->mu + 1) * sizeof(Olink));
    Sum->chead = (Olink *)malloc((M1->nu + 1) * sizeof(Olink));
    for (int i = 0; i < Sum->mu + 1; i++)
        Sum->rhead[i] = NULL;
    for (int j = 0; j < Sum->nu + 1; j++)
        Sum->chead[j] = NULL;

    for (int i = 0; i < M1->mu; i++) {
        Olink p1 = M1->rhead[i];
        Olink p2 = M2->rhead[i];
        Olink tail = NULL; // 用于记录Sum的当前行的最后一个节点

        while (p1 || p2) {
            int col;
            ElemType e;
            Olink p;
            if (p2 == NULL || (p1 && p1->j < p2->j)) {
                col = p1->j;
                e = p1->e;
                p1 = p1->right;
            } else if (p1 == NULL || (p2 && p2->j < p1->j)) {
                col = p2->j;
                e = p2->e;
                p2 = p2->right;
            } else {
                col = p1->j;
                e = p1->e + p2->e;
                p1 = p1->right;
                p2 = p2->right;
            }

            if (e != 0) {
                p = (Olink)malloc(sizeof(OLNode));
                p->i = i;
                p->j = col;
                p->e = e;
                p->right = NULL;
                p->down = NULL;

                if (Sum->rhead[i] == NULL)
                    Sum->rhead[i] = p;
                else
                    tail->right = p;
                tail = p;

                if (Sum->chead[col] == NULL) {
                    Sum->chead[col] = p;
                } else {
                    Olink q = Sum->chead[col];
                    while (q->down)
                        q = q->down;
                    q->down = p;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &m, &n);
    int V1[m * n], V2[m * n];
    for (int i = 0; i < m * n; i++) {
        V1[i] = 0;
        V2[i] = 0;
    }

    char c;
    c = getchar();
    if ((c = getchar()) != '\n' && c != '\0') {
        ungetc(c, stdin);
        int i = 0;
        while (scanf("%d", &V1[i]) == 1) {
            i++;
            c = getchar();
            if (c == '\n')
                break;
        }
    }

    int B1[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B1[i][j]);
        }
    }
    c = getchar();
    if ((c = getchar()) != '\n' && c != '\0') {
        ungetc(c, stdin);
        int i = 0;
        while (scanf("%d", &V2[i]) == 1) {
            i++;
            c = getchar();
            if (c == '\n')
                break;
        }
    }

    int B2[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B2[i][j]);
        }
    }
    CrossList M1, M2, Sum;
    CreateCrossList(&M1, m, n, V1, B1);
    CreateCrossList(&M2, m, n, V2, B2);
    MatrixAddition(&M1, &M2, &Sum);
    int V[m * n], B[m][n];
    for (int i = 0; i < m * n; i++) {
        V[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            B[i][j] = 0;
        }
    }
    ChangeCrossList(&Sum, V, B);
    int k = 0;
    if (V[0] == 0) {
        printf("\n");
    }
    while (V[k] != 0 && k < m * n) {
        if (V[k + 1] != 0 && k < m * n - 1)
            printf("%d ", V[k]);
        else
            printf("%d\n", V[k]);
        k++;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n - 1; j++) {
            printf("%d ", B[i][j]);
        }
        printf("%d\n", B[i][n - 1]);
    }
    // 释放动态分配的内存
    for (int i = 0; i < m; i++) {
        Olink p1 = M1.rhead[i];
        Olink p2 = M2.rhead[i];
        Olink p3 = Sum.rhead[i];
        Olink temp;
        while (p1) {
            temp = p1;
            p1 = p1->right;
            free(temp);
        }
        while (p2) {
            temp = p2;
            p2 = p2->right;
            free(temp);
        }
        while (p3) {
            temp = p3;
            p3 = p3->right;
            free(temp);
        }
    }
    free(M1.rhead);
    free(M1.chead);
    free(M2.rhead);
    free(M2.chead);
    free(Sum.rhead);
    free(Sum.chead);
    return 0;
}