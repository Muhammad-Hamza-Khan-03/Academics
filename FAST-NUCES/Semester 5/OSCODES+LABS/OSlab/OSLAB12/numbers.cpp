#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define FILE_SIZE 100

void printFileContents(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file to print contents");
    return;
  }
  char ch;
  while ((ch = fgetc(file)) != EOF) {
    putchar(ch);
  }
  printf("\n");
  fclose(file);
}
void *replaceIntegers(void *arg) {
  char *map = (char *)arg;
  for (int i = 0; i < FILE_SIZE / 2; ++i) {
    if (map[i] >= '0' && map[i] <= '9') {
      map[i] = ' ';
    }
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }
  printf("Original file:\n");
  printFileContents(argv[1]);

  int fd = open(argv[1], O_RDWR);
  if (fd == -1) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  char *map =
      (char *)mmap(0, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (map == MAP_FAILED) {
    perror("Error mapping the file");
    close(fd);
    return EXIT_FAILURE;
  }

  pthread_t threads[2];
  pthread_create(&threads[0], NULL, replaceIntegers, map);
  pthread_create(&threads[1], NULL, replaceIntegers, map + 50);
  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);

  munmap(map, FILE_SIZE);
  close(fd);

  printf("\nUpdated file:\n");
  printFileContents(argv[1]);

  return EXIT_SUCCESS;
}
