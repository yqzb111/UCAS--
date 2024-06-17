#include <stdio.h>

int main() {
    int m, n, i, j;
    scanf("%d %d", &m, &n);

    int V1[m * n], V2[m * n];
    for (i = 0; i < m * n; i++) {
        V1[i] = 0;
        V2[i] = 0;
    }

    char c;
    c = getchar();
    if ((c = getchar()) != '\n' && c!='\0') {
        ungetc(c, stdin); 
        i = 0;
        while (scanf("%d", &V1[i]) == 1) {
            i++;
            c = getchar(); 
            if (c == '\n') break; 
        }
    }

    int B1[m][n];
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &B1[i][j]);
        }
    }
    c = getchar();
    if ((c = getchar()) != '\n' && c!='\0') {
        ungetc(c, stdin); 
        i = 0;
        while (scanf("%d", &V2[i]) == 1) {
            i++;
            c = getchar(); 
            if (c == '\n') break; 
        }
    }

    int B2[m][n];
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &B2[i][j]);
        }
    }

    int V[m * n], B[m][n];
    for (i = 0; i < m * n; i++) {
        V[i] = 0;
    }
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            B[i][j] = 0;
        }
    }

    int k = 0, t = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (B1[i][j] != 0 && B2[i][j] != 0) {
                B[i][j] = V1[k] + V2[t];
                k++;
                t++;
            } else if (B1[i][j] != 0 && B2[i][j] == 0) {
                B[i][j] = V1[k];
                k++;
            } else if (B1[i][j] == 0 && B2[i][j] != 0) {
                B[i][j] = V2[t];
                t++;
            }
        }
    }

    k = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (B[i][j] != 0) {
                V[k] = B[i][j];
                k++;
                B[i][j] = 1;
            }
        }
    }

    k = 0;
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
    for (i = 0; i < m; i++) {
        for (j = 0; j < n - 1; j++) {
            printf("%d ", B[i][j]);
        }
        printf("%d\n", B[i][j]);
    }

    return 0;
}