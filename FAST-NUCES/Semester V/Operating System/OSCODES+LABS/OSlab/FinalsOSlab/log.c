/* local date and time example in C/C++ */
// For C
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  if (argc < 1) {
    printf("Provide output");
    return 1;
  }
  int fd = open("logfile.txt", O_WRONLY);

  for (int i = 0; i < atoi(argv[1]); i++) {

    pid_t pid = fork();
    if (pid < 0) {
      printf("child not created\n");
      break;
    } else if (pid == 0) {

      time_t rawtime;
      struct tm *timeinfo;

      time(&rawtime);
      timeinfo = localtime(&rawtime);
      // for C use
      int getmypid = getpid();
      char *s = asctime(timeinfo);
      printf("PID % d;Current local time and date: %s", getppid(),
             asctime(timeinfo));

      char buf[100];
      snprintf(buf, 100, "PID %d;Current local time and date: %s", getmypid, s);
      write(fd, buf, strlen(buf));

      sleep(1);
    } else if (pid > 0) {
      wait(NULL);

      break;
    }
  }
  return 0;
}
