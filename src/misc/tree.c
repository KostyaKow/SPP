#include "tree.h"

tree_t* new_tree(void) {
   tree = malloc(sizeof(tree));
   tree->num_child = tree->size = 0;
   tree->data = tree->child = NULL;

   return true;
}

bool_t tree_add(tree_t* tree, void* data) {
   if (!tree)
      return false;

   if (!tree->size) {
      tree->size = 1;
      tree->data = malloc(sizeof(void**));
   }

   if (tree->num_elem + 1 > tree->size) {
      tree->size *= 2;
      tree->data = realloc(data, tree->size *= 2); //still exist?

   }

   tree->data[tree->num_elem++] = data;

}
