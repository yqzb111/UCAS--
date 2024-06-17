#include <stdio.h>

#define MAX 1000

int main()
{
    int L[MAX];
    int R[MAX];
    int i = 0, j;
    char c;
    int length = 0;
    int temp;
    while (i < MAX)
    {
        scanf("%d", &L[i]);
        i++;
        length++;
        if ((c = getchar()) == '\n')
            break;
    }
    i = 0;
    while (i < length)
    {
        scanf("%d", &R[i]);
        i++;
        if ((c = getchar()) == '\n')
            break;
    }
    for (i = 0; i < length; i++)
    {
        temp = L[i];
        L[i] = R[i];
        R[i] = temp;
    }
    for (i = 0; i < length - 1; i++)
    {
        printf("%d ", L[i]);
    }
    printf("%d\n", L[i]);
    for (i = 0; i < length - 1; i++)
    {
        printf("%d ", R[i]);
    }
    printf("%d\n",R[i]);
    return 0;
}