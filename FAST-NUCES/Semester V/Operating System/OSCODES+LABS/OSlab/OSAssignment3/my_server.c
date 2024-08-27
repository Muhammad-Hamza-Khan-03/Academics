#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>


#define SHARED_MEMORY_SIZE 1024
#define MAX_THREADS 10

sem_t *mutex;
sem_t *readerSemaphore;
sem_t *writerSemaphore;

char *sharedMemory;

void *readSharedMemory(void *arg) {
  // Read the command from the shared memory
  char *command = sharedMemory;
  char file_name[1024];
  int read_write_info;

  sscanf(command, "%s %d", file_name, &read_write_info);

  if (read_write_info == 0) {
    // Perform read operation
    FILE *file = fopen(file_name, "r");
    if (file) {
      char data[SHARED_MEMORY_SIZE];
      fgets(data, SHARED_MEMORY_SIZE, file);
      printf("Data read from file: %s\n", data);
      fclose(file);
    } else {
      printf("Error: File not found\n");
    }
    sem_post(writerSemaphore);
  } else if (read_write_info == 1) {
    // Perform write operation
    FILE *file = fopen(file_name, "w");
    if (file) {
      fputs(sharedMemory, file);
      printf("Data written to file: %s\n", sharedMemory);
      fclose(file);
    } else {
      printf("Error: Could not write to file\n");
    }
    sem_post(readerSemaphore);
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s <file_name> <read_write_info>\n", argv[0]);
    return 1;
  }

  char *file_name = argv[1];
  int read_write_info = atoi(argv[2]);

  mutex = sem_open("mutex", O_CREAT, 0644, 1);
  readerSemaphore = sem_open("readerSemaphore", O_CREAT, 0644, 0);
  writerSemaphore = sem_open("writerSemaphore", O_CREAT, 0644, 0);

  // get file name and read/write info from command line
  char command[1024];
  fgets(command, sizeof(command), stdin);
  sscanf(command, "%s %d", file_name, &read_write_info);

  // shared memory
  key_t key = ftok("my_server.c", 'R');
  int shmid = shmget(key, SHARED_MEMORY_SIZE, 0644);
  sharedMemory = shmat(shmid, (void *)0, 0);

  // threads
  pthread_t threads[MAX_THREADS];
  for (int i = 0; i < MAX_THREADS; ++i) {
    pthread_create(&threads[i], NULL, readSharedMemory, NULL);
  }

  for (int i = 0; i < MAX_THREADS; ++i) {
    pthread_join(threads[i], NULL);
  }

  sem_close(mutex);
  sem_close(readerSemaphore);
  sem_close(writerSemaphore);

  shmdt(sharedMemory);
  shmctl(shmid, IPC_RMID, NULL);

  // Display what has been written and read from the server
  printf("Read/Write information: %s %d\n", file_name, read_write_info);

  return 0;
}