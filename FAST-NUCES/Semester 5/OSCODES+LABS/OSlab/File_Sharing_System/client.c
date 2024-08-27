#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#define MAX_SIZE 1024
void tokenization(char *input, char tokens[][20]) {
  int i = 0;
  char *token = strtok(input, " \t\n");
  while (token != NULL) {
    strcpy(tokens[i], token);
    token = strtok(NULL, " \t\n");
    i++;
  }
}
int main(int argc, char *argv[]) {
  // only write command is checked here

  if (argc < 3) {
    printf("Usage <command> <filename> <data>\n");
    return 1;
  }
  char *command = argv[1], *filename = argv[2];
  char *data = NULL;
  if (strcmp(command, "write") == 0) {
    data = argv[3];
  } else if (strcmp(command, "read") != 0) {
    printf("\nERROR IN FORMAT\n");
  }
  printf("Before wala check %s %s %s\n", command, filename, data);

  int shmid = shmget(11, sizeof(char *), 0666 | IPC_CREAT);
  int sem_serv = shmget(12, sizeof(sem_t), 0666 | IPC_CREAT);
  int sem_client = shmget(13, sizeof(sem_t), 0666 | IPC_CREAT);

  char *old_shared_memory = (char *)shmat(shmid, NULL, 0);
  sem_t *sem_srv = (sem_t *)shmat(sem_serv, NULL, 0);
  sem_t *sem_cli = (sem_t *)shmat(sem_client, NULL, 0);

  bool flag = true;
  sem_init(sem_srv, 1, 0);
  sem_init(sem_cli, 1, 1);

  while (1) {
    sem_wait(sem_cli);
    // only for write case
    if (strcmp(command, "write") == 0) {
      //   flag = false;
      sprintf(old_shared_memory, "%s %s %s", command, filename, data);
      sem_post(sem_srv);
    }
    if (strcmp(command, "read") == 0) {

      sem_post(sem_srv);
      printf("WAITING\n");
      char tok[10][20]; // Define a 2D character array to store the tokens

      tokenization(old_shared_memory, tok);
      int new_shmid = 10;
      char *new_shared_memory = (char *)shmat(new_shmid, NULL, 0);

      sleep(5);
      sem_wait(sem_cli);
      printf("shmid%d, NEW READ STRING:\n-> %s", new_shmid, new_shared_memory);
    }
  }
  shmdt(old_shared_memory);

  shmdt(sem_srv);
  shmdt(sem_cli);
  return 0;
}