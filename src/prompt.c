#include <stdio.h>


// declare a buffer for input size of 2048 bytes
static char input[2048];

int main(int argc, char** argv) {
    puts("eclisp version 0.1.0");
    puts("press ctrl+c to exit.\n");

    while (1) {
        fputs("ecl> ", stdout);
        fgets(input, 2048, stdin);
        printf("no! you're a %s", input);
    }

    return 0;
}
