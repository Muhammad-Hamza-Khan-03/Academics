#include <omp.h>
#include <stdio.h>

#define m 4
#define n 4

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
int main() {
  int arr[m][n] = {
      {3, 5, 32, 80}, {23, 11, 9, 15}, {20, 7, 14, 26}, {4, 17, 2, 7}};

  printf("Original Array:\n");
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", arr[i][j]);
    }
    printf("\n");
  }
  int matrix_sum = 0;
// Sorting each column
#pragma omp parallel for shared(matrix_sum)
  for (int i = 0; i < n; i++) {
    int column[m];
    for (int j = 0; j < m; j++) {
      column[j] = arr[j][i];
    }
    quickSort(column, 0, m - 1);
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