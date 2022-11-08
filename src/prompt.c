#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>


int main(int argc, char** argv) {
    puts("eclisp version 0.1.0");
    puts("press ctrl+c to exit.\n");

    while (1) {
        char* input = readline("eclisp> ");
        add_history(input);
        printf("no! you're a %s\n", input);
        free(input);
    }

    return 0;
}
