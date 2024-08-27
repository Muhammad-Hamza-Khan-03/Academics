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

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("enter file name input.txt\n");
    return 1;
  }

  int fd = open(argv[1], O_RDONLY);

  if (fd < 0) {
    printf("File Error");
    return 1;
  }
  printf("%s file opened successfully\n", argv[1]);

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

  // Initialize sempahores producer and consumer
  sem_init(semaphore_producer, 1, 1);
  sem_init(semaphore_consumer, 1, 0);

  char buffer[size];
  ssize_t read_count = 20;

  int i = 0;
  while (1) {

    sem_wait(semaphore_producer);

    if (i > read_count) { // case when read count is reached
      shared_buffer[0] = '$';
      sem_post(semaphore_consumer);
      break;
    }

    read(fd, shared_buffer, size);
    sem_post(semaphore_consumer);

    i += 20; // bcz i is always multiple of 20
  }

  // we detach the memory
  shmdt(shared_buffer);
  shmdt(semaphore_consumer);
  shmdt(semaphore_producer);

  // now we destroy
  shmctl(shared_mem_id, IPC_RMID, NULL);
  shmctl(shared_producer, IPC_RMID, NULL);
  shmctl(shared_consumer, IPC_RMID, NULL);
  return 0;
}