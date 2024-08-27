#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define BUFFER_SIZE 25

void tokenization(char *input, char *tokens[]) {
  int i;
  char *token = strtok(input, " \t\n");
  for (i = 0; token != NULL; i++) {
    tokens[i] = token;
    token = strtok(NULL, " \t\n");
  }
  tokens[i] = NULL;
}
int main() {

  char input[BUFFER_SIZE];     // user input
  char *arg_list[BUFFER_SIZE]; // store arguments list

  printf("\n\nOpening Termainal:\n\n");
  while (1) {
    printf("Ammars shell: l1AK1 Shell >$");
    fgets(input, BUFFER_SIZE, stdin); // take input from user

    if (strcmp(input, "exit\n") ==
        0) // if user enters exit, the program will terminate
    {
      printf("\nExiting the terminal\n");
      // printf("break");
      return 1;
    }

    tokenization(input, arg_list);
    pid_t pid = fork();

    if (pid < 0) // if child not created
    {
      printf("\nChild creation error\n");
      // break;
      exit(1);
    }
    if (pid == 0) // if child created successfully
    {
      // running shell commands
      if (execvp(arg_list[0], arg_list) ==
          -1) // if execvp terminated abnormally
      {
        printf("\nTerminated Incorrectly\n");
        exit(1);
      }
      exit(1);
    } else { // parent process
      wait(NULL);
    }
  }
  return 0;
}