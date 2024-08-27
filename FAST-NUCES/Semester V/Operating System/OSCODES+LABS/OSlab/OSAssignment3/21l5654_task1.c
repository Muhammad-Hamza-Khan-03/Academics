#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define maxsize 5

int top = -1;
sem_t semaphore[2];
int arr[maxsize];
int itemCount = 0;

void *push(void *val) {
  int value = *((int *)val);
  while (1) {
    sem_wait(&semaphore[0]);
    value = rand() % 100;
    top = (top + 1) % maxsize;
    arr[top] = value;
    itemCount++;

    printf("Pushed element %d\n", value);

    if (itemCount == maxsize) {
      printf("STACK FULL\n");
      sem_post(&semaphore[1]);
      sem_wait(&semaphore[0]);
    }

    sem_post(&semaphore[0]);
    sleep(1);
  }
  return NULL;
}

void *pop() {
  while (1) {
    sem_wait(&semaphore[1]);

    int top_element = arr[top];
    top = (top - 1 + maxsize) % maxsize;
    printf("Popped element %d\n", top_element);
    itemCount--;

    if (itemCount == 0) {
      printf("STACK EMPTY\n");
      sem_post(&semaphore[0]);
      sem_wait(&semaphore[1]);
    }

    sem_post(&semaphore[1]);
    sleep(1);
  }
  return NULL;
}

int main() {
  sem_init(&semaphore[0], 0, 1);
  sem_init(&semaphore[1], 0, 0);

  pthread_t thread[2]; // thread[0]->prod, thread[1]->consumer
  int value = 38;

  // create pthreads
  pthread_create(&thread[0], NULL, push, (void *)&value);
  pthread_create(&thread[1], NULL, pop, NULL);

  // joining threads
  pthread_join(thread[0], NULL);
  pthread_join(thread[1], NULL);

  for (int i = 0; i < 2; i++) {
    sem_destroy(&semaphore[i]);
  }

  return 0;
}
