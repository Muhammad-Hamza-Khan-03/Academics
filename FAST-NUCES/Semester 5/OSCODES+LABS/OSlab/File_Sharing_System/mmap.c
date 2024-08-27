#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
int main() {
  // void *mmap(void *addr, size_t length, int prot, int flags,
  //           int fd, off_t offset);
  // int munmap(void *addr, size_t length);
  int fd;
  fd = open("file.txt", O_RDONLY);
  if (fd < 0) {
    perror("FILE");
    exit(EXIT_FAILURE);
  }
  struct stat sb;
  if (fstat(fd, &sb) == -1) {
    perror("fstat");
    exit(EXIT_FAILURE);
  }
  char *file_in_memory =
      (char *)mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (file_in_memory == MAP_FAILED) {
    perror("mmap");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < sb.st_size; i++) {
    if (file_in_memory[i] == 'a')
      file_in_memory[i] = 'a';
    printf("%c", file_in_memory[i]);
  }
  munmap(file_in_memory, sb.st_size);
  return 0;
}
