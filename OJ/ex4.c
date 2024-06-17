#include <stdio.h>

int main() {
    int arrsize, n;
    scanf("%d %d", &n, &arrsize);
    if (n > arrsize) {
        printf("-1\n");
        return 0;
    }
    unsigned long long MAXINT = (1ULL << 32) - 1;
    unsigned int a[arrsize];
    int i, j;
    for (i = 0; i < n; i++) {
        long long t1 = 1, t2 = 1;
        for (j = 1; j <= i; j++) {
            t1 *= j;
            t2 *= 2;
        }
        a[i] = t1 * t2;
        if (t1*t2 > MAXINT) {
            printf("-1\n");
            return 0;
        }
    }
    for (i = 0; i < n; i++) {
        printf("%u ", a[i]);
    }
    printf("\n");
    return 0;
}