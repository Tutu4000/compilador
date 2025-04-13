#ifndef TREE_H
#define TREE_H

#include "stack.h" // para StackElement

// Nó da árvore genérica
typedef struct TreeNode {
  StackElement data;
  struct TreeNode *first_child;  // ponteiro para o primeiro filho
  struct TreeNode *next_sibling; // ponteiro para o próximo irmão
  struct TreeNode *parent;       // ponteiro para o nó pai
} TreeNode;

// Funções
TreeNode *tree_create_node(int value, bool flag);
void tree_add_child(TreeNode *parent, TreeNode *child);
void tree_traverse(TreeNode *root); // exibe em profundidade
void tree_free(TreeNode *root);
void tree_print(TreeNode *root, int level);

#endif // TREE_H

