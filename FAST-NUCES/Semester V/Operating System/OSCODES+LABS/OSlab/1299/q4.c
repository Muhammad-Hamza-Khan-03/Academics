#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int len;
int max;
int min;
float avg;

void *average(void *arg) {
    int *num = (int *)arg,i;
    int sum = 0;
    for (i = 0; i < len; i++) {
        sum += num[i];
    }
    avg = (float)sum / len;
    pthread_exit(NULL);
}

void *maximum(void *arg) {
    int *num = (int *)arg,i;
    max = num[0];
    for (i = 1; i < len; i++) {
        if (num[i] > max) {
            max = num[i];
        }
    }
    pthread_exit(NULL);
}

void *minimum(void *arg) {
    int *num = (int *)arg,i;
    min = num[0];
    for (i = 1; i < len; i++) {
        if (num[i] < min) {
            min = num[i];
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s ", argv[0]);
        return 1;
    }

    len = argc - 1;
    int *num = malloc(len * sizeof(int)),i;
    for (i = 0; i < len; i++) {
        num[i] = atoi(argv[i + 1]);
    }

    pthread_t tid[3];
    pthread_create(&tid[0], NULL, average, num);
    pthread_create(&tid[1], NULL, maximum, num);
    pthread_create(&tid[2], NULL, minimum, num);

    for (i = 0; i < 3; i++) {
        pthread_join(tid[i], NULL);
    }

    printf("The average value is %.2f\n", avg);
    printf("The minimum value is %d\n", min);
    printf("The maximum value is %d\n", max);

    free(num);

    return 0;
}
