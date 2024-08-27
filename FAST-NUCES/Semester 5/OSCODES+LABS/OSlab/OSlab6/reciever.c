#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdbool.h>
#define size 256

/*the logic is to traverse the string from left and right towards middle and if 
the characters are same then it is palindorme else it is not*/
bool isPalindrome(int n)
{
    //converting number n to string
    char str[20];
    sprintf(str, "%d", n);

    int left = 0;
    int right = strlen(str) - 1;
    while (left <= right) {
        if (str[left] != str[right]) {
            return 0;
        }
        left++;
        right--;
    }
    return 1;
}
int main()
{
    int fd = open("pipe",O_RDWR);

    char read_file_name[size];

    read(fd,read_file_name,size);
    close(fd);
    printf("File Name: %s \n",read_file_name);

    int fd_file = open(read_file_name,O_RDONLY);
    
    if(fd_file==-1)
    {
        printf("File read failed");
        return 1;
    }
    
    char buffer[size];
    ssize_t bytes_read = read(fd_file,buffer,sizeof(buffer));
    
    if(bytes_read<0)
    {
        printf("Problem in bytes read");
        exit(1);
    }
    printf("Numbers: %s",buffer);

    //tokenization
    char *token = strtok(buffer, " \n");
   
    int i = 0;//store count of numbers in i
    int numbers[size];
    
    while (token != NULL && i < size)
    {
        numbers[i++] = atoi(token);
        token = strtok(NULL, " \t\n");
    }

    printf("\nPalindrome Numbers:\n");
    for (int j = 0; j < i; j++)
    {
        if(isPalindrome(numbers[j]))
        {
            printf("%d\n",numbers[j]);
        }
    }
    printf("\n");
    close(fd)
 return 0;       
}
    
    