#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#define size 100

int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf(
        "command improper format: write read filename data \n read filename");
    return 1;
  }
  char *command = argv[1];
  char *filename = argv[2];
  char *data = argv[3];

  // check format
  if (strcmp(argv[1], "write") != 0 && strcmp(argv[1], "read") != 0) {
    printf("Incorrect Format");
    return 1;
  }

  // shared memory
  int shared_mem_id = shmget(560, sizeof(char *), IPC_CREAT | 0666);
  if (shared_mem_id < 0) {
    printf("er");
    return 1;
  }
  char *shared_buffer = (char *)shmat(shared_mem_id, NULL, 0);

  int shared_client = shmget(111, sizeof(sem_t), IPC_CREAT | 0666);
  int shared_server = shmget(222, sizeof(sem_t), IPC_CREAT | 0666);

  sem_t *semaphore_client = (sem_t *)shmat(shared_client, NULL, 0);
  sem_t *semaphore_server = (sem_t *)shmat(shared_server, NULL, 0);

  sem_init(semaphore_client, 0, 1);
  sem_init(semaphore_server, 0, 0);

  while (1) {
    sem_wait(semaphore_client);
    sprintf(shared_buffer, "%s %s %s", command, filename, data);
    printf("Shared Buffer: %s\n", shared_buffer);

    // if command is read wait for response
    if (strcmp(command, "read") == 0) {
      sem_post(semaphore_server);
    } else {
      sem_post(semaphore_client);
    }
    sleep(2);
  }
  // Detach shared memory
  shmdt(shared_buffer);
  // Delete shared memory
  shmctl(shared_mem_id, IPC_RMID, NULL);

  // Delete semaphores
  sem_destroy(semaphore_client);
  sem_destroy(semaphore_server);
  shmctl(shared_client, IPC_RMID, NULL);
  shmctl(shared_server, IPC_RMID, NULL);
  return 0;
}