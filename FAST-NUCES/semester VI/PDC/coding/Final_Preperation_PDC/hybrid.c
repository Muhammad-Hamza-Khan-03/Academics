#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

int main(int argc, char **argv) {
  int provided;
  MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
  if (provided < MPI_THREAD_MULTIPLE) {
    fprintf(stderr, "MPI does not support MPI_THREAD_MULTIPLE\n");
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int sendbuf[NUM_THREADS] = {2, 4, 6, 8};
  int recvbuf[NUM_THREADS] = {0, 0, 0, 0};

  omp_set_num_threads(NUM_THREADS);

#pragma omp parallel
  {
    int thread_id = omp_get_thread_num();

    if (rank == 0) {
      for (int i = 1; i < size; i++) {
        printf("process_id:%d-->thread#%d is sending %d to process %d\n", rank,
               thread_id, sendbuf[thread_id], i);
        MPI_Send(&sendbuf[thread_id], 1, MPI_INT, i, thread_id, MPI_COMM_WORLD);
      }
    } else {
      MPI_Recv(&recvbuf[thread_id], 1, MPI_INT, 0, thread_id, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      printf("process-id:%d Received %d from thread#%d of source\n", rank,
             recvbuf[thread_id], thread_id);
    }
  }

  if (rank != 0) {
    printf("recvbuff=");
    for (int i = 0; i < NUM_THREADS; i++) {
      printf("%d ", recvbuf[i]);
    }
    printf("\n");
  }

  MPI_Finalize();
  return 0;
}
