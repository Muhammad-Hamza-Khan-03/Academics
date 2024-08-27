// linear search parallel
#include <omp.h>
#include <stdio.h>
#define n 10

int main() {
  int arr[n] = {1, 2, 1, 5, 3, 1, 2, 1, 4, 5};
  int key = 1;

  int num_procs = omp_get_num_procs();

  omp_set_num_threads(num_procs);
  int i, count = 0;

#pragma omp parallel for reduction(+ : count) shared(key)
  for (i = 0; i < n; i++) {
    if (key == arr[i]) {
      printf("Thread id: %i found key at index %d\n", omp_get_thread_num(), i);
      count++;
    }
  }

  printf("Key found %d times\n", count);
  return 0;
}