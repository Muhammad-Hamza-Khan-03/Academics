#include <omp.h>
#include <stdio.h>

// int main() {
//   int procs = omp_get_num_procs();
//   int i = 0;
//   int x = 0;
//   int a = 9;

// #pragma omp parallel num_threads(300)
// #pragma omp atomic
//   i = i + 1;

//   x = x + 1;
//   a = a + 1;

//   printf("i = %d\n", i);
//   printf("a = %d\n", a);
//   printf("x = %d\n", x);
//   return 1;
// }
int main() {
  int k;
  omp_set_num_threads(8);
  int c = 10;
  int i;
  printf("total threads are : % d \n", omp_get_num_threads());
#pragma omp parallel
  {
#pragma omp master
    printf("total threads are : % d \n", omp_get_num_threads());
#pragma omp for schedule(static) firstprivate(c) lastprivate(c)
    for (i = 1; i <= 16; i++) {
      c = c + i;

      printf("The value of counter is : % d thread : %d\n", c,
             omp_get_thread_num());
    }
  }
}