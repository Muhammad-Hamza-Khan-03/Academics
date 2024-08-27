#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    const char* pipeName = "calculator_pipe"; // Updated variable name
    mkfifo(pipeName, 0666); // Create a named pipe

    char buffer[256]; // Updated variable name
    int pipeDescriptor = open(pipeName, O_RDONLY); // Updated variable name

    while (1) {
        read(pipeDescriptor, buffer, sizeof(buffer)); // Read data from the client
        char operator;
        double operand1, operand2, result;

        // Parse the input buffer to extract operator and operands
        sscanf(buffer, "%c %lf %lf", &operator, &operand1, &operand2);

        // Perform the requested calculation based on the operator
        switch (operator) {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                if (operand2 != 0) {
                    result = operand1 / operand2;
                } else {
                    printf("Error: Division by zero\n");
                    result = 0;
                }
                break;
            default:
                printf("Error: Invalid operator\n");
                result = 0;
        }

        // Print the result of the calculation
        printf("Server: %c %.2lf %.2lf = %.2lf\n", operator, operand1, operand2, result);
    }

    close(pipeDescriptor);
    unlink(pipeName); // Remove the named pipe when done
    return 0;
}
