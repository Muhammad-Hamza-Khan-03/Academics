#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

sem_t semaphores[3];
int global = 0;
int a = 0;
void *printA(void *arg) {
  while (1) {

    sem_wait(&semaphores[0]);
    printf("a");
    global += 1;
    a += 1;
    if (global >= 5) {
      sem_post(&semaphores[2]);
    } else if (a % 2 != 0) {
      sem_post(&semaphores[1]);
    } else {
      sem_post(&semaphores[0]);
    }
  }

  return NULL;
}

void *printB(void *arg) {
  while (1) {
    sem_wait(&semaphores[1]);
    printf("b");
    global += 1;
    sem_post(&semaphores[0]);
  }

  return NULL;
}

void *printC(void *arg) {
  while (1) {
    sem_wait(&semaphores[2]);
    printf("c");
    global = 0;
    sem_post(&semaphores[0]);
  }

  return NULL;
}

int main() {
  const int a = 1;
  const int totalThreads = 3;

  pthread_t threads[totalThreads];

  // Initialize semaphores
  for (int i = 0; i < totalThreads; ++i) {
    sem_init(&semaphores[i], 0, i == 0 ? 1 : 0);
  }

  // Create threads for each letter
  pthread_create(&threads[0], NULL, printA, NULL);
  pthread_create(&threads[1], NULL, printB, NULL);
  pthread_create(&threads[2], NULL, printC, NULL);

  // Wait for threads to finish (this won't happen)
  for (int i = 0; i < totalThreads; ++i) {
    pthread_join(threads[i], NULL);
  }

  // Destroy semaphores
  for (int i = 0; i < totalThreads; ++i) {
    sem_destroy(&semaphores[i]);
  }

  return 0;
}
