#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define m1 100
#define n1 100
void init(int matrix1[][n1], int matrix2[][n1]) {
  for (int i = 0; i < m1; i++) {
    for (int j = 0; j < n1; j++) {
      matrix1[i][j] = rand() % 3 + 1;
      matrix2[i][j] = rand() % 3 + 1;
    }
  }
}
void default_para_mult(int matrix1[][n1], int matrix2[][n1], int result[][n1]) {
  int row, col, k;
#pragma parallel for collapse(2)
  for (row = 0; row < m1; row++) {
    for (col = 0; col < n1; col++) {
      result[row][col] = 0;
      for (k = 0; k < n1; k++) {
        result[row][col] += matrix1[row][k] * matrix2[k][col];
      }
    }
  }
}

void default_static(int matrix1[][n1], int matrix2[][n1], int result[][n1]) {
  int k, row, col;
#pragma omp parallel for shared(matrix1, matrix2, result) private(row, col, k) \
    schedule(static)
  for (row = 0; row < m1; row++) {
    for (col = 0; col < n1; col++) {
      result[row][col] = 0;
      for (k = 0; k < n1; k++) {
        result[row][col] += matrix1[row][k] * matrix2[k][col];
      }
    }
  }
}

void default_dynamic(int matrix1[][n1], int matrix2[][n1], int result[][n1]) {
  int k, row, col;
#pragma omp parallel for shared(matrix1, matrix2, result) private(row, col, k) \
    schedule(dynamic)
  for (row = 0; row < m1; row++) {
    for (col = 0; col < n1; col++) {
      result[row][col] = 0;
      for (k = 0; k < n1; k++) {
        result[row][col] += matrix1[row][k] * matrix2[k][col];
      }
    }
  }
}
void fine_param(int row, int col, int k, int matrix1[][n1], int matrix2[][n1],
                int result[][n1]) {
#pragma omp parallel for shared(matrix1, matrix2, result) private(row, col, k) \
    collapse(2)
  for (row = 0; row < m1; row++) {
    for (col = 0; col < n1; col++) {
      result[row][col] = 0;
      for (k = 0; k < n1; k++) {
        result[row][col] += matrix1[row][k] * matrix2[k][col];
      }
    }
  }
}
int main() {
  double start_time, end_time;
  int matrix1[m1][n1];
  int matrix2[m1][n1];
  int result[m1][n1];

  init(matrix1, matrix2); /// initialize both matrices

  // calculating execution time with default Parameters
  start_time = omp_get_wtime();
  default_para_mult(matrix1, matrix2,
                    result); // default parameters multiplication
  end_time = omp_get_wtime();
  printf("Execution time with default parameters is: %f\n",
         end_time - start_time);

  // Calculating execution time with static and dynamic schedule with default
  start_time = omp_get_wtime();
  default_static(matrix1, matrix2, result);
  end_time = omp_get_wtime();
  printf("Static Scheduling time : %f\n", end_time - start_time);

  // dynamic:
  start_time = omp_get_wtime();
  default_dynamic(matrix1, matrix2, result);
  end_time = omp_get_wtime();

  printf("Dynamic Scheduling time : %f\n", end_time - start_time);

  // Part 2
  omp_set_num_threads(m1 * n1); // set threads num to element
  int k, row, col;
  start_time = omp_get_wtime();
  fine_param(row, col, k, matrix1, matrix2, result);
  end_time = omp_get_wtime();

  printf("\nFine grain default execution time: %f\n", end_time - start_time);
  start_time = omp_get_wtime();
#pragma omp parallel for shared(matrix1, matrix2, result) private(row, col, k) \
    collapse(2) schedule(static)
  for (row = 0; row < m1; row++) {
    for (col = 0; col < n1; col++) {
      result[row][col] = 0;
      for (k = 0; k < n1; k++) {
        result[row][col] += matrix1[row][k] * matrix2[k][col];
      }
    }
  }
  end_time = omp_get_wtime();
  printf("FINE GRAIN -> Static Scheduling time : %f\n", end_time - start_time);
  start_time = omp_get_wtime();

#pragma omp parallel for shared(matrix1, matrix2, result) private(row, col, k) \
    collapse(2) schedule(dynamic)
  for (row = 0; row < m1; row++) {
    for (col = 0; col < n1; col++) {
      result[row][col] = 0;
      for (k = 0; k < n1; k++) {
        result[row][col] += matrix1[row][k] * matrix2[k][col];
      }
    }
  }
  end_time = omp_get_wtime();

  printf("FINE GRAIN-> Dynamic Scheduling time : %f\n", end_time - start_time);

  return 0;
}