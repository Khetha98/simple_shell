#include "declare.h"

void execute_the_command(const char *thecommand){
    __pid_t new_pid = fork();

    if (new_pid == 1){
        perror("fork");
        exit(EXIT_FAILURE);
    }else if (new_pid == 0){
        execlp(thecommand,thecommand, (char *)NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }else{
        wait(NULL);
    }
}