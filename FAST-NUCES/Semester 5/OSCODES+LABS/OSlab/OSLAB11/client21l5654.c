#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
int main(int argc, char *argv[]) {

  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    perror("open");
    exit(1);
  }
  int shmid = shmget(1234, 1024, IPC_CREAT | 0666);
  if (shmid < 0) {
    perror("shmget");
    exit(1);
  }

  void *shmaddr = shmat(shmid, NULL, 0);

  char data[1024];
  ssize_t bytesRead = read(fd, data, sizeof(data));

  strcpy((char *)shmaddr, data);

  shmdt(shmaddr);

  return 0;
}
