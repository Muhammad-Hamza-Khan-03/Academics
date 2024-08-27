#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    printf("PID of main program is: %d",getpid());

    pid_t pid = fork();

    if(pid<0) 
    {
        printf("\nfork failed\n");
        return 1;
    }
    else if(pid == 0)
    {
        //child
        char* arguments[] = {"Muhammad Hamza Khan","21l-5654","BDS-5C",NULL};
        execv("./my_info",arguments);
       
    }
    else{
        //parent
        printf("\nParent program has pid: %d",getpid());
    }
 return 0;   
}