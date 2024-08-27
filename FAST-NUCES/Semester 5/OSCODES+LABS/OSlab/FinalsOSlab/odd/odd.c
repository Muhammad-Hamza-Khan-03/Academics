#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define size 100
int main(int argc, char *argv[]) { // numbers.txt out.txt

  int fd;
  if (fd < 0) {
    perror("file not open");
    exit(EXIT_FAILURE);
  }
  fd = open(argv[1], O_RDONLY);
  ssize_t bytes_read;
  char buffer[size];
  int i = 0;
  int numbers[size];
  while ((bytes_read = read(fd, buffer, size)) > 0) {
    printf("%s\n", buffer);
    char *token = strtok(buffer, " \t\n");

    while (token != NULL) {
      // Convert token to an integer and print
      int number = atoi(token);
      if (number % 2 == 0) {
        numbers[i] = number;
        i++;
      }
      // printf("%d ", number);

      // Get the next token
      token = strtok(NULL, " \t\n");
    }
    printf("\n");
  }
  for (int it = 0; it < i; it++) {
    printf("%d ", numbers[it]);
  }

  return 0;
}