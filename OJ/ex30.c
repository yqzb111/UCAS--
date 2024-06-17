#include <stdio.h>

#define MAX_ROWS 100
#define MAX_COLS 100

void findSaddlePoints(int matrix[][MAX_COLS], int rows, int cols) {
    int i, j, k;
    int min_row[MAX_ROWS], max_col[MAX_COLS];
    for (i = 0; i < rows; i++) {
        min_row[i] = matrix[i][0];
        for (j = 1; j < cols; j++) {
            if (matrix[i][j] < min_row[i]) {
                min_row[i] = matrix[i][j];
            }
        }
    }
    for (j = 0; j < cols; j++) {
        max_col[j] = matrix[0][j];
        for (i = 1; i < rows; i++) {
            if (matrix[i][j] > max_col[j]) {
                max_col[j] = matrix[i][j];
            }
        }
    }
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (matrix[i][j] == min_row[i] && matrix[i][j] == max_col[j]) {
                printf("%d ", matrix[i][j]);
            }
        }
    }
}

int main() {
    int matrix[MAX_ROWS][MAX_COLS];
    int rows, cols;
    int i, j;
    scanf("%d %d", &rows, &cols);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    findSaddlePoints(matrix, rows, cols);
    return 0;
}