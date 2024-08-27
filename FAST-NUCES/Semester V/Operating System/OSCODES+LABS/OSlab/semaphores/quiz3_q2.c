#include <stdio.h>
#include <string.h>

int main() {
  int matrix1[4][4] = {{3, 2, 1, 5}, {1, 2, 3, 1}, {0, 1, 2, 3}, {4, 6, 7, 8}};
  int matrix2[4][4] = {{1, 5, 6, 4}, {2, 3, 1, 2}, {0, 0, 1, 0}, {0, 0, 2, 0}};
  int sum[1][8];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%d", matrix1[i][j]);
    }
    printf("\n");
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%d", matrix2[i][j]);
    }
    printf("\n");
  }
  int k = 0;
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
      sum[0][k] = matrix1[i][j] + matrix2[i][j];
      k++;
    }
  }
  printf("SUM:\n");
  for (int i = 0; i < 1; i++) {
    for (int j = 0; j < 8; j++) {
      printf("%d ", sum[i][j]);
    }
  }
  printf("\n");
  return 0;
}