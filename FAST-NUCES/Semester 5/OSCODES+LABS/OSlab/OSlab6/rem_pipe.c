#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
int main()
{
    if(unlink("pipe")==0){
        printf("\nPipe has been removed\n");    
    }
    else{
        printf("\nPipe not found\n");
    }
    return 0;
}