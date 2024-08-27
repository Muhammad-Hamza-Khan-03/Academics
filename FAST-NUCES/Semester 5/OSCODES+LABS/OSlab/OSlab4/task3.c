#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(int argc,char*argv[]) 
{
   if(argc==1)
   {
    printf("Input a number:");
    return 1;
   }
   pid_t pid=fork();
   if(pid<0)
   {
    printf("Fork Failed");
    return 1;
   }
   else if(pid==0)
   {
    //child
    char* arguments[]={argv[1],NULL};
    execv("./fibonnaci",arguments);
   }
   else{
    //parent
    wait(NULL);

   }
   return 0;
}