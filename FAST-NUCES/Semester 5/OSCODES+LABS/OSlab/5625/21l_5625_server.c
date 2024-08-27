#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define size 250

int calculation(char sign, int num1, int num2) {
  int result = 0;
  switch (sign) {
  case '+':
    result = num1 + num2;
    break;
  case '-':
    result = num1 - num2;
    break;
  case '*':
    result = num1 * num2;
    break;
  case '/':
    if (num2 != 0) {
      result = num1 / num2;
    } else {
      printf("Error: Division by zero\n");
    }
    break;
  }
  return result;
}
int main() {
  const char *pipe_path = "mynamedpipe";
  mkfifo(pipe_path, 0666);

  int fd_server, fd_client;

  fd_server = open(pipe_path, O_RDWR);
  if (fd_server == -1) {
    printf("Can not open server pipe");
    return -1;
  }
  char buffer[size];

  ssize_t bytes_read = read(fd_server, buffer, sizeof(buffer));
  if (bytes_read < 0) {
    printf("File read error");
    return 1;
  }

  char sign;
  int num1, num2;

  sscanf(buffer, "%c %d %d", &sign, &num1, &num2);
  printf("The numbers are %d %c %d", num1, sign, num2);
  int result = calculation(sign, num1, num2);

  write(fd_server, &result, 4);
  close(fd_server);

  fd_client = open(pipe_path, O_WRONLY);

  if (fd_client == -1) {
    printf("Error opening the client named pipe");
    return -1;
  }

  if (write(fd_client, &result, sizeof(result)) == -1) {
    printf("Error writing to the client");
    return -1;
  }

  close(fd_client);

  return 0;
}
