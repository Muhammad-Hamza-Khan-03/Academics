#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int m1 = 3;
int n1 = 3;
// Data Parallelism and Task Paralellism
int main(int argc, char *argv[])
// correct for 2x2 matrix
{
  if (argc < 2) {
    printf("Input the size of matrix such as 3 3");
    perror("Error");
  }
  m1 = atoi(argv[1]);
  n1 = atoi(argv[2]);

  int matrix1[m1][n1];
  int matrix2[m1][n1];
  int result[m1][n1];

  for (int i = 0; i < m1; i++) {
    for (int j = 0; j < n1; j++) {
      matrix1[i][j] = rand() % 3 + 1;
      matrix2[i][j] = rand() % 3 + 1;
    }
  }

  for (int i = 0; i < m1; i++) {
    for (int j = 0; j < n1; j++) {
      printf("Matrix1 : [%d][%d] = %d \t", i, j, matrix1[i][j]);
      printf("Matrix2 : [%d][%d] = %d", i, j, matrix2[i][j]);
      printf("\n");
    }
  }
  omp_set_num_threads(omp_get_max_threads());
  int i, j, k;
  int row, col;
#pragma omp parallel for shared(matrix1, matrix2, result) private(row, col, k)
  for (row = 0; row < m1; row++) {
    for (col = 0; col < n1; col++) {
      result[row][col] = 0;
      for (k = 0; k < n1; k++) {
        result[row][col] += matrix1[row][k] * matrix2[k][col];
      }
    }
    printf("Thread Ids: %d\n", omp_get_thread_num());
  }
  printf("My resultant Matrix:\n");
  for (i = 0; i < m1; i++) {
    for (j = 0; j < n1; j++) {
      printf("%d ", result[i][j]);
    }
    printf("\n");
  }
  return 0;
}