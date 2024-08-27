#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_SIZE 20

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
    exit(1);
  }

  FILE *source_file = fopen(argv[1], "r");
  if (source_file == NULL) {
    perror("Error opening source file");
    exit(1);
  }

  key_t key = ftok("producer_consumer", 'R');
  if (key == -1) {
    perror("ftok");
    exit(1);
  }

  int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
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

  int read_count;
  char buffer[SHM_SIZE];

  while ((read_count = fread(buffer, 1, SHM_SIZE, source_file)) > 0) {
    sem_wait(producer_sem);
    memcpy(shared_memory, buffer, SHM_SIZE);
    sem_post(consumer_sem);

    sem_wait(consumer_sem);
    write(1, shared_memory, SHM_SIZE);
    sem_post(producer_sem);
  }

  // Indicate end-of-file to the consumer
  sem_wait(producer_sem);
  shared_memory[0] = '$';
  sem_post(consumer_sem);

  sem_close(producer_sem);
  sem_close(consumer_sem);

  shmdt(shared_memory);
  fclose(source_file);

  return 0;
}