#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define read_end 0
#define write_end 1
#define size 100
char content[size];
int main(int argc, char *argv[]) // inputcopy.txt file.txt
{
  if (argc < 2) {
    printf("INVALID INPUT");
    exit(EXIT_FAILURE);
  }
  int pipefd[2];
  int fd = pipe(pipefd);
  if (fd == -1) {
    perror("Pipe");
    exit(EXIT_FAILURE);
  }
  pid_t pid = fork();
  if (pid < 0) {
    perror("FORK");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {
    // child
    // write
    char buf[size];
    read(pipefd[read_end], buf, size);
    close(pipefd[read_end]);
    int fd = open(argv[2], O_WRONLY);

    write(fd, buf, strlen(buf));
    printf("%s", buf);
    close(pipefd[write_end]);

  } else {
    char buf[size];
    close(pipefd[read_end]);
    int fd = open(argv[1], O_RDONLY);
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buf, size)) > 0) {
      write(pipefd[write_end], buf, strlen(buf));
    }
    printf("%s", buf);
    wait(NULL);
    close(pipefd[write_end]);
  }
  return 0;
}