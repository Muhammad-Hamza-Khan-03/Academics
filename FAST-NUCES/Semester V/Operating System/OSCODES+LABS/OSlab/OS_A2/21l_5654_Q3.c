#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define size 1060
#define file "file.txt"

typedef struct {
  char word[50];
  int count;
} word_struct;
typedef struct {
  int start_seg;
  int end_seg;
} segment_area;

word_struct words[size];
char *tokens[size];
int word_count = 0;
int segment_size = 0;
int words_c = 0;
int seg_count = 0;

void *word_freq(void *arg) {
  segment_area *args = (segment_area *)arg;
  int segment_starts = args->start_seg;
  int segment_ends = args->end_seg;

  bool tok_match;
  for (int i = segment_starts; i < segment_ends; i++) {

    tok_match = false;

    for (int j = 0; j < word_count; j++) {
      if (strcmp(words[j].word, tokens[i]) == 0)
      /*If match found then count++ and tok_match = true*/
      {
        words[j].count++;
        tok_match = true;

        break;
      }
    }
    // no match found
    if (tok_match == 0) {
      // if match not found then we just copy string into word
      strcpy(words[word_count].word, tokens[i]);
      words[word_count].count = 1;
      word_count++;
    }
  }

  words_c += (segment_ends - segment_starts);
  printf(
      "Segment number %d:\n\t Segment Start %d - Segment End %d - Word count: "
      "%d\n",
      seg_count, segment_starts, segment_ends, words_c);
  seg_count++;
  pthread_exit(NULL);
}

int tokenize(char *input, char **tokens) {
  int wc = 0;

  char *token = strtok(input, " \t\n");
  while (token != NULL) {
    tokens[wc++] = token;
    token = strtok(NULL, " \t\n");
  }
  tokens[wc] = NULL;
  return wc;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Input a positive number of segments\n");
    return 1;
  }

  int segment = atoi(argv[1]);

  int fd = open(file, O_RDONLY);

  if (fd < 0) {
    perror("File open failed");
    return 1;
  }

  char buf[size];
  ssize_t bytes_read;
  bytes_read = read(fd, buf, size);
  printf("File Text is:\n%s\n", buf);

  // count words on basis of tokenization
  int number_of_words = tokenize(buf, tokens);

  segment_size = number_of_words / segment;
  pthread_t threads[segment];
  // segment start and ends
  int segment_starts;
  int segment_ends;

  for (int i = 0; i < segment; i++) {

    segment_starts = i * segment_size;
    if (i + 1 == segment) {
      segment_ends = number_of_words;
    }

    else {
      segment_ends = (i + 1) * segment_size;
    }

    segment_area args[2] = {segment_starts, segment_ends};

    pthread_create(&threads[i], NULL, word_freq, args);

    sleep(1);
  }

  for (int i = 0; i < segment; i++) {
    pthread_join(threads[i], NULL);
  }
  printf("Word\tCount\n");
  for (int i = 0; i < word_count; i++) {
    printf("%s\t%d\n", words[i].word, words[i].count);
  }

  close(fd);

  return 0;
}