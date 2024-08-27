#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include<fcntl.h>

//global
long int thread_ids[4];

struct struct_fib{
    int size;
    int *Fibarr;
    int count_even;
    int count_odd;
    int total_sum;
}args;



void* fibonnaci_generator(void* arg)
{
    struct struct_fib *a = (struct struct_fib *) arg;
    int size = a->size;
    int * fibSequence = a->Fibarr;  

    fibSequence[0] = 0;
    fibSequence[1] = 1;
    int i;
    for (i = 2; i <= size; i++){
        fibSequence[i] = fibSequence[i-1] + fibSequence[i-2];
    }    
    thread_ids[0] = pthread_self();
    pthread_exit(NULL);
}

void* count_of_even(void* arg)
{
    struct struct_fib *a = (struct struct_fib *) arg;
    int*fib_array = a->Fibarr;
    int size_of_arr = a->size;
    int* count_even = &(a->count_even);
    
    int i;
    
    for(i = 0; i < size_of_arr; i++)
    {
        if(fib_array[i] % 2 == 0)
            (*count_even)++;
    }
    
    thread_ids[1] = pthread_self();
    pthread_exit(NULL);
}

void* count_of_odd(void* arg)
{
    struct struct_fib *a = (struct struct_fib *) arg;
    int*fib_array = a->Fibarr;
    int size_of_arr = a->size;
    int* count_odd = &(a->count_odd);
    
    int i;
    
    for(i = 0; i < size_of_arr; i++)
    {
        if(fib_array[i] % 2)
            (*count_odd)++;
    }
    
    thread_ids[2] = pthread_self();
    pthread_exit(NULL);
}

void* summation(void * arg)
{
    struct struct_fib *a = (struct struct_fib *) arg;
    int*fib_array = a->Fibarr;
    int size_of_arr = a->size;
    int *sum = &(a->total_sum);
    int i;
    for(i = 0; i < size_of_arr; i++)
    {
        *(sum) += fib_array[i];
    }
    thread_ids[3] = pthread_self();
    pthread_exit(NULL);
}

int main()
{
    int num = 8; //pass this from cli

    int fib_sequence[num];
    int even;
    struct struct_fib arg_Fib;
    arg_Fib.size = num;
    arg_Fib.Fibarr = fib_sequence;

    pthread_t thread[4];
    
    pthread_create(&thread[0], NULL, fibonnaci_generator, &arg_Fib);
    pthread_create(&thread[1], NULL, count_of_even, &arg_Fib);
    pthread_create(&thread[2], NULL, count_of_odd, &arg_Fib);
    pthread_create(&thread[3], NULL, summation, &arg_Fib);
    
    for(int i = 0; i < 4; i++)
    {
        pthread_join(thread[i], NULL);
    }
    
    printf("Thread ID = %lld \tSeries: ",thread_ids[0]);
    for(int i = 0; i < num; i++)
    {
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
