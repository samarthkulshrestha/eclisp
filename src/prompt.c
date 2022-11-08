#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32

#include <string.h>

static char buffer[2048];

// fake readline func
char* readline(char* prompt) {
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char* cpy = malloc(strlen(buffer)+1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy)-1] = '\0';
    return cpy
}

// fake add_history func
void add_history(char* unused) {}

#else

#include <editline/readline.h>
#include <histedit.h>

#endif


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
