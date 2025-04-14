#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

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

  // Indenta a árvore conforme a profundidade
  for (int i = 0; i < depth; i++) {
    printf("  "); // Imprime espaços para o nível de profundidade
  }

  // Imprime o valor do nó
  printf("%d\n", node->data.value);

  // Chama recursivamente para o primeiro filho
  tree_print(node->first_child, depth + 1);

  // Chama recursivamente para os irmãos
  tree_print(node->next_sibling, depth);
}


