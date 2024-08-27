#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define read_end 0
#define write_end 1

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Please input a positive a number");
    return 1;
  }

  int N = atoi(argv[1]);
  // pipe
  int fd[2];
  if (pipe(fd) < 0) {
    printf("Pipe creation failed");
    return -1;
  }

  pid_t process1 = fork();
  pid_t process2;
  if (process1 < 0) {
    printf("Child 1 Creation Failed");
    return -1;
  }
  // child process of process 1
  if (process1 == 0) {
    int sum = 0;
    for (int i = 1; i < N / 4; i++) {
      if (N % i == 0) {
        sum += i;
      }
    }
    close(fd[read_end]);
    write(fd[write_end], &sum, sizeof(sum));
    close(fd[write_end]);
  }
  // Parent process of process 1
  else {
    process2 = fork(); // 2nd child created
    if (process2 < 0) {
      printf("Child 2 Creation Failed");
      return -1;
    } else if (process2 == 0) {
      int sum2;
      for (int j = N / 4; j <= N / 2; j++) {
        if (N % j == 0) {
          sum2 += j;
        }
      }
      close(fd[read_end]);
      write(fd[write_end], &sum2, sizeof(sum2));
      close(fd[write_end]);
    }
    // Parent of process 2
    else {
      // result
      int sum, sum2;
      close(fd[write_end]);
      read(fd[read_end], &sum, sizeof(sum));
      read(fd[read_end], &sum2, sizeof(sum2));
      close(fd[read_end]);
      if (N == sum + sum2) {
        printf("Truee, %d is a perfect Number\n", N);
      } else {
        printf("Falsee, %d is not a perfect number\n", N);
      }
    }
  }

  return 0;
}
