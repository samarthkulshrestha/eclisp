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


typedef struct {
    int type;
    long num;
    int err;
} lval;

enum { LVAL_NUM, LVAL_ERR };
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

lval lval_num(long x) {
    lval v;
    v.type = LVAL_NUM;
    v.num = x;
    return v;
}

lval lval_err(int x) {
    lval v;
    v.type = LVAL_ERR;
    v.err = x;
    return v;
}

void lval_print(lval v) {
    switch (v.type) {
        case LVAL_NUM: printf("%li", v.num); break;

        case LVAL_ERR:
            if (v.err == LERR_DIV_ZERO) {
                printf("error: division by zero.");
            }
            if (v.err == LERR_BAD_OP) {
                printf("error: invalid operator.");
            }
            if (v.err == LERR_BAD_NUM) {
                printf("error: invalid number.");
            }
        break;
    }
}

void lval_println(lval v) { lval_print(v); putchar('\n'); }

lval eval_op(lval x, char* op, lval y) {

    if (x.type == LVAL_ERR) { return x; }
    if (y.type == LVAL_ERR) { return y; }

    if (strcmp(op, "+") == 0) { return lval_num(x.num + y.num); }
    if (strcmp(op, "-") == 0) { return lval_num(x.num - y.num); }
    if (strcmp(op, "*") == 0) { return lval_num(x.num * y.num); }
    if (strcmp(op, "/") == 0) {
        // if second operand is zero, return error
        return y.num == 0
            ? lval_err(LERR_DIV_ZERO)
            : lval_num(x.num / y.num);
    }

    return lval_err(LERR_BAD_OP);
}

lval eval(mpc_ast_t* t) {
    // return directly if tagged as a number
    if (strstr(t->tag, "number")) {
        // check for conversion errors
        errno = 0;
        long x = strtol(t->contents, NULL, 10);
        return errno != ERANGE ? lval_num(x) : lval_err(LERR_BAD_NUM);
    }

    // the operator is always the second child
    char* op = t->children[1]->contents;

    // third child is x
    lval x = eval(t->children[2]);

    // iterate over remaining children
    int i = 3;
    while (strstr(t->children[i]->tag, "expr")) {
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }

    return x;
}

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
            lval result = eval(r.output);
            lval_println(result);
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
