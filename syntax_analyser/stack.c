#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void stack_init(Stack *stack) { stack->top = NULL; }

bool stack_is_empty(Stack *stack) { return stack->top == NULL; }

void stack_push(Stack *stack, int value, bool flag) {
  StackNode *node = (StackNode *)malloc(sizeof(StackNode));
  if (node == NULL) {
    fprintf(stderr, "Erro de alocação de memória\n");
    exit(EXIT_FAILURE);
  }
  node->data.value = value;
  node->data.flag = flag;
  node->next = stack->top;
  stack->top = node;
  stack->size = stack->size + 1;
}

bool stack_pop(Stack *stack, StackElement *out) {
  if (stack_is_empty(stack)) {
    return false;
  }
  StackNode *temp = stack->top;
  *out = temp->data;
  stack->top = temp->next;
  stack->size = stack->size - 1;
  free(temp);
  return true;
}

bool stack_peek(Stack *stack, StackElement *out) {
  if (stack_is_empty(stack)) {
    return false;
  }
  out = &stack->top->data;
  return true;
}

void stack_free(Stack *stack) {
  StackElement temp;
  while (stack_pop(stack, &temp)) {
    // apenas esvaziando
  }
}
