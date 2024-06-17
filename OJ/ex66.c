#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void sortColors(int arr[], int n) {
    int low = 0;
    int high = n - 1;
    int mid = 0;

    while (mid <= high) {
        switch (arr[mid]) {
            case 1:
                swap(&arr[low++], &arr[mid++]);
                break;
            case 2:
                mid++;
                break;
            case 3:
                swap(&arr[mid], &arr[high--]);
                break;
        }
    }
}

void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n-1; i++) {
        printf("%d ", arr[i]);
    }
    printf("%d\n",arr[i]);
}

int main() {
    int arr[MAX];
    char line[400];
    fgets(line, sizeof(line), stdin);
    char *token = strtok(line, " ");
    int i = 0;
    while (token != NULL) {
        arr[i++] = atoi(token);
        token = strtok(NULL, " ");
    }
    int n = i;
    sortColors(arr, n);
    printArray(arr, n);
    return 0;
}
