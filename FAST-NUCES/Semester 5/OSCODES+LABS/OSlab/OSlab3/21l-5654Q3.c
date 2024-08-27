#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

void pid_function(int input)
{

	int i;

	for(i=0;i<input;i++)
		{
			pid_t pid= fork();

			if(pid<0)
			{
				printf("Child not created");
			} 
			else if(pid == 0)
			{
					printf("The pid of child is %d and the pid of parent is %d\n",getpid(),getppid());
			}
			else{
			wait(NULL);
			break;
			}
		}
}
int main(int argv,char**argc)
{
	if(argv<2)
	{
		printf("Enter a value beween 1 to 10\n");
        exit(1);
	}
	
	int input=atoi(argc[1]);	
	
	pid_function(input);
	
return 0;
}