#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define size 20

int main() {

  // opening file
  int fd = open("input.txt", O_RDONLY);

  // shared memory
  int shared_mem_id = shmget(560, size, IPC_CREAT | 0666);
  int shared_producer = shmget(111, sizeof(sem_t), IPC_CREAT | 0666);
  int shared_consumer = shmget(222, sizeof(sem_t), IPC_CREAT | 0666);

  if (shared_mem_id < 0 || shared_producer < 0 || shared_consumer < 0) {
    perror("shmget");
    exit(1);
  }

  // shared memory attach
  char *shared_buffer = (char *)shmat(shared_mem_id, NULL, 0);
  sem_t *semaphore_producer = (sem_t *)shmat(shared_producer, NULL, 0);
  sem_t *semaphore_consumer = (sem_t *)shmat(shared_consumer, NULL, 0);

  int i = 0; // for file iteration
             // for number of times the process executes its critical section
  while (1) {
    sem_wait(semaphore_consumer);

    if (shared_buffer[0] == '$') { // case when file end is detected
      sem_post(semaphore_producer);
      break;
    }
    printf(" %s\n", shared_buffer);
    sem_post(semaphore_producer);
    i += 20;
  }

  // detach the shared memory
  shmdt(shared_buffer);
  shmdt(semaphore_producer);
  shmdt(semaphore_consumer);
  return 0;
}