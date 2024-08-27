#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int is_perfect(int n) {
    int sum = 0,i;
    for (i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i * i != n) {
                sum += n / i;
            }
        }
    }
    return sum == n * 2;
}

void child_process(int start, int end, int n, int pipe_fd[]) {
    int i,sum = 0;
    for (i = start; i <= end; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    write(pipe_fd[1], &sum, sizeof(sum));
    close(pipe_fd[1]);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s N\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("N must be a positive integer\n");
        return EXIT_FAILURE;
    }

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        return EXIT_FAILURE;
    } else if (pid1 == 0) {
        child_process(1, n / 4, n, pipe_fd);
        return EXIT_SUCCESS;
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        return EXIT_FAILURE;
    } else if (pid2 == 0) {
        child_process(n / 4 + 1, n / 2, n, pipe_fd);
        return EXIT_SUCCESS;
    }

    close(pipe_fd[1]);

    int sum1, sum2;
    read(pipe_fd[0], &sum1, sizeof(sum1));
    read(pipe_fd[0], &sum2, sizeof(sum2));
    close(pipe_fd[0]);

    int sum = sum1 + sum2 + n;

    printf("%s \n", is_perfect(n) ? "true" : "false");

    wait(NULL);
    wait(NULL);

    return EXIT_SUCCESS;
}

