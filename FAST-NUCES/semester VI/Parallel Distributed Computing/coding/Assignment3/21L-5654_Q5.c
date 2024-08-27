#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int partition(int array[], int low, int high) {
  int pivot = array[high];
  int i = (low - 1);

  for (int j = low; j < high; j++) {
    if (array[j] >= pivot) {
      i++;
      swap(&array[i], &array[j]);
    }
  }

  swap(&array[i + 1], &array[high]);
  return (i + 1);
}

void quickSort(int array[], int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);
    quickSort(array, low, pi - 1);
    quickSort(array, pi + 1, high);
  }
}

// ROLL Number: 5654
// Sorting columns in decreasing order
int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Input error: 3 3 1 2 3 4 5 6 7 8 9");
    return 1;
  }
  int m = atoi(argv[1]); // rows
  int n = atoi(argv[2]); // columns
  printf("rows = %d , columns = %d", m, n);
  int arr[m][n];
  int index = 2;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      arr[i][j] = atoi(argv[++index]);
    }
  }
  // int arr[m][n] = {
  //     {3, 5, 32, 80}, {23, 11, 9, 15}, {20, 7, 14, 26}, {4, 17, 2, 7}};

  printf("Original Array:\n");
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", arr[i][j]);
    }
    printf("\n");
  }
  int matrix_sum = 0;
  omp_set_num_threads(m);
// Sorting each column
#pragma omp parallel for reduction(+ : matrix_sum)
  for (int i = 0; i < n; i++) {
    int column[m];
    for (int j = 0; j < m; j++) {
      column[j] = arr[j][i];
    }
    quickSort(column, 0, m - 1);
    printf("Column %d sorted by thread %d\n", i, omp_get_thread_num());
    for (int j = 0; j < m; j++) {
      arr[j][i] = column[j];
      matrix_sum += arr[j][i];
    }
  }

  printf("Sorted Array by Columns:\n");
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", arr[i][j]);
    }
    printf("\n");
  }
  printf("The Matrix Sum is: %d\n", matrix_sum);

  return 0;
}