#include "../lexer/lexer.h"
#include "stack.h"
#include "table.h"
#include "tree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void process_production(Stack *s, TreeNode *tree, int production, int prox_token);
int map_lexer_token_to_table_token(int lexer_token);

int main(int argc, char *argv[]) {
  (void)argc;
  
  FILE *input = fopen(argv[1], "r");
  if (!input) {
    printf("Could not open file %s\n", argv[1]);
    return 1;
  }
  init_lexer(input);

  Token prox_token;
  int current_token = 0;
  int value_prox_token = 0;
  
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  StackElement *X = (StackElement *)malloc(sizeof(StackElement));
  StackElement *element = (StackElement *)malloc(sizeof(StackElement));

  TreeNode *tree = tree_create_node(ESTADO_INICIAL, false);

  stack_init(stack);
  stack_push(stack, ESTADO_INICIAL, false);
  
  prox_token = get_token();
  while (!stack_is_empty(stack)) {
    stack_peek(stack,X);
    current_token = map_lexer_token_to_table_token(prox_token.token);

    printf("X->value=%d\tX->flag=%d\tprox->token=%d\n", X->value, X->flag, current_token);

    if (X->flag) {
      if (X->value == current_token) {
        stack_pop(stack, element);
        prox_token = get_token();
        value_prox_token = map_lexer_token_to_table_token(prox_token.token);
        if (tree->next_sibling != NULL) {
          tree = tree->next_sibling;
        } else {
          while (tree->parent != NULL) {
            if (tree->next_sibling != NULL) {
              tree = tree->next_sibling;
              break;
            }
            tree = tree->parent;
          }
        }
      } else {
        fprintf(stderr, "ERRO DESEMPILHA\n");
        return 1;
      }
    } else {
      if (TABELA[X->value][value_prox_token] == 0) {
        fprintf(stderr, "ERRO TABELA! %d,%d,%d\n",X->value,value_prox_token,X->flag);
        return 1;
      } else {
        stack_pop(stack, element);
        process_production(stack, tree, TABELA[X->value][value_prox_token], value_prox_token);
      }
    }
  }
  while (tree->parent != NULL) {
    tree = tree->parent;
  }
  tree_print(tree, 1);
  return 0;
}

void process_production(Stack *s, TreeNode *tree, int production, int prox_token) {
  int insertions = 0;
  int stack_initial_size = s->size;
  StackElement *element = (StackElement*)malloc(sizeof(StackElement));
  printf("PRODUCTION=%d\n", production);
  switch (production) {
  case 1:
    stack_push(s, ESTADO_BLOCO, false);
    stack_push(s, CLOSE_PAREN, true);
    stack_push(s, OPEN_PAREN, true);
    stack_push(s, ESTADO_NOME_PROGRAMA, false);
    stack_push(s, PROGRAMA, true);
    break;
  case 2:
    stack_push(s, ID, true);
    break;
  case 3:
    stack_push(s, CLOSE_PERCENT_CURLY, true);
    stack_push(s, ESTADO_COMANDOS, false);
    stack_push(s, ESTADO_DECLARACOES, false);
    stack_push(s, OPEN_CURLY_PERCENT, true);
    break;
  case 4:
    stack_push(s, ESTADO_DECLARACOES, false);
    stack_push(s, COMMA, true);
    stack_push(s, ESTADO_LISTA_IDS, false);
    stack_push(s, COLON, true);
    stack_push(s, ESTADO_PRIMITIVO, false);
    break;
  case 5:
    break;
  case 6:
    stack_push(s, ESTADO_LISTA_IDS_LINHA, false);
    stack_push(s, ID, true);
    break;
  case 7:
    stack_push(s, ESTADO_LISTA_IDS, false);
    stack_push(s, COMMA, true);
    break;
  case 8:
    stack_pop(s, element);
    stack_push(s, SEMICOLON, true);
    break;
  case 9:
    stack_push(s, CHAR, true);
    break;
  case 10:
    stack_push(s, INT, true);
    break;
  case 11:
    stack_push(s, FLOAT, true);
    break;
  case 12:
    stack_push(s, ESTADO_COMANDOS_LINHA, false);
    stack_push(s, ESTADO_COMANDO, false);
    break;
  case 13:
    stack_push(s, ESTADO_COMANDOS_LINHA, false);
    stack_push(s, ESTADO_COMANDO, false);
    break;
  case 14:
    break;
  case 15:
    stack_push(s, ESTADO_COMANDO_LINHA, false);
    stack_push(s, ESTADO_COMANDO, false);
    stack_push(s, THEN, true);
    stack_push(s, CLOSE_BRACKET, true);
    stack_push(s, ESTADO_CONDICAO, false);
    stack_push(s, OPEN_BRACKET, true);
    stack_push(s, IF, true);
    break;
  case 16:
    stack_push(s, ESTADO_COMANDO, false);
    stack_push(s, DO, true);
    stack_push(s, CLOSE_BRACKET, true);
    stack_push(s, ESTADO_CONDICAO, false);
    stack_push(s, OPEN_BRACKET, true);
    stack_push(s, WHILE, true);
    break;
  case 17:
    stack_push(s, SEMICOLON, true);
    stack_push(s, CLOSE_BRACKET, true);
    stack_push(s, ESTADO_CONDICAO, false);
    stack_push(s, OPEN_BRACKET, true);
    stack_push(s, WHILE, true);
    stack_push(s, ESTADO_COMANDO, false);
    stack_push(s, DO, true);
    break;
  case 18:
    stack_push(s, SEMICOLON, true);
    stack_push(s, ESTADO_EXPRESSAO, false);
    stack_push(s, ASSIGN, true);
    stack_push(s, ID, true);
    break;
  case 19:
    stack_push(s, ESTADO_BLOCO, false);
    break;
  case 20:
    stack_push(s, ESTADO_COMANDO, false);
    stack_push(s, ELSE, true);
    break;
  case 21:
    stack_push(s, ESTADO_ELSEIFS, false);
    break;
  case 22:
    break;
  case 23:
    stack_push(s, ESTADO_ELSEIFS_LINHA, false);
    stack_push(s, ESTADO_COMANDO, false);
    stack_push(s, THEN, true);
    stack_push(s, CLOSE_BRACKET, true);
    stack_push(s, ESTADO_CONDICAO, false);
    stack_push(s, OPEN_BRACKET, true);
    stack_push(s, ELSEIF, true);
    break;
  case 24:
    stack_push(s, ESTADO_COMANDO, false);
    stack_push(s, ELSE, true);
    break;
  case 25:
    stack_push(s, ESTADO_ELSEIFS, false);
    break;
  case 26:
    break;
  case 27:
    stack_push(s, ESTADO_EXPRESSAO, false);
    stack_push(s, RELOP, true);
    stack_push(s, ESTADO_EXPRESSAO, false);
    break;
  case 28:
    stack_push(s, ESTADO_EXPRESSAO_LINHA, false);
    stack_push(s, ESTADO_TERMO, false);
    break;
  case 29:
    stack_push(s, ESTADO_EXPRESSAO_LINHA, false);
    stack_push(s, ESTADO_TERMO, false);
    stack_push(s, ARITOP_ADD, true);
    break;
  case 30:
    break;
  case 31:
    stack_push(s, ESTADO_TERMO_LINHA, false);
    stack_push(s, ESTADO_POTENCIA, false);
    break;
  case 32:
    stack_push(s, ESTADO_TERMO_LINHA, false);
    stack_push(s, ESTADO_POTENCIA, false);
    stack_push(s, ARITOP_MULT, true);
    break;
  case 33:
    break;
  case 34:
    stack_push(s, ESTADO_POTENCIA_LINHA, false);
    stack_push(s, ESTADO_FATOR, false);
    break;
  case 35:
    stack_push(s, ESTADO_POTENCIA, false);
    stack_push(s, ARITOP_POT, true);
    break;
  case 36:
    break;
  case 37:
    stack_push(s, ESTADO_FATOR, false);
    stack_push(s, ARITOP_ADD, true);
    break;
  case 38:
    stack_push(s, CLOSE_PAREN, true);
    stack_push(s, ESTADO_EXPRESSAO, false);
    stack_push(s, OPEN_PAREN, true);
    break;
  case 39:
    stack_push(s, SEMICOLON, true);
    stack_push(s, ID, true);
    break;
  case 40:
    stack_push(s, CONST_CHAR, true);
    break;
  case 41:
    stack_push(s, CONST_INT, true);
    break;
  case 42:
    stack_push(s, CONST_FLOAT, true);
    break;
  case 43:
  case 44:
  case 45:
    break;
  default:
    fprintf(stderr, "ERRO DESCONHECIDO %d\n", production);
    exit(1);
}

  insertions = s->size - stack_initial_size;
  for (int i = 0; i < insertions; i++) {
    stack_peek(s, element);
    
    TreeNode *child = tree_create_node(element->value, element->flag);
    tree_add_child(tree, child);
  }
  
  tree = tree->first_child;
}

int map_lexer_token_to_table_token(int lexer_token) {
    switch (lexer_token) {
        case TK_ID:
            return ID;
        case TK_OPEN_BLOCK:
            return OPEN_CURLY_PERCENT;
        case TK_CLOSE_BLOCK:
            return CLOSE_PERCENT_CURLY;
        case TK_OPEN_PAREN:
            return OPEN_PAREN;
        case TK_CLOSE_PAREN:
            return CLOSE_PAREN;
        case TK_OPEN_BRACKET:
            return OPEN_BRACKET;
        case TK_CLOSE_BRACKET:
            return CLOSE_BRACKET;
        case TK_IF:
            return IF;
        case TK_THEN:
            return THEN;
        case TK_ELSEIF:
            return ELSEIF;
        case TK_ELSE:
            return ELSE;
        case TK_WHILE:
            return WHILE;
        case TK_DO:
            return DO;
        case TK_ASSIGN:
            return ASSIGN;
        case TK_COLON:
            return COLON;
        case TK_SEMICOLON:
            return SEMICOLON;
        case TK_COMMA:
            return COMMA;
        case TK_CONST_CHAR:
            return CONST_CHAR;
        case TK_CONST_INT:
            return CONST_INT;
        case TK_CONST_FLOAT:
            return CONST_FLOAT;
        case TK_CHAR:
            return CHAR;
        case TK_INT:
            return INT;
        case TK_FLOAT:
            return FLOAT;
        case TK_PROGRAMA:
            return PROGRAMA;


        case TK_SUM:
        case TK_SUB:
            return ARITOP_ADD;
        case TK_MULT:
        case TK_DIV:
            return ARITOP_MULT;
        case TK_POT:
            return ARITOP_POT;
        case TK_EQ:
        case TK_NE:
        case TK_LT:
        case TK_GT:
        case TK_LE:
        case TK_GE:
            return RELOP;

        case TK_EOF:
            return DOLLAR;
        default:

            fprintf(stderr, "Token %d\n", lexer_token);
            return -1;
    }
}