#include <omp.h>
#include <stdio.h>
#define m 4
#define n 2

int max_row(int arr[][n], int row) {
  int min = -1000;
  for (int i = 0; i < n; i++) {
    if (min < arr[i][row]) {
      min = arr[i][row];

      printf("%i", min);
    }
  }
  return min;
}
int main() {
  int arr[m][n] = {{1, 2}, {3, 4}, {3, 9}, {8, 7}};
  int max[m];
  int max_element;

#pragma omp parallel for num_threads(n)
  for (int i = 0; i < m; i++) {
    max[i] = max_row(arr, i);
  }
#pragma single for
  for (int i = 0; i < m; i++) {
    max_element = -100;
    if (max_element < max[i]) {
      max_element = max[i];
    }
  }

  printf("Maximum element %d\n", max_element);
  return 0;
}