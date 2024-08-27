#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

void printFile(const char *mapped, size_t size) {
  fwrite(mapped, sizeof(char), size, stdout);
  printf("\n");
}

void replaceWordInFile(const char *fileName, const char *wordToReplace,
                       const char *replacementWord) {
  int fd = open(fileName, O_RDWR);
  if (fd == -1) {
    perror("Error opening file");
    return;
  }
  struct stat fileInfo;
  if (fstat(fd, &fileInfo) == -1) {
    perror("Error getting the file size");
    close(fd);
    return;
  }
  char *mapped = static_cast<char *>(
      mmap(0, fileInfo.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
  if (mapped == MAP_FAILED) {
    perror("Error mapping the file");
    close(fd);
    return;
  }

  printf("Original file:\n");
  printFile(mapped, fileInfo.st_size);

  size_t wordLen = strlen(wordToReplace);
  size_t replacementLen = strlen(replacementWord);
  size_t newSize = fileInfo.st_size;

  for (char *curr = mapped; curr < mapped + newSize - wordLen; ++curr) {
    if (strncmp(curr, wordToReplace, wordLen) == 0) {
      newSize += (replacementLen - wordLen);

      if (ftruncate(fd, newSize) == -1) {
        perror("Error extending the file");
        break;
      }

      munmap(mapped, fileInfo.st_size);
      mapped = static_cast<char *>(
          mmap(0, newSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
      if (mapped == MAP_FAILED) {
        perror("Error remapping the file");
        break;
      }

      memmove(curr + replacementLen, curr + wordLen,
              newSize - (curr - mapped) - replacementLen);
      memcpy(curr, replacementWord, replacementLen);
      curr += replacementLen - 1;
    }
  }
  printf("\nUpdated file:\n");
  printFile(mapped, newSize);

  munmap(mapped, newSize);
  close(fd);
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    fprintf(stderr, "Usage: %s <file> <word_to_replace> <replacement_word>\n",
            argv[0]);
    return EXIT_FAILURE;
  }

  replaceWordInFile(argv[1], argv[2], argv[3]);
  return EXIT_SUCCESS;
}
