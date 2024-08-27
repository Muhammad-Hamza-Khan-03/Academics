#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define size 250

int main() {

  mkfifo("mynamedpipe", 0666);

  char input[size];

  printf("Enter operator and two operands: ");
  fgets(input, sizeof(input), stdin);

  int fd_server = open("mynamedpipe", O_WRONLY);
  if (fd_server == -1) {
    perror("Server pipe open nhi hoa");
    return -1;
  }

  write(fd_server, input, strlen(input));
  close(fd_server);

  int fd_client = open("mynamedpipe", O_RDONLY);
  if (fd_client == -1) {
    perror("Client pipe open nhi hoa");
    return -1;
  }
  sleep(10);
  int result = 0;
  printf("Reading from client pipe\n");
  read(fd_client, &result, sizeof(result));

  printf("Result: %d\n", result);

  close(fd_client);

  return 0;
}