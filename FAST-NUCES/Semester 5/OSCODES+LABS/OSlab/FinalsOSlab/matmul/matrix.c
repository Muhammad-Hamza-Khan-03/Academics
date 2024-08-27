#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define MATRIX_SIZE 10
#define NUM_THREADS 4

int matrix1[MATRIX_SIZE][MATRIX_SIZE];
int matrix2[MATRIX_SIZE][MATRIX_SIZE];
int resultMatrix[MATRIX_SIZE][MATRIX_SIZE];

struct ThreadArgs {
  int startRow;
  int endRow;
  double *executionTime;
};

void initializeMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
  for (int i = 0; i < MATRIX_SIZE; ++i) {
    for (int j = 0; j < MATRIX_SIZE; ++j) {
      matrix[i][j] = rand() % 10; // Random values between 1 and 10
    }
  }
}

void *multiply(void *arg) {
  struct ThreadArgs *args = (struct ThreadArgs *)arg;

  struct timeval startTime, endTime;
  gettimeofday(&startTime, NULL);

  for (int i = args->startRow; i < args->endRow; ++i) {
    for (int j = 0; j < MATRIX_SIZE; ++j) {
      resultMatrix[i][j] = 0;
      for (int k = 0; k < MATRIX_SIZE; ++k) {
        resultMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }

  gettimeofday(&endTime, NULL);
  *args->executionTime = (endTime.tv_sec - startTime.tv_sec) * 1000000 +
                         (endTime.tv_usec - startTime.tv_usec);

  pthread_exit(NULL);
}

int main() {
  initializeMatrix(matrix1);
  initializeMatrix(matrix2);

  pthread_t threads[NUM_THREADS];
  struct ThreadArgs threadArgs[NUM_THREADS];
  double threadExecutionTimes[NUM_THREADS];

  int rowsPerThread = MATRIX_SIZE / NUM_THREADS;

  for (int i = 0; i < NUM_THREADS; ++i) {
    threadArgs[i].startRow = i * rowsPerThread;
    threadArgs[i].endRow = (i + 1) * rowsPerThread;
    threadArgs[i].executionTime = &threadExecutionTimes[i];

    pthread_create(&threads[i], NULL, multiply, (void *)&threadArgs[i]);
  }

  for (int i = 0; i < NUM_THREADS; ++i) {
    pthread_join(threads[i], NULL);
  }

  double totalExecutionTime = 0;
  for (int i = 0; i < NUM_THREADS; ++i) {
    totalExecutionTime += threadExecutionTimes[i];
  }

  // Display the resultant matrix and total execution time
  printf("Resultant Matrix:\n");
  for (int i = 0; i < MATRIX_SIZE; ++i) {
    for (int j = 0; j < MATRIX_SIZE; ++j) {
      printf("%d ", resultMatrix[i][j]);
    }
    printf("\n");
  }

  printf("Total Execution Time: %.2f microseconds\n", totalExecutionTime);

  return 0;
}
