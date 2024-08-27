#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int count;
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  if (world_rank == 0) {
    int data[5] = {10, 20, 30, 40, 50};
    MPI_Send(data, 5, MPI_INT, 1, 0, MPI_COMM_WORLD);
    MPI_Send(&data[1], 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
  } else if (world_rank == 1) {
    MPI_Status status;
    int received_data[5];
    MPI_Recv(received_data, 5, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

    MPI_Get_count(&status, MPI_INT, &count);
  }

  printf("Received %d elements from source %d with tag %d\n", count);
  MPI_Finalize();
  return 0;
}
