#include<unistd.h>
#include<stdio.h>

int main(int argc,char*argv[])
{
    printf("\nName: %s \t Roll Number: %s \t Semester: %s",argv[0],argv[1],argv[2]);
    printf("The process ID in my_info is: %d",getpid());
    return 0;
}