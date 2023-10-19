#include "declare.h"

void take_command(char *thecommand, size_t size){
    if (fgets(thecommand, size,stdin) == NULL){
        if (feof(stdin)){
            the_print("\n");
            exit(EXIT_SUCCESS);
        } else {
            the_print("Error while reading input.\n");
            exit(EXIT_FAILURE);

        }
    }
    thecommand[strcspn(thecommand, "\n")] ='\0';
}