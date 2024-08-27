#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdbool.h>
#include<sys/stat.h>
#include<sys/types.h>
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
int main(int argc,char* argv[])
{

    if(mkfifo("pipe",0777)==-1)
    {

        printf("Could not create fifo");
        return 1;
    }
    int pipe = open("pipe",O_WRONLY);
    write(pipe,argv[1],sizeof(argv[1])+1);
    close(pipe);
    int numbers[256];
    int fd = open("pipe",O_RDONLY);
    int bytes_read = read(fd,numbers,256);
    for(int i=0;i<bytes_read;i++){
    printf("%d ",numbers[i]);
    }
        printf("\nPalindrome Numbers:\n");
    for (int j = 0; j < bytes_read; j++)
    {
        if(isPalindrome(numbers[j]))
        {
            printf("%d\n",numbers[j]);
        }
    }
    printf("\n");


    close(fd);
    return 0;
}