#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
  int rank, size;
  int matrix[4][4] = {
      {1, 3, 5, 7}, {2, 4, 6, 8}, {11, 13, 15, 17}, {12, 14, 16, 18}};
  int transposed_matrix[4][4];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Scatter rows of the matrix to processes
  MPI_Scatter(matrix, 4, MPI_INT, &matrix[rank], 4, MPI_INT, 0, MPI_COMM_WORLD);

  // Transpose the local matrix
  for (int i = 0; i < 4; i++) {
    MPI_Allgather(&matrix[0][i], 1, MPI_INT, &transposed_matrix[i], 1, MPI_INT,
                  MPI_COMM_WORLD);
  }

  // Print the transposed matrix
  printf("Process %d: Transposed matrix\n", rank);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%d ", transposed_matrix[i][j]);
    }
    printf("\n");
  }

  MPI_Finalize();
  return 0;
}