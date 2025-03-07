#ifndef TOKENS_H
#define TOKENS_H

// reserved
#define TK_IF       1
#define TK_THEN     2
#define TK_ELSEIF   3
#define TK_ELSE     4
#define TK_WHILE    5
#define TK_DO       6

// relop
#define TK_EQ       7  // =
#define TK_NE       8  // <>
#define TK_LT       9  // <
#define TK_GT       10 // >
#define TK_LE       11 // <=
#define TK_GE       12 // >=

// aritop_sum
#define TK_SUM      13 // +
#define TK_SUB      14 // -

//aritop_mult
#define TK_MULT     15 // *
#define TK_DIV      16 // /

//aritop_pot
#define TK_POT      17 // **

// primitive
#define TK_CHAR     18
#define TK_INT      19
#define TK_FLOAT    20

// ids and consts
#define TK_ID           21
#define TK_CONST_INT    22
#define TK_CONST_FLOAT  23
#define TK_CONST_CHAR   24

// Special symbols
#define TK_ASSIGN           25 // :=
#define TK_COLON           26 // :
#define TK_SEMICOLON       27 // ;
#define TK_COMMA           28 // ,
#define TK_OPEN_BRACKET    29 // [
#define TK_CLOSE_BRACKET   30 // ]
#define TK_OPEN_BLOCK      31 // {%
#define TK_CLOSE_BLOCK     32 // %}
#define TK_COMMENT         33 // {##}

// Special  
#define TK_ERROR       -1
#define TK_EOF         0

// New tokens
#define TK_OPEN_PAREN   36  // 
#define TK_CLOSE_PAREN  37  // 
#define TK_PROGRAMA     38  // 

#endif // TOKENS_H 