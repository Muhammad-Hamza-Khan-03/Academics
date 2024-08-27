#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
struct car {
  char make[16];
  int year;
  int price;
};
// add /display/edit
void add(void *arg);
void *display(void *arg) { pthread_exit(NULL); }
void edit(void *arg);

int main() {
  int fd = open("carinfo.bin", O_RDONLY);
  struct stat sb;
  fstat(fd, &sb);
  char *map =
      mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

  pthread_t thread;
  int choice;
  struct car c;

  scanf("%d", &choice);
  switch (choice) {
  case 1:
    pthread_create(&thread, NULL, display, &c);
    pthread_join(thread, NULL);
  }
  //  pthread_t pthread;
  //   pthread_create(&pthread, NULL, display, 0);
  //   pthread_join(pthread, NULL);
  return 0;
}