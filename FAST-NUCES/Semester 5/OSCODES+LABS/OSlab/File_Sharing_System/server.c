#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#define MAX_SIZE 10

struct cmd {
  char *command;
  char *filename;
  char *data;
  char *buffer;
};
void tokenization(char *input, char tokens[][20]) {
  int i = 0;
  char *token = strtok(input, " \t\n");
  while (token != NULL) {
    strcpy(tokens[i], token);
    token = strtok(NULL, " \t\n");
    i++;
  }
}
void *writecommand(void *arg) {
  struct cmd *command = (struct cmd *)arg;
  int fd;

  fd = open(command->filename, O_WRONLY);
  write(fd, command->data, strlen(command->data));
  close(fd);
  return NULL;
}
void *readcommand(void *arg) {
  struct cmd *command = (struct cmd *)arg;
  command->filename = "file.txt";
  int fd;
  fd = open(command->filename, O_RDONLY);
  printf("%s ", command->filename);
  char *buffer = (char *)calloc(100, sizeof(char));
  size_t bytesread = read(fd, buffer, 100);
  buffer[bytesread] = '\0';
  // strcpy(command->buffer, buffer);
  printf("buffer %s\n", buffer);
  return NULL;
}
int main() {
  int shmid = shmget(11, sizeof(char *), 0666 | IPC_CREAT);
  int sem_serv = shmget(12, sizeof(sem_t), 0666 | IPC_CREAT);
  int sem_client = shmget(13, sizeof(sem_t), 0666 | IPC_CREAT);

  char *old_shared_memory = (char *)shmat(shmid, NULL, 0);
  sem_t *sem_srv = (sem_t *)shmat(sem_serv, NULL, 0);
  sem_t *sem_cli = (sem_t *)shmat(sem_client, NULL, 0);
  char *tokenized;

  while (1) {
    sem_wait(sem_srv);
    char tok[10][20]; // Define a 2D character array to store the tokens
    struct cmd cd;
    tokenization(old_shared_memory, tok);
    printf("%s", tok[1]);
    cd.command = tok[0];
    cd.filename = tok[1];
    if (strcmp(tok[0], "write") == 0) {
      cd.data = tok[2];
      pthread_t pid;
      pthread_create(&pid, NULL, writecommand, (void *)&cd);
      pthread_join(pid, NULL);
    }
    // for read
    else {
      cd.data = NULL;
      printf("READING PROGRESS 1\n");
      int new_shmid = shmget(10, sizeof(char *), 0666 | IPC_CREAT);
      char *new_shared_memory = (char *)shmat(new_shmid, NULL, 0);
      printf("READING PROGRESS 2\n");
      pthread_t pid;
      pthread_create(&pid, NULL, readcommand, (void *)&cd);
      pthread_join(pid, NULL);
      sprintf(old_shared_memory, "%d", 10);
      strcpy(new_shared_memory, cd.buffer);
      printf("new shared memory:%s", new_shared_memory);
      sem_post(sem_cli);
    }
    // sem_post(sem_cli);
  }

  shmdt(sem_srv);
  shmdt(sem_cli);
  return 0;
}