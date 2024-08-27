#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define read_end 0
#define write_end 1
int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("Enter source and destenation files");
    return 1;
  }
  char *inputfile = argv[1];
  char *outputfile = argv[2];
  int fd[2];
  if (pipe(fd) != 0) {
    perror("The pipe not created");
    return 1;
  }
  pid_t pid = fork();
  if (pid > 0) {
    char read_buf[100];
    int fd_read = open(inputfile, O_RDONLY);
    read(fd_read, read_buf, sizeof(read_buf));
  }
  return 0;
}