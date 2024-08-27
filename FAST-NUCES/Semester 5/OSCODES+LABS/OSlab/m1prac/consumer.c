#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_SIZE 20

int main() {
  key_t key = ftok("producer_consumer", 'R');
  if (key == -1) {
    perror("ftok");
    exit(1);
  }

  int shmid = shmget(key, SHM_SIZE, 0666);
  if (shmid == -1) {
    perror("shmget");
    exit(1);
  }

  char *shared_memory = (char *)shmat(shmid, NULL, 0);
  if (shared_memory == (char *)(-1)) {
    perror("shmat");
    exit(1);
  }

  sem_t *producer_sem = sem_open("/producer_sem", 0666, 1);
  sem_t *consumer_sem = sem_open("/consumer_sem", 0666, 0);

  while (1) {
    sem_wait(consumer_sem);
    if (shared_memory[0] == '$') {
      break;
    }
    write(1, shared_memory, SHM_SIZE);
    sem_post(producer_sem);
  }

  sem_close(producer_sem);
  sem_close(consumer_sem);

  shmdt(shared_memory);

  return 0;
}