#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int fibbonacci(int n)
{
    if(n <= 1) 
    {
      return n;
    }
    return (fibbonacci(n-1) + fibbonacci(n-2));
}
int main(int argc,char*argv[]) 
{
   
   printf("Fibbonacci of %d: " , atoi(argv[0]));
    int i;
    for(i = 0;i<atoi(argv[0]);i++) 
    {
      printf("%d ",fibbonacci(i));            
    }
    printf("\n");
}