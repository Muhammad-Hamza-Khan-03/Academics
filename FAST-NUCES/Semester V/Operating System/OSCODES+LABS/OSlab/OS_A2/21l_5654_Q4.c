
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

typedef struct {
  int size;
  int *arr;
} arr_struct;
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
void *max(void *arg) {
  arr_struct *args = (arr_struct *)arg;
  int *list = args->arr;
  int size = args->size;

  // sort
  for (int i = 0; i < size - 1; i++) {
    for (int j = 1; j < size - i; j++) {
      if (list[j] > list[j + 1]) {
        swap(&list[j], &list[j + 1]);
      }
    }
  }
  int *maximum_n = malloc(sizeof(int));
  *maximum_n = list[size - 1];
  pthread_exit(maximum_n);
}

void *min(void *arg) {

  arr_struct *args = (arr_struct *)arg;
  int *list = args->arr;
  int size = args->size;

  // sort
  for (int i = 0; i < size - 1; i++) {
    for (int j = 1; j < size - i; j++) {
      if (list[j] > list[j + 1]) {
        swap(&list[j], &list[j + 1]);
      }
    }
  }
  int *min_n = malloc(sizeof(int));
  *min_n = list[0];
  pthread_exit(min_n);
}
void *avg(void *arg) {
  arr_struct *arr = (arr_struct *)arg;
  int *list = arr->arr;
  int size = arr->size;

  double sum = 0.0;
  for (int i = 0; i < size; i++) {
    sum += list[i];
  }
  int *average_ = malloc(sizeof(int));
  *average_ = sum / size;
  pthread_exit(average_);
}
int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Enter valid Numbers\n");
    return 1;
  }
  int size = argc - 1;
  // int *numbers = (int *)malloc(size * sizeof(int));
  int arr[size];
  for (int i = 0; i < size; i++) {
    arr[i] = atoi(argv[i + 1]);
  }

  arr_struct obj[2] = {size, arr};
  pthread_t id_avg, id_max, id_min;

  pthread_create(&id_avg, NULL, avg, &obj);
  pthread_create(&id_max, NULL, max, &obj);
  pthread_create(&id_min, NULL, min, &obj);

  void *ave;
  void *maxi;
  void *mini;
  pthread_join(id_avg, &ave);
  pthread_join(id_max, &maxi);
  pthread_join(id_min, &mini);
  int res_avg = *(int *)ave;
  int res_max = *(int *)maxi;
  int res_min = *(int *)mini;
  printf("\nAverage Number: %d ", res_avg);
  printf("\nMaximum Number:%d", res_max);
  printf("\nMinimum number :%d\n", res_min);
  return 0;
}