#include <omp.h>
#include <stdio.h>
#include <time.h>
#define size 100
#define key 111
int start_time, end_time;
int static_implementation() {
  double start_time = omp_get_wtime();
  int win, x, y, z;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < size; k++) {
        x = (i * i * 1000 / 35) % 1000;
        y = (j * j * 1000 / 36) % 1000;
        z = (k * k * 1000 / 37) % 1000;
        if (key == (x + y + z)) {
          win = win + 1;
        }
      }
    }
  }
  printf("total wins=%d\n", win);
  double end_time = omp_get_wtime();
  double seq_time = end_time - start_time;
  return seq_time;
}

int parallel(int num_threads) {

  start_time = omp_get_wtime();
  int i, j, k, x, y, z, win = 0;
#pragma omp parallel for private(i, j, k, x, y, z) reduction(+ : win)          \
    num_threads(num_threads)
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      for (k = 0; k < size; k++) {
        x = (i * i * 1000 / 35) % 1000;
        y = (j * j * 1000 / 36) % 1000;
        z = (k * k * 1000 / 37) % 1000;
        if (key == (x + y + z)) {
#pragma omp critical
          win = win + 1;
        }
      }
    }
  }
  printf("total wins=%d\n", win);
  end_time = omp_get_wtime();
  double parallel_execution_time = end_time - start_time;
  return parallel_execution_time;
}
int main() {

  double sequential_time = static_implementation();
  printf("Sequential Time taken in seconds : %f\n", sequential_time);

  int num_threads = 2;
  while (num_threads <= 4) {
    double parallel_execution_time = parallel(num_threads);
    printf("Parallel Time taken with num_threads: %d : %f seconds\n",
           num_threads, parallel_execution_time);
    num_threads += 1;
  }
  return 0;
}