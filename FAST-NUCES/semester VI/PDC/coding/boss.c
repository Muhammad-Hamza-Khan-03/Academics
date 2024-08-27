#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 2
#define COLS 2

void merge(int arr[], int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  int L[n1], R[n2];

  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];

  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(int arr[], int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    merge(arr, l, m, r);
  }
}

int main(int argc, char **argv) {
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int matrix[ROWS][COLS];
  int sorted_matrix[ROWS][COLS]; // 2D array to store sorted rows

  // Process 0 initializes the matrix
  if (rank == 0) {
    printf("Enter matrix elements (%d x %d):\n", ROWS, COLS);
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        scanf("%d", &matrix[i][j]);
      }
    }
  }

  // Broadcast matrix from process 0 to all processes
  MPI_Bcast(matrix, ROWS * COLS, MPI_INT, 0, MPI_COMM_WORLD);

  // Each process sorts its assigned row using merge sort and calculates row
  // product
  long long int row_product = 1;
  for (int i = 0; i < ROWS; i++) {
    if (i % size == rank) {
      mergeSort(matrix[i], 0, COLS - 1); // Sort the row
      for (int j = 0; j < COLS; j++) {
        sorted_matrix[i][j] =
            matrix[i][j]; // Copy the sorted row to sorted_matrix array
        row_product *= matrix[i][j]; // Calculate row product
      }
    }
  }

  // Gather sorted rows from all processes to process 0
  MPI_Gather(sorted_matrix[rank], COLS, MPI_INT, matrix, COLS, MPI_INT, 0,
             MPI_COMM_WORLD);

  // Reduce row products to find product of the complete matrix at process 0
  long long int matrix_product;
  MPI_Reduce(&row_product, &matrix_product, 1, MPI_LONG_LONG, MPI_PROD, 0,
             MPI_COMM_WORLD);

  // Process 0 prints the sorted matrix and product of the complete matrix
  if (rank == 0) {
    printf("Sorted matrix:\n");
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        printf("%d ", matrix[i][j]);
      }
      printf("\n");
    }
    printf("Product of the complete matrix: %lld\n", matrix_product);
  }

  MPI_Finalize();
  return 0;
}