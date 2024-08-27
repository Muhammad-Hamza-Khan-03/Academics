#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void selectionSort(int arr[], int n) {
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 11) {
        printf("\nEnter 10 values\n");

        return 1;
    }
	int i;
    int arr[10];
    for (i = 1; i <= 10; i++) {
        arr[i - 1] = atoi(argv[i]);
    }

    pid_t child_pid = fork();

    if (child_pid < 0) {
        printf("Fork failed.\n");
        exit(1);
    } else if (child_pid == 0) {
        
        selectionSort(arr, 10);

        printf("Child Process (PID: %d) Sorted Array: ", getpid());
        for (i = 0; i < 10; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        return 0;
    } else {
        printf("Parent Process (PID: %d) Original Array: ", getpid());
        for (i = 0; i < 10; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        return 0;
    }
}