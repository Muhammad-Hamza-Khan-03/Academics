#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>



char** tokenization(char *input, char *tokens[])
{
    int i;
    char *token = strtok(input, " \t\n");
    for (i = 0; token != NULL; i++)
    {
        tokens[i] = token;
        token = strtok(NULL, " \t\n");
    }
    tokens[i] = NULL;

    return tokens;
}
char calculate_grade(int marks)
{
    if (marks >= 80 && marks <= 100)
        return 'A';
    else if (marks >= 70)
        return 'B';
    else if (marks >= 60)
        return 'C';
    else if (marks >= 50)
        return 'D';
    else
        return 'F';
}
int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("Input The File Name in the command line \n");
        exit(1);
    }


    // Open the file
    int fd =open(argv[1], O_RDONLY);

    if (fd < 0)
        {   printf("File Error");
            return 1;
        }
    printf("%s file opened successfully\n",argv[1]);
    int marks[25];
    char roll_number[25][10],grades[25][2],line[14];
    char *tokens[14];
    
    int count,number_of_tuples=5;
    //reading the file
    for (count = 0; count < number_of_tuples; count++) 
    {
        ssize_t bytes_read = read(fd, line, sizeof(line)); 
    
        if (bytes_read <= 0)
        break;
     
        tokenization(line, tokens);

        strcpy(roll_number[count], tokens[0]);
        marks[count] = atoi(tokens[1]);
        strcpy(grades[count], tokens[2]);
        line[bytes_read] = '\0';
        
    }
    // Close the file
    close(fd);

    //working of output file
    int output_fd = open("outputfile.txt",O_RDWR);
    if (output_fd < 1)
    {    printf("Failed to open output.txt");
        return 1;
    }
    printf("\nOutput file is working on data.\n");
    pid_t child1,child2;

    child1 = fork();
    if(child1<0)
    {
        printf("\nChild 1 Fork failed\n");
    }
    
    else if(child1==0)
    {
        
        
        child2=fork();
        if(child2<0) printf("\nChild 2 Fork failed\n");
        else if(child2==0)
        {
            int i;
            char updated_grades[25][2];
            for(i=0;i<count;i++)
            {
                updated_grades[i][0]=calculate_grade(marks[i]);
                updated_grades[i][1]='\0';
            }
            int x;
            for(x=0;x<number_of_tuples;x++)
            {
                char mark_str[10];
                sprintf(mark_str, "%d", marks[x]);

                write(output_fd,roll_number[x],sizeof(roll_number[x])-2);
                write(output_fd,"\t",1);
                write(output_fd,mark_str,strlen(mark_str));
                write(output_fd,"\t",1);
                write(output_fd,&updated_grades[x],sizeof(char));
                write(output_fd,"\n",1);
            }
        }
        else{
            wait(NULL);
        }
    }
    else{
        wait(NULL);
    }
    close(output_fd);
    
    return 0;
}
