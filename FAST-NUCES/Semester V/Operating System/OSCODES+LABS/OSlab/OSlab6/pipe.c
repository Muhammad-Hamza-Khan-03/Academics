#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>

int main()
{
    int named_pipe = mkfifo("pipe",0777);
    printf("\n named pipe has been created\n");
    return 0;
}