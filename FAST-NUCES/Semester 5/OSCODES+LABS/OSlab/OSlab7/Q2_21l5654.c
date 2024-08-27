#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void* summation(void * arg)
{
    int numbers_sum = *(int *)arg;
    int sum = 0;

    for (int i = 0; i <= numbers_sum; i++)
    {
        sum += i;
        printf("sum = %d\n", sum);
    }

    printf("Total sum = %d\n", sum);
    pthread_exit(&sum);
}
int main()
{
    int N = 5;
    pthread_t thread;
    
    pthread_create(&thread, NULL, summation, (void *) &N);

    pthread_join(thread, NULL);
    
    return 0;
}