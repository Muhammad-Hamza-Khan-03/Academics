#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    
    pid_t child1 = fork();

    if (child1 < 0) {
        printf("Fork Failed");
        return 1;
    }

    if (child1 == 0) {           // Child1

        execlp("mkdir", "mkdir", "demo_folder", NULL);
        
        exit(1);

    }
    else 
    {
        wait(NULL); // Wait for child1  

        pid_t child2 = fork();

        if (child2 < 0) 
        {
            printf("Fork Failed");
            return 1;
        }

        if (child2 == 0)      // Child process 2
        {
            execlp("touch", "touch", "demo_folder/file1.txt", "demo_folder/file2.txt", NULL);
            exit(1); 

        }
         else 
        {
            wait(NULL); // Wait for child2  

            pid_t child3 = fork();

            if (child3 < 0) 
            {
                printf("Fork failed");
                return 1;
            }

            if (child3 == 0) 
            {
                // Child 3
                execlp("ls", "ls", "demo_folder", NULL);
                exit(1); 

            } 
            else 
            {
                wait(NULL); // Wait for child3  

                pid_t child4 = fork();

                if (child4 < 0) {
                    printf("Fork Failed");
                    return 1;
                }

                if (child4 == 0) {
                    // Child process 4
                    execlp("rm", "rm", "-rf", "demo_folder", NULL);
                    exit(1);

                } else {
                    wait(NULL);
                }
            }
        }
    }

    return 0;
}
