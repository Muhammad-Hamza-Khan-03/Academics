#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    const char* pipeName = "calculator_pipe"; // Updated variable name
    int pipeDescriptor = open(pipeName, O_WRONLY); // Updated variable name

    if (pipeDescriptor == -1) {
        perror("Error opening the named pipe (server is not running)");
        exit(1);
    }

    char userInput[256]; // Updated variable name
    char calculationResult[256]; // Updated variable name

    while (1) {
        printf("Enter operator and two operands (e.g., + 4 10): ");
        fgets(userInput, sizeof(userInput), stdin);

        // Write the user input data to the server through the named pipe
        write(pipeDescriptor, userInput, strlen(userInput) + 1);

        // Read and display the result from the server
        read(pipeDescriptor, calculationResult, sizeof(calculationResult));
        printf("Client: %s", calculationResult);
    }

    close(pipeDescriptor);
    return 0;
}
