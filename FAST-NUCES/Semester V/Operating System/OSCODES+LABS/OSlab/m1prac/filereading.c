#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void tokenize(char *list, char *tokens[]) {
  int i = 0;
  char *token = strtok(list, " \t\n");
  for (i = 0; token != NULL; i++) {
    tokens[i] = token;
    token = strtok(NULL, " \t\n");
  }
  tokens[i] = NULL;
}

// int main() {
//   char line[100];
//   int fd = open("input.txt", O_RDONLY);
//   if (fd < 0) {
//     perror("Error opening input file");
//     return 1;
//   }
//   int numbers[5];
//   char *tokens[10];

//   for (int i = 0; i < 5; i++) {
//     ssize_t bytes_read = read(
//         fd, line, sizeof(line) - 1); // Leave one byte for the null
//         terminator

//     if (bytes_read <= 0) {
//       break;
//     }

//     line[bytes_read] = '\0'; // Ensure the line is null-terminated
//     tokenize(
//         line, tokens,
//         10); // Pass the maximum number of tokens to prevent buffer overflow
//     numbers[i] = atoi(tokens[0]);
//   }

//   close(fd);

//   for (int r = 0; r < 5; r++) {
//     printf("line: %d\n", numbers[r]);
//   }

//   return 0;
// }

int main() {
  int fd = open("input.txt", O_RDONLY);
  char buff[100];
  char *tokens[50];
  read(fd, buff, sizeof(buff) - 1);
  tokenize(buff, tokens);
  int number[10];
  for (int i = 0; tokens[i] != NULL; ++i) {
    number[i] = atoi(tokens[i]);
    printf("%d\n", number[i]);
  }
  return 0;
}