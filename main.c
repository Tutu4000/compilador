#include <stdio.h>
#include "lexer.h"

int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");

    if (!input) {
        printf("Could not open file %s\n", argv[1]);
        return 1;
    }

    init_lexer(input);
    Token token;

    printf("Tokens:\n");
    do {
        token = get_token();
        print_token(token);
    } while (token.token != TK_EOF && token.token != TK_ERROR);

    print_symbol_table();
    close_lexer();
    return 0;
} 