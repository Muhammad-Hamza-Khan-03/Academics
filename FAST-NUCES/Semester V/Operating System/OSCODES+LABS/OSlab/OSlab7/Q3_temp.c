#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include<fcntl.h>
long long int thread_ids[4];
struct arg_struct{
    int limit;
    int *ptrFib;
    int count_even;
    int count_odd;
    int total_sum;
}args;

long long int show_threads_id()
{
    //printf("ID = %ld \n", pthread_self());
    return pthread_self();
}

void* fibonnaci_generator(void* arg)
{
    struct arg_struct *a = (struct arg_struct *) arg;
    int size = a->limit;
    int * fibSequence = a->ptrFib;  

    fibSequence[0] = 0;
    fibSequence[1] = 1;
    int i;
    for (i = 2; i <= size; i++){
        fibSequence[i] = fibSequence[i-1] + fibSequence[i-2];
    }    
    thread_ids[0] = show_threads_id();
    pthread_exit(NULL);
}

void* count_of_even(void* arg)
{
    struct arg_struct *a = (struct arg_struct *) arg;
    int*fib_array = a->ptrFib;
    int size_of_arr = a->limit;
    int* count_even = &(a->count_even);
    
    int i;
    
    for(i = 0; i < size_of_arr; i++)
    {
        if(fib_array[i] % 2 == 0)
            (*count_even)++;
    }
    
    thread_ids[1] = show_threads_id();
    pthread_exit(NULL);
}

void* count_of_odd(void* arg)
{
    struct arg_struct *a = (struct arg_struct *) arg;
    int*fib_array = a->ptrFib;
    int size_of_arr = a->limit;
    int* count_odd = &(a->count_odd);
    
    int i;
    
    for(i = 0; i < size_of_arr; i++)
    {
        if(fib_array[i] % 2)
            (*count_odd)++;
    }
    
    thread_ids[2] = show_threads_id();
    pthread_exit(NULL);
}

void* summation(void * arg)
{
    struct arg_struct *a = (struct arg_struct *) arg;
    int*fib_array = a->ptrFib;
    int size_of_arr = a->limit;
    int *sum = &(a->total_sum);
    int i;
    for(i = 0; i < size_of_arr; i++)
    {
        *(sum) += fib_array[i];
    }
    thread_ids[3] = show_threads_id();
    pthread_exit(NULL);
}

int main()
{
    int num = 8; //pass this from cli

    int fib_sequence[num];
    int even;
    struct arg_struct arg_Fib;
    arg_Fib.limit = num;
    arg_Fib.ptrFib = fib_sequence;

    pthread_t thread[4];
    
    if(pthread_create(&thread[0], NULL, fibonnaci_generator, &arg_Fib) == -1)
    {
        printf("Thread failed to create");
    }
    if(pthread_create(&thread[1], NULL, count_of_even, &arg_Fib) == -1)
    {
        printf("Thread even failed to create");
    }
    if(pthread_create(&thread[2], NULL, count_of_odd, &arg_Fib) == -1)
    {
        printf("Thread Odd failed to create");
    }

    if(pthread_create(&thread[3], NULL, summation, &arg_Fib) == -1)
    {
        printf("Thread Sum failed to create");
    }
    
    for(int i = 0; i < 4; i++)
    {
        pthread_join(thread[i], NULL);
    }
    printf("Thread ID = %lld \tSeries: ",thread_ids[0]);
    for(int i = 0; i < num; i++)
    {
        //printf("Thread ID: %ld - %d\n", pthread_self(), fib_sequence[i]);
        printf(" %d ",fib_sequence[i]);
    }
    printf("\n");

    printf("Thread ID: %lld - even numbers: %d\n", thread_ids[1], arg_Fib.count_even);
    printf("Thread ID: %lld - Odd numbers: %d\n", thread_ids[2], arg_Fib.count_odd);
    printf("Thread ID: %lld - Total Sum of numbers: %d\n", thread_ids[3], arg_Fib.total_sum);
    
     // Write sum to file
    int fd = open("sum.txt", 'w');
    if (fd < 0) {
        printf("Error opening file.\n");
        return 1;
    }
    write(fd, &arg_Fib.total_sum,4);
    close(fd);
    return 0;
}
