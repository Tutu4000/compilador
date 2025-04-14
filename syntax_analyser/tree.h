#ifndef TREE_H
#define TREE_H

#include "stack.h"

typedef struct TreeNode {
  StackElement data;
  struct TreeNode *first_child;  
  struct TreeNode *next_sibling; 
  struct TreeNode *parent;       
} TreeNode;


TreeNode *tree_create_node(int value, bool flag);
void tree_add_child(TreeNode *parent, TreeNode *child);
void tree_traverse(TreeNode *root); 
void tree_free(TreeNode *root);
void tree_print(TreeNode *root, int level);
const char* print_v(int token, bool is_token);

#endif 

