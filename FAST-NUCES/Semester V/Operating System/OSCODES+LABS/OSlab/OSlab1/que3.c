#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char**argv)
{
int i,sum;
float avg;
sum=0;
for(i=1;i<argc;i++)
{
sum+=atoi(argv[i]);

}
printf("sum : %d",sum);
avg = sum/(argc-1);
printf("avg: %f",avg);
return 0;
}