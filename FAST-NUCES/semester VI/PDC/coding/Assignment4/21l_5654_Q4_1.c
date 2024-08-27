#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void onetoallbc(int d, int myid, char *X) {
  int mask = pow(2, d) - 1;

  for (int i = d - 1; i >= 0; i--) {
    mask ^= (1 << i);

    if ((myid & mask) == 0) {
      if ((myid & (1 << i)) == 0) {
        int msg_dest = myid ^ (1 << i);
        printf("Process %d sending message to process %d\n", myid, msg_dest);
      } else {
        int msg_source = myid ^ (1 << i);
        printf("Process %d receiving message from process %d\n", myid,
               msg_source);
      }
    }
  }
}

int main() {
  int d = 3;                     // Dimension
  int num_processes = pow(2, d); // Total processes
  char X[] = "Hello, world!";

  for (int myid = 0; myid < num_processes; myid++) {
    onetoallbc(d, myid, X);
  }

  return 0;
}
