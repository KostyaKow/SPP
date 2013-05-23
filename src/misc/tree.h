#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdlib.h>
#include "types.h"

struct tree {
   tree_t** child;
   void* data;
   int num_child;
   int size;
} tree_t;

tree_t* new_tree(tree_t* tree);
bool_t tree_add(tree_t* tree, void* data);

#endif // TREE_H_INCLUDED
