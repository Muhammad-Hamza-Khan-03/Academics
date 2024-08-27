#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

// summation
void *summation(void *arg) {

  int args = *(int *)arg;
  int *sum = malloc(sizeof(int));
  *sum = 0;
  for (int i = 0; i <= args; i++) {
    *sum += i;
  }
  pthread_exit(sum);
}
int main() {

  int N = 5;
  pthread_t tid;
  pthread_create(&tid, NULL, summation, &N);
  void *res;
  pthread_join(tid, &res);
  int *sum = (int *)res;

  printf("%d", *sum);
  free(sum);
  return 0;
}