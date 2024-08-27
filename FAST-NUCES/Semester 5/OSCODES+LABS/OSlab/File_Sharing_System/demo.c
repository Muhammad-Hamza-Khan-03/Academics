#include <stdio.h>
#include <string.h>

void tokenization(char *input, char tokens[][20]) {
  int i = 0;
  char *token = strtok(input, " \t\n");
  while (token != NULL) {
    strcpy(tokens[i], token);
    token = strtok(NULL, " \t\n");
    i++;
  }
}

int main() {
  char shared[] = "my name is aaaaaaaaaaaaaaaaaa";
  char *tokens;
  char *mai;
  tokens = strtok(shared, " /t/n");
  while (tokens != NULL) {
    mai = tokens;
    printf("%s\n", mai);
    tokens = strtok(NULL, " \t\n");
  }

  return 0;
}
