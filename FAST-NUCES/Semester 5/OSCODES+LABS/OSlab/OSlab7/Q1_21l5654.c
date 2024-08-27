#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void* function_thread(void* arg)
{
    printf("Pid of thread is: %ld \t process id: %d\n", pthread_self(),getpid());

    pthread_exit(NULL);
   
}
int main()
{
    int n = 10;
    pthread_t thread[n];

    int i;
    for (i = 0; i < n; i++)
    {
    pthread_create(&thread[i], NULL,function_thread,NULL);
    }


    for (i = 0; i < n; i++)
    {
        pthread_join(thread[i], NULL);
    }
    
    return 0;
}