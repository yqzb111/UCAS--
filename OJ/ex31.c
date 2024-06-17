#include <stdio.h>

int main(){
    int m,n;
    scanf("%d %d", &n, &m);
    int a[n+1][m+1];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    int state = 1;
    for (int x = n; x >= 1; x--){
        for (int y = m; y >= 1; y--){
            if (a[x][y] == 0) 
                continue;
            if (!state) 
                printf("+");
            else 
                state = 0;
            if (x == 1 && y == 1){
                printf("%d", a[x][y]);
                continue;
            }
            if (a[x][y] != 1)
                printf("%d", a[x][y]);
            if (x >= 2)
                printf("xE%d", x - 1);
            if (y >= 2)
                printf("yE%d", y - 1);
        }
    }
    if (state) 
        printf("0");
    return 0;
}