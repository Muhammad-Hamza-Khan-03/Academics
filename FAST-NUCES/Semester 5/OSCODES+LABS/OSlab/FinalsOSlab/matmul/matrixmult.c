#include <pthread.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>

int matrix1[3][3] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
int matrix2[3][3] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
int res[3][3];

struct thread_args {
  int row;
  int executionTime;
};

void *multiply(void *arg) {
  struct timeval startTime, endTime;
  gettimeofday(&startTime, NULL);

  struct thread_args *t = (struct thread_args *)arg;
  int i = t->row;
  printf("%d\n", i);

  for (int j = 0; j < 3; j++) {
    res[i][j] = matrix1[i][j] * matrix2[i][j];
  }

  gettimeofday(&endTime, NULL);
  t->executionTime = (endTime.tv_sec - startTime.tv_sec) * 1000000 +
                     (endTime.tv_usec - startTime.tv_usec);

  pthread_exit(NULL);
}

int main() {
  int shmid = shmget(11, sizeof(int) * 3, IPC_CREAT | 0666);
  int *shm = (int *)shmat(shmid, NULL, 0);

  pthread_t threads[3];
  struct thread_args t[3];

  for (int i = 0; i < 3; i++) {
    t[i].row = i;
    pthread_create(&threads[i], NULL, multiply, &t[i]);
  }

  for (int j = 0; j < 3; j++) {
    pthread_join(threads[j], NULL);
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%d ", res[i][j]);
    }
    printf("\n");
  }

  long long sum = 0;
  for (int i = 0; i < 3; i++) {
    sum += t[i].executionTime;
  }
  printf("Total Execution Time: %lld microseconds\n", sum);

  shmdt(shm);
  shmctl(shmid, IPC_RMID, NULL); // Remove shared memory segment
  return 0;
}
