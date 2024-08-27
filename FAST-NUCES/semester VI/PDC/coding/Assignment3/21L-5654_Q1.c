#include <fcntl.h>
#include <math.h>
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// gcc -fopenmp Q1.c -o Q1 -lm

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Enter P and N and filename\n");
    return 1;
  }
  int n = atoi(argv[2]), p = atoi(argv[1]);
  bool isprime = false; // check prime numbers
  int number = sqrt(n); // getting square root

  char stringArr[n]; // storing data to pass to file
  bool arr[n];       // bool array for storing prime numbers

  arr[0] = false, arr[1] = false;
  arr[2] = true;

  char *filepath = argv[3];

  int fd = open(filepath, O_CREAT | O_WRONLY, 0666); // open file fd

  if (fd < 0) {
    perror("File not opening");
    return 1;
  }
  omp_set_num_threads(p); // set threads num p
#pragma omp parallel for  // running code parallely
  for (int counter = 3; counter <= n; counter++) {
    bool isPrime = true;
    for (int lower = 2; lower < sqrt(n); lower++) {
      if (counter % lower == 0) {
        isPrime = false;
      }
      arr[counter] = isPrime;
      // uncomment this for geting thread_ids
      // printf("Index %d computed by thread %d\n", counter,
      // omp_get_thread_num());
    }
    // check value of isPrime
  }
  printf("Prime numbers: \n");
  for (int i = 1; i < n; i++) {
    if (arr[i]) { // if value is 1 ,it means that number is prime

      sprintf(&stringArr[i], "%d", i);

      write(fd, &stringArr[i],
            number); // write system call
      printf("%s ", &stringArr[i]);
    }
  }
  printf("\n");

  close(fd);
  return 0;
}