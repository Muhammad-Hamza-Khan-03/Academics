#include <stdio.h>
#include <unistd.h>
void a() { sleep(1); }
int main(void) {
  int i = 0;
  a();
  pid_t pid = fork();
  a();
  if (pid == 0) {
    printf("par:%d", getpid());
    printf("\ni times %d\n", i);
    a();
    pid_t pid1 = fork();
    a();
    i++;
    if (pid1 == 0) {
      printf("\np child id:%d\n", getpid());
      a();
    } else if (pid1 > 0) {
      printf("su pid %d", getpid());
    }
  } else if (pid > 0) {
    printf("\npehe\n");
  }
  return 0;
}

// #include <stdio .h>
// int main(void) {
//   int pid = 0;
//   pid = fork(); // (1001)
//   if (pid == 0) {
//     printf("%d,", getpid()); // 1001
//     pid = fork();            // (10011)
//     if (pid == 0) {
//       printf("%d,", getpid()); // 10011
//       pid = fork();            // (100111)
//       if (pid > 0) {
//         printf("%d,", getpid()); // 10011
//         pid = fork();            // (100112)
//         if (pid > 0) {
//           printf("%d,", getpid()); // 10011
//           pid = fork();            // (100113)
//           if (pid == 0) {
//             printf("%d,", getpid()); // 100113
//           }
//         }
//       }
//     }

//   } else if (pid > 0) {
//     printf("%d,", getpid()); // 100
//   }
//   return 0;
// }