#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

#define PROGRAMA 0
#define ID 1
#define OPEN_CURLY_PERCENT 2
#define CLOSE_PERCENT_CURLY 3
#define OPEN_PAREN 4
#define CLOSE_PAREN 5
#define OPEN_BRACKET 6
#define CLOSE_BRACKET 7
#define IF 8
#define THEN 9
#define ELSEIF 10
#define ELSE 11
#define WHILE 12
#define DO 13
#define ASSIGN 14
#define COLON 15
#define SEMICOLON 16
#define COMMA 17
#define ARITOP_ADD 18
#define ARITOP_MULT 19
#define ARITOP_POT 20
#define RELOP 21
#define CONST_CHAR 22
#define CONST_INT 23
#define CONST_FLOAT 24
#define CHAR 25
#define INT 26
#define FLOAT 27
#define SPACE 28
#define TAB 29
#define NEWLINE 30
#define DOLLAR 31


#define ESTADO_INICIAL 0
#define ESTADO_NOME_PROGRAMA 1
#define ESTADO_BLOCO 2
#define ESTADO_DECLARACOES 3
#define ESTADO_LISTA_IDS 4
#define ESTADO_LISTA_IDS_LINHA 5
#define ESTADO_PRIMITIVO 6
#define ESTADO_COMANDOS 7
#define ESTADO_COMANDOS_LINHA 8
#define ESTADO_COMANDO 9
#define ESTADO_COMANDO_LINHA 10
#define ESTADO_ELSEIFS 11
#define ESTADO_ELSEIFS_LINHA 12
#define ESTADO_CONDICAO 13
#define ESTADO_EXPRESSAO 14
#define ESTADO_EXPRESSAO_LINHA 15
#define ESTADO_TERMO 16
#define ESTADO_TERMO_LINHA 17
#define ESTADO_POTENCIA 18
#define ESTADO_POTENCIA_LINHA 19
#define ESTADO_FATOR 20
#define ESTADO_WS 21

#define NUM_ESTADOS 22
#define NUM_SIMBOLOS 32

const char* print_v(int token, bool is_token) {
  if (is_token) {
    switch (token) {
      case ID: return "ID";
      case OPEN_CURLY_PERCENT: return "{%";
      case CLOSE_PERCENT_CURLY: return "%}";
      case OPEN_PAREN: return "(";
      case CLOSE_PAREN: return ")";
      case OPEN_BRACKET: return "[";
      case CLOSE_BRACKET: return "]";
      case IF: return "if";
      case THEN: return "then";
      case ELSEIF: return "elseif";
      case ELSE: return "else";
      case WHILE: return "while";
      case DO: return "do";
      case ASSIGN: return ":=";
      case COLON: return ":";
      case SEMICOLON: return ";";
      case COMMA: return ",";
      case CONST_CHAR: return "const_char";
      case CONST_INT: return "const_int";
      case CONST_FLOAT: return "const_float";
      case CHAR: return "char";
      case INT: return "int";
      case FLOAT: return "float";
      case PROGRAMA: return "programa";
      case ARITOP_ADD: return "soma/sub";
      case ARITOP_MULT: return "mult/div";
      case ARITOP_POT: return "potência";
      case RELOP: return "relop";
      case DOLLAR: return "$";
      default: return "desconhecido";
    }
  } else {
    switch (token) {
      case ESTADO_INICIAL: return "ESTADO_INICIAL";
      case ESTADO_NOME_PROGRAMA: return "ESTADO_NOME_PROGRAMA";
      case ESTADO_BLOCO: return "ESTADO_BLOCO";
      case ESTADO_DECLARACOES: return "ESTADO_DECLARACOES";
      case ESTADO_LISTA_IDS: return "ESTADO_LISTA_IDS";
      case ESTADO_LISTA_IDS_LINHA: return "ESTADO_LISTA_IDS_LINHA";
      case ESTADO_PRIMITIVO: return "ESTADO_PRIMITIVO";
      case ESTADO_COMANDOS: return "ESTADO_COMANDOS";
      case ESTADO_COMANDOS_LINHA: return "ESTADO_COMANDOS_LINHA";
      case ESTADO_COMANDO: return "ESTADO_COMANDO";
      case ESTADO_COMANDO_LINHA: return "ESTADO_COMANDO_LINHA";
      case ESTADO_ELSEIFS: return "ESTADO_ELSEIFS";
      case ESTADO_ELSEIFS_LINHA: return "ESTADO_ELSEIFS_LINHA";
      case ESTADO_CONDICAO: return "ESTADO_CONDICAO";
      case ESTADO_EXPRESSAO: return "ESTADO_EXPRESSAO";
      case ESTADO_EXPRESSAO_LINHA: return "ESTADO_EXPRESSAO_LINHA";
      case ESTADO_TERMO: return "ESTADO_TERMO";
      case ESTADO_TERMO_LINHA: return "ESTADO_TERMO_LINHA";
      case ESTADO_POTENCIA: return "ESTADO_POTENCIA";
      case ESTADO_POTENCIA_LINHA: return "ESTADO_POTENCIA_LINHA";
      case ESTADO_FATOR: return "ESTADO_FATOR";
      case ESTADO_WS: return "ESTADO_WS";
      default: return "desconhecido";
    }
  }
}

TreeNode *tree_create_node(int value, bool flag) {
  TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
  if (!node) {
    fprintf(stderr, "Erro de alocação para nó da árvore.\n");
    exit(EXIT_FAILURE);
  }
  node->data.value = value;
  node->data.flag = flag;
  node->first_child = NULL;
  node->next_sibling = NULL;
  node->parent = NULL; 
  return node;
}

void tree_add_child(TreeNode *parent, TreeNode *child) {
  if (!parent || !child)
    return;

  child->parent = parent;


  if (parent->first_child == NULL) {
    parent->first_child = child;
  } else {
    TreeNode *current = parent->first_child;
    while (current->next_sibling != NULL) {
      current = current->next_sibling;
    }
    current->next_sibling = child;
  }
}

void tree_traverse(TreeNode *root) {
  if (root == NULL)
    return;

  printf("Valor: %d, Flag: %s\n", root->data.value,
         root->data.flag ? "true" : "false");

  TreeNode *child = root->first_child;
  while (child != NULL) {
    tree_traverse(child);
    child = child->next_sibling;
  }
}

void tree_free(TreeNode *root) {
  if (root == NULL)
    return;

  TreeNode *child = root->first_child;
  while (child != NULL) {
    TreeNode *next = child->next_sibling;
    tree_free(child);
    child = next;
  }

  free(root);
}

void tree_print(TreeNode *node, int depth) {
  if (node == NULL) {
    return;
  }

   if (depth > 0) {
    for (int i = 0; i < depth - 1; i++) {
      printf("│   ");
    }
    printf("├── ");
  }

  printf("%s\n", print_v(node->data.value, node->data.flag));


  tree_print(node->first_child, depth + 1);


  tree_print(node->next_sibling, depth);
}


