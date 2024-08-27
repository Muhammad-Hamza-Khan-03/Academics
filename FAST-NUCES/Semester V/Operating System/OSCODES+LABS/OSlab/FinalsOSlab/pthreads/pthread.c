#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
void *myturn(void *arg) {
  //   int *iptr = (int*)arg;
  int *iptr = (int *)malloc(sizeof(int));
  *iptr = 5;
  return iptr;
}
int main() {
  pthread_t new_thread;
  int *result;
  pthread_create(&new_thread, NULL, myturn, NULL);

  pthread_join(new_thread, (void *)&result);
  printf("%d", *result);
  return 0;
}