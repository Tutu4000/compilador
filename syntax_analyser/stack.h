#ifndef STACK_H
#define STACK_H

#include <stdbool.h> // para usar bool

// Definição do tipo de elemento (um par int, bool)
typedef struct {
  int value;
  bool flag;
} StackElement;

// Nó da pilha
typedef struct StackNode {
  StackElement data;
  struct StackNode *next;
} StackNode;

// Estrutura da pilha
typedef struct {
  StackNode *top;
  int size;
} Stack;

// Funções da pilha
void stack_init(Stack *stack);
bool stack_is_empty(Stack *stack);
void stack_push(Stack *stack, int value, bool flag);
bool stack_pop(Stack *stack, StackElement *out);
bool stack_peek(Stack *stack, StackElement *out);
void stack_free(Stack *stack);

#endif // STACK_H
