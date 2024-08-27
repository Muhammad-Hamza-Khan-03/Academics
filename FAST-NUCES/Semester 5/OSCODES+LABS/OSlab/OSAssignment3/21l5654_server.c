#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define MAX_SIZE 100

struct CommandData {
  char command[MAX_SIZE];
  char filename[MAX_SIZE];
  char data[MAX_SIZE];
};
void *readCommand(void *arg) {
  struct CommandData *cmdData = (struct CommandData *)arg;
  char *filename = cmdData->filename;
  int file = open(filename, O_RDONLY);
  if (file < 0) {
    perror("File open error");
    exit(1);
  }

  char file_content[MAX_SIZE];
  ssize_t bytes_read = read(file, file_content, sizeof(file_content));
  if (bytes_read < 0) {
    perror("File read error");
    exit(1);
  }
  printf("file content is:%s", file_content);
  close(file);

  int new_shared_mem_id = shmget(300, sizeof(char *), 0666);
  if (new_shared_mem_id < 0) {
    perror("shmget error");
    exit(1);
  }

  char *new_shared_buffer = (char *)shmat(new_shared_mem_id, NULL, 0);

  strcpy(new_shared_buffer, file_content);

  // Detach from the new shared memory
  shmdt(new_shared_buffer);

  return NULL;
}
void *writeCommand(void *arg) {
  struct CommandData *cmdData = (struct CommandData *)arg;
  char *filename = cmdData->filename;
  char *data = cmdData->data;
  // Open the file for writing
  int file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if (file == -1) {
    perror("File open error");
    exit(1);
  }

  ssize_t bytes_written = write(file, data, strlen(data));
  if (bytes_written == -1) {
    perror("Write error");
    exit(1);
  }

  close(file);

  return NULL;
}
int main() {

  // shared memory bna rha
  int size = 100;
  int shared_mem_id = shmget(310, sizeof(char *), IPC_CREAT | 0666);
  if (shared_mem_id < 0) {
    perror("shmget error");
    return 1;
  }
  struct CommandData cmdData;

  char *shared_buffer = (char *)shmat(shared_mem_id, NULL, 0);

  int shared_client = shmget(110, sizeof(sem_t), IPC_CREAT | 0666);
  int shared_server = shmget(220, sizeof(sem_t), IPC_CREAT | 0666);

  sem_t *semaphore_client = (sem_t *)shmat(shared_client, NULL, 0);
  sem_t *semaphore_server = (sem_t *)shmat(shared_server, NULL, 0);
  char command[MAX_SIZE], filename[MAX_SIZE], data[MAX_SIZE];

  while (1) {
    sem_wait(semaphore_server);

    sscanf(shared_buffer, "%s %s %s", cmdData.command, cmdData.filename,
           cmdData.data);
    pthread_t tid;
    if (strcmp(cmdData.command, "read") == 0) {
      int new_shared_mem_id = shmget(300, sizeof(char *), IPC_CREAT | 0666);
      if (new_shared_mem_id < 0) {
        perror("shmget error");
        return 1;
      }

      sprintf(shared_buffer, "%d", 300);

      pthread_create(&tid, NULL, readCommand, (void *)&cmdData);
      pthread_join(tid, NULL);
    }

    // if case is write

    else if (strcmp(cmdData.command, "write") == 0) {

      pthread_create(&tid, NULL, writeCommand, (void *)&cmdData);
      pthread_join(tid, NULL);
    }

    sem_post(semaphore_client);
  }

  // Detach shared memory
  shmdt(shared_buffer);

  return 0;
}