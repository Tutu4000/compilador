#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE *input_file = NULL;
static char lexeme[MAX_LEXEME_LENGTH];
static int lexeme_pos = 0;
static int current_char;
static Position current_pos = {1, 1};
static Position token_start_pos = {1, 1};
static Symbol symbol_table[MAX_SYMBOLS];
static int symbol_count = 0;

void init_lexer(FILE *input) {
  input_file = input;
  current_pos.line = 1;
  current_pos.column = 0;
  token_start_pos = current_pos;
  symbol_count = 0;
  lexeme_pos = 0;
  current_char = getc(input_file);
  current_pos.column = 1;
}

static void reset_lexeme() {
  lexeme_pos = 0;
  lexeme[0] = '\0';
}

static void mark_token_start() { token_start_pos = current_pos; }

static void add_to_lexeme(char c) {
  if (lexeme_pos < MAX_LEXEME_LENGTH - 1) {
    lexeme[lexeme_pos++] = c;
    lexeme[lexeme_pos] = '\0';
  }
}

static Token create_token(int token_type) {
  Token token;
  token.token = token_type;
  strcpy(token.lexeme, lexeme);
  token.pos = token_start_pos;
  token.symbol_table_index = -1;
  return token;
}

static int next_char() {
  current_char = getc(input_file);
  if (current_char == '\n') {
    current_pos.line++;
    current_pos.column = 1;
  } else if (current_char == '\t') {
    current_pos.column = (current_pos.column + 4);
  } else if (current_char != EOF) {
    current_pos.column++;
  }

  return current_char;
}

static int is_whitespace() {
  return current_char == ' ' || current_char == '\t' || current_char == '\n' ||
         current_char == '\r' || current_char == '\f' || current_char == '\v';
}

static void skip_whitespace() {
  while (is_whitespace()) {
    next_char();
  }
  mark_token_start();
}

Symbol *lookup_symbol(const char *lexeme) {
  for (int i = 0; i < symbol_count; i++) {
    if (strcmp(symbol_table[i].lexeme, lexeme) == 0) {
      return &symbol_table[i];
    }
  }
  return NULL;
}

Symbol *insert_symbol(const char *lexeme, int type, void *value) {
  if (symbol_count >= MAX_SYMBOLS) {
    printf("Error: Symbol table overflow\n");
    return NULL;
  }

  Symbol *sym = &symbol_table[symbol_count++];
  strcpy(sym->lexeme, lexeme);
  sym->type = type;

  if (value != NULL) {
    switch (type) {
    case TK_CONST_INT:
      sym->value.int_value = *(int *)value;
      break;
    case TK_CONST_FLOAT:
      sym->value.float_value = *(float *)value;
      break;
    case TK_CONST_CHAR:
      sym->value.char_value = *(char *)value;
      break;
    }
  }

  return sym;
}

void print_symbol_table() {
  printf("\nSymbol Table:\n");
  printf("Position\tLexeme\t\tType\t\tValue\n");
  printf("------------------------------------------------\n");
  for (int i = 0; i < symbol_count; i++) {
    printf("%d\t\t%s\t\t", i, symbol_table[i].lexeme);
    switch (symbol_table[i].type) {
    case TK_CONST_INT:
      printf("INT\t\t%d\n", symbol_table[i].value.int_value);
      break;
    case TK_CONST_FLOAT:
      printf("FLOAT\t\t%f\n", symbol_table[i].value.float_value);
      break;
    case TK_CONST_CHAR:
      printf("CHAR\t\t%c\n", symbol_table[i].value.char_value);
      break;
    case TK_ID:
      printf("ID\t\t-\n");
      break;
    }
  }
}

void print_token(Token token) {
  switch (token.token) {
  case TK_PROGRAMA:
  case TK_IF:
  case TK_THEN:
  case TK_ELSE:
  case TK_ELSEIF:
  case TK_WHILE:
  case TK_DO:
  case TK_CHAR:
  case TK_INT:
  case TK_FLOAT:
    printf("<%s, - >", token.lexeme);
    break;

  case TK_CONST_INT:
  case TK_CONST_FLOAT:
  case TK_CONST_CHAR:
  case TK_ID:
    printf("<%s, pos {%d} >",
           token.token == TK_ID            ? "id"
           : token.token == TK_CONST_INT   ? "const_int"
           : token.token == TK_CONST_FLOAT ? "const_float"
                                           : "const_char",
           token.symbol_table_index);
    break;

  case TK_LT:
    printf("<relop, < >");
    break;
  case TK_LE:
    printf("<relop, <= >");
    break;
  case TK_GT:
    printf("<relop, > >");
    break;
  case TK_GE:
    printf("<relop, >= >");
    break;
  case TK_EQ:
    printf("<relop, = >");
    break;
  case TK_NE:
    printf("<relop, <> >");
    break;

  case TK_ASSIGN:
    printf("<:=, - >");
    break;
  case TK_SEMICOLON:
    printf("<;, - >");
    break;
  case TK_COMMA:
    printf("<,, - >");
    break;
  case TK_OPEN_BRACKET:
    printf("<[, - >");
    break;
  case TK_CLOSE_BRACKET:
    printf("<], - >");
    break;
  case TK_COLON:
    printf("<:, - >");
    break;
  case TK_SUM:
    printf("<+, - >");
    break;
  case TK_SUB:
    printf("<-, - >");
    break;
  case TK_MULT:
    printf("<*, - >");
    break;
  case TK_DIV:
    printf("</, - >");
    break;
  case TK_POT:
    printf("<**, - >");
    break;
  case TK_OPEN_BLOCK:
    printf("<{%%, - >");
    break;
  case TK_CLOSE_BLOCK:
    printf("<%%}, - >");
    break;
  case TK_COMMENT:
    printf("<comment, - >");
    break;
  case TK_EOF:
    printf("<EOF, - >");
    break;
  case TK_ERROR:
    printf("<ERROR, - >");
    break;
  case TK_OPEN_PAREN:
    printf("<(, - >");
    break;
  case TK_CLOSE_PAREN:
    printf("<), - >");
    break;
  }
  printf("\n");
}

Token get_token() {
  int state = 0;
  Token token;
  reset_lexeme();

  while (1) {
    switch (state) {
    case 1:
      if (is_whitespace()) {
        skip_whitespace();
      } else {
        mark_token_start();
      }
      state = 2;
      break;

    case 2:
      state = 0;
      break;

    case 0:
      if (current_char == EOF) {
        return create_token(TK_EOF);
      }

      if (is_whitespace()) {
        //add_to_lexeme(current_char);
        state = 1;
        break;
      }

      if (isdigit(current_char)) {
        add_to_lexeme(current_char);
        state = 13;
        current_char = next_char();
      } else if (isalpha(current_char)) {
        add_to_lexeme(current_char);
        state = 3;
        current_char = next_char();
      } else {
        add_to_lexeme(current_char);
        switch (current_char) {
        case '(':
          state = 45;
          current_char = next_char();
          break;
        case ')':
          state = 46;
          current_char = next_char();
          break;
        case '<':
          state = 5;
          current_char = next_char();
          break;
        case '>':
          state = 10;
          current_char = next_char();
          break;
        case '=':
          state = 9;
          current_char = next_char();
          break;
        case '+':
          state = 25;
          current_char = next_char();
          break;
        case '-':
          state = 26;
          current_char = next_char();
          break;
        case '*':
          state = 27;
          current_char = next_char();
          break;
        case '/':
          state = 30;
          current_char = next_char();
          break;
        case '{':
          state = 32;
          current_char = next_char();
          break;
        case ':':
          state = 36;
          current_char = next_char();
          break;
        case ';':
          state = 39;
          current_char = next_char();
          break;
        case ',':
          state = 40;
          current_char = next_char();
          break;
        case '[':
          state = 41;
          current_char = next_char();
          break;
        case ']':
          state = 42;
          current_char = next_char();
          break;
        case '%':
          state = 43;
          current_char = next_char();
          break;
        case '\'':
          state = 22;
          current_char = next_char();
          break;
        default:
          printf("Error at line %d, column %d: Invalid character '%c'\n",
                 current_pos.line, current_pos.column, current_char);
          token = create_token(TK_ERROR);
          current_char = next_char();
          return token;
        }
      }
      break;

    case 3:
      while (isalnum(current_char) || current_char == '_') {
        add_to_lexeme(current_char);
        current_char = next_char();
      }
      state = 4;
      break;

    case 4:
      if (strcmp(lexeme, "programa") == 0)
        return create_token(TK_PROGRAMA);
      if (strcmp(lexeme, "if") == 0)
        return create_token(TK_IF);
      if (strcmp(lexeme, "then") == 0)
        return create_token(TK_THEN);
      if (strcmp(lexeme, "elseif") == 0)
        return create_token(TK_ELSEIF);
      if (strcmp(lexeme, "else") == 0)
        return create_token(TK_ELSE);
      if (strcmp(lexeme, "while") == 0)
        return create_token(TK_WHILE);
      if (strcmp(lexeme, "do") == 0)
        return create_token(TK_DO);
      if (strcmp(lexeme, "char") == 0)
        return create_token(TK_CHAR);
      if (strcmp(lexeme, "int") == 0)
        return create_token(TK_INT);
      if (strcmp(lexeme, "float") == 0)
        return create_token(TK_FLOAT);

      token = create_token(TK_ID);
      Symbol *sym = lookup_symbol(lexeme);
      if (sym == NULL) {
        sym = insert_symbol(lexeme, TK_ID, NULL);
      }
      token.symbol_table_index = sym - symbol_table;
      return token;

    case 5:
      if (current_char == '>') {
        add_to_lexeme(current_char);
        current_char = next_char();
        state = 6;
      } else if (current_char == '=') {
        add_to_lexeme(current_char);
        current_char = next_char();
        state = 7;
      } else {
        state = 8;
      }
      break;

    case 6:
      return create_token(TK_NE);

    case 7:
      return create_token(TK_LE);

    case 8:
      return create_token(TK_LT);

    case 9:
      return create_token(TK_EQ);

    case 10:
      if (current_char == '=') {
        add_to_lexeme(current_char);
        current_char = next_char();
        state = 11;
      } else {
        state = 12;
      }
      break;

    case 11:
      return create_token(TK_GE);

    case 12:
      return create_token(TK_GT);

    case 13:
      while (isdigit(current_char)) {
        add_to_lexeme(current_char);
        current_char = next_char();
      }
      if (current_char == '.') {
        add_to_lexeme(current_char);
        current_char = next_char();
        state = 15;
      } else if (current_char == 'E' || current_char == 'e') {
        add_to_lexeme(current_char);
        current_char = next_char();
        state = 18;
      } else {
        state = 14;
      }
      break;

    case 14:
      token = create_token(TK_CONST_INT);
      token.value.int_value = atoi(lexeme);
      sym = insert_symbol(lexeme, TK_CONST_INT, &token.value.int_value);
      token.symbol_table_index = sym - symbol_table;
      return token;

    case 15:
      if (isdigit(current_char)) {
        add_to_lexeme(current_char);
        current_char = next_char();
        state = 16;
      } else {
        printf("Error at line %d, column %d: Invalid float number format\n",
               current_pos.line, current_pos.column);
        return create_token(TK_ERROR);
      }
      break;

    case 16:
      while (isdigit(current_char)) {
        add_to_lexeme(current_char);
        current_char = next_char();
      }
      if (current_char == 'E' || current_char == 'e') {
        add_to_lexeme(current_char);
        current_char = next_char();
        state = 18;
      } else {
        state = 17;
      }
      break;

    case 17:
      token = create_token(TK_CONST_FLOAT);
      token.value.float_value = atof(lexeme);
      sym = insert_symbol(lexeme, TK_CONST_FLOAT, &token.value.float_value);
      token.symbol_table_index = sym - symbol_table;
      return token;

    case 18:
      if (current_char == '+' || current_char == '-') {
        add_to_lexeme(current_char);
        current_char = next_char();
        state = 19;
      } else if (isdigit(current_char)) {
        add_to_lexeme(current_char);
        current_char = next_char();
        state = 20;
      } else {
        printf("Error at line %d, column %d: Invalid float number format\n",
               current_pos.line, current_pos.column);
        return create_token(TK_ERROR);
      }
      break;

    case 19:
      if (isdigit(current_char)) {
        add_to_lexeme(current_char);
        current_char = next_char();
        state = 20;
      } else {
        printf("Error at line %d, column %d: Invalid float number format\n",
               current_pos.line, current_pos.column);
        return create_token(TK_ERROR);
      }
      break;

    case 20:
      while (isdigit(current_char)) {
        add_to_lexeme(current_char);
        current_char = next_char();
      }
      state = 21;
      break;

    case 21:
      token = create_token(TK_CONST_FLOAT);
      token.value.float_value = atof(lexeme);
      sym = insert_symbol(lexeme, TK_CONST_FLOAT, &token.value.float_value);
      token.symbol_table_index = sym - symbol_table;
      return token;

    case 22:
      if (current_char == EOF || current_char == '\n') {
        printf("Error at line %d, column %d: Unclosed character literal\n",
               current_pos.line, current_pos.column);
        return create_token(TK_ERROR);
      }
      add_to_lexeme(current_char);
      current_char = next_char();
      state = 23;
      break;

    case 23:
      if (current_char == '\'') {
        add_to_lexeme(current_char);
        current_char = next_char();
        state = 24;
      } else {
        printf("Error at line %d, column %d: Expected closing quote for "
               "character literal\n",
               current_pos.line, current_pos.column);
        return create_token(TK_ERROR);
      }
      break;

    case 24:
      token = create_token(TK_CONST_CHAR);
      token.value.char_value = lexeme[1];
      sym = insert_symbol(lexeme, TK_CONST_CHAR, &token.value.char_value);
      token.symbol_table_index = sym - symbol_table;
      return token;

    case 25:
      return create_token(TK_SUM);

    case 26:
      return create_token(TK_SUB);

    case 27:
      if (current_char == '*') {
        state = 28;
        add_to_lexeme(current_char);
        current_char = next_char();
      } else {
        state = 29;
      }
      break;

    case 28:
      return create_token(TK_POT);

    case 29:
      return create_token(TK_MULT);

    case 30:
      return create_token(TK_DIV);

    case 32:
      if (current_char == '%') {
        add_to_lexeme(current_char);
        current_char = next_char();
        return create_token(TK_OPEN_BLOCK);
      } else if (current_char == '#') {
        add_to_lexeme(current_char);
        current_char = next_char();
        state = 33;
      } else {
        printf("Error at line %d, column %d: Expected '%%' or '#' after '{'\n",
               current_pos.line, current_pos.column);
        return create_token(TK_ERROR);
      }
      break;

    case 33:
      while (current_char != '#' && current_char != EOF) {
        add_to_lexeme(current_char);
        current_char = next_char();
      }
      if (current_char == EOF) {
        printf("Error at line %d, column %d: Unclosed comment\n",
               current_pos.line, current_pos.column);
        return create_token(TK_ERROR);
      }
      add_to_lexeme(current_char);
      current_char = next_char();
      if (current_char == '}') {
        add_to_lexeme(current_char);
        current_char = next_char();
        return create_token(TK_COMMENT);
      }
      printf("Error at line %d, column %d: Expected '}' to close comment\n",
             current_pos.line, current_pos.column);
      return create_token(TK_ERROR);

    case 36:
      if (current_char == '=') {
        add_to_lexeme(current_char);
        current_char = next_char();
        state = 37;
      } else {
        state = 38;
      }
      break;

    case 37:
      return create_token(TK_ASSIGN);

    case 38:
      return create_token(TK_COLON);

    case 39:
      return create_token(TK_SEMICOLON);

    case 40:
      return create_token(TK_COMMA);

    case 41:
      return create_token(TK_OPEN_BRACKET);

    case 42:
      return create_token(TK_CLOSE_BRACKET);

    case 43:
      if (current_char == '}') {
        add_to_lexeme(current_char);
        current_char = next_char();
        state = 44;
      } else {
        printf("Error at line %d, column %d: Expected '}' after '%%'\n",
               current_pos.line, current_pos.column);
        return create_token(TK_ERROR);
      }
      break;

    case 44:
      return create_token(TK_CLOSE_BLOCK);

    case 45:
      return create_token(TK_OPEN_PAREN);

    case 46:
      return create_token(TK_CLOSE_PAREN);
    }
  }
}

void close_lexer() {
  if (input_file != NULL) {
    fclose(input_file);
    input_file = NULL;
  }
}
