#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "tokens.h"

#define MAX_LEXEME_LENGTH 1024
#define MAX_SYMBOLS 1000

typedef struct {
    int line;
    int column;
} Position;

typedef struct {
    char lexeme[MAX_LEXEME_LENGTH];
    int type;
    union {
        int int_value;
        float float_value;
        char char_value;
    } value;
} Symbol;

typedef struct {
    int token;
    char lexeme[MAX_LEXEME_LENGTH];
    Position pos;
    int symbol_table_index;
    union {
        int int_value;
        float float_value;
        char char_value;
    } value;
} Token;


void init_lexer(FILE *input);
Token get_token();
void close_lexer();
void print_token(Token token);


Symbol* lookup_symbol(const char* lexeme);
Symbol* insert_symbol(const char* lexeme, int type, void* value);
void print_symbol_table();



#endif