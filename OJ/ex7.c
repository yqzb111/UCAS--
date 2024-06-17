#include <stdio.h>
#include <math.h>

// 计算多项式的值
int polynomial_value(int x, int n, int coefficients[]) {
    int value = 0;
    int i;
    for (i = 0; i <= n; i++) {
        value += coefficients[i] * pow(x, i);
    }
    return value;
}

int main() {
    int x;
    int n;
    scanf("%d %d", &x, &n);
    // 系数数组
    int coefficients[n + 1];
    // 输入系数
    int i;
    for (i = 0; i <= n; i++) {
        scanf("%d", &coefficients[i]);
    }
    int result = polynomial_value(x, n, coefficients);
    printf("%d\n", result);
    return 0;
}