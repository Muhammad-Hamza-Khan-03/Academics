#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main() {

  float sum = 0;
  int count = 0;

  int shmid = shmget(1234, 1024, 0666);

  void *shmaddr = shmat(shmid, NULL, 0);

  char data[1024];

  strcpy(data, (char *)shmaddr);

  for (int i = 0; data[i] != '\0'; i++) {
    if (data[i] >= '0' && data[i] <= '9') {
      sum += data[i] - '0';
      count++;
    }
  }

  float average;
  average = sum / count;

  printf("Sum = %f\n", sum);
  printf("Average = %.2f\n", average);

  shmdt(shmaddr);

  return 0;
}
