#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int number_of_laps;
int lap_time;

void handler(int sig_number) {
  if (sig_number == SIGCHLD) {
    printf("SIGCHLD caught\n");
    printf("Total elapsed_time : % d\n", number_of_laps * lap_time);
  }
}

int main() {

  int current_lap = 0;
  int i;

  if (signal(SIGCHLD, handler) == SIG_ERR) {
    printf("SIGNAL CHILD NOT CHAUGHT\n");
  }
  printf("Enter Number of Laps:");
  scanf("%d", &number_of_laps);

  printf("Enter Lap time:");
  scanf("%d", &lap_time);
  pid_t pid = fork();
  if (pid < 0) {
    printf("Child creation error\n");
    exit(1);
  } else if (pid > 0) {
    // parent process

    wait(NULL);
  } else if (pid == 0) {
    // child process

    while (current_lap < number_of_laps) {
      i = 1;
      printf("\nlap_time:");

      while (i <= lap_time) {
        sleep(1);

        printf("%d ", i);
        i += 1;
      }
      printf("\nLap number %d Completed\n", ++current_lap);
    }
  }

  return 0;
}