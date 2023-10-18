#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFFER_SIZE 1024



/**
 * main - Entry point for a simple shell.
 *
 * This function implements a basic shell that reads user commands, forks a child process to execute them,
 * and waits for the child process to complete. It continues to loop until the user presses Ctrl+D, indicating the end of input.
 *
 * Return: Always returns 0 upon successful execution.
 */

int main() {
    char *input;
    size_t input_size = 0;
    ssize_t read_chars;

    while (1) {
        printf("#cisfun$ ");


	input = NULL;
        read_chars = getline(&input, &input_size, stdin);

	if (read_chars == -1) {
            printf("\n");
            free(input);
            break;
        }



        if (read_chars > 0 && input[read_chars - 1] == '\n') {
            input[read_chars - 1] = '\0';
        }

        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            free(input);
            continue;
        }

	if (child_pid == 0) { // Child process
            if (execve(input, NULL, NULL) == -1) {
                perror("execve");
                free(input);
                exit(EXIT_FAILURE);
            }
        } else { // Parent process
            int status;
            wait(&status);
            free(input);
        }
    }

    return 0;
}

