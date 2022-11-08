#include <stdio.h>
#include <stdlib.h>
#include "lib/mpc.h"

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
    // parsers
    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* Eclisp = mpc_new("eclisp");

    // grammar def
    mpca_lang(MPCA_LANG_DEFAULT,
        "\
            number: /-?[0-9]+/;                             \
            operator: '+' | '-' | '*' | '/';                \
            expr: <number> | '(' <operator> <expr>+ ')';    \
            eclisp: /^/ <operator> <expr>+ /$/;             \
        ",
        Number, Operator, Expr, Eclisp);

    puts("eclisp version 0.1.0");
    puts("press ctrl+c to exit.\n");

    while (1) {
        char* input = readline("eclisp> ");
        add_history(input);

        // attempt to parse user input
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Eclisp, &r)){
            // on success print AST
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        } else {
            // otherwise print error
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);
    }

    // undefine and delete parsers
    mpc_cleanup(4, Number, Operator, Expr, Eclisp);

    return 0;
}
