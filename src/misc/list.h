#include <stdlib.h>

//TODO: check if the struct in the looop really nessasary? (I am writing this at 11:20 PM...)
#define _LIST_FOR_EACH(lst, elem, type) \
   for (struct { int i; type* elem; } _LIST = {0, lst->data[0] }; _LIST.i < lst->num_elem; _LIST.i++, _LIST.elem = lst->data[_LIST.i])

#define _LIST_FOR_EACH_VOID(lst, elem) \
   for (struct { int i; void* elem; } _LIST = {0, lst->data[0] }; _LIST.i < lst->num_elem; _LIST.i++, _LIST.elem = lst->data[_LIST.i])

typedef struct list {
   int num_elem, size;
   void** data;
} list;

inline list* new_list() {
   list* lst = (list*)malloc(sizeof(list));
   lst->num_elem = 0;
   lst->size = 3;
   lst->data = malloc(3 * sizeof(void*));
   return lst;
}

inline void delete_list(list* lst) {
   free(lst->data);
   free(lst);
}

//delete all data in the list (TODO: not really recursively? change name?)
inline void delete_list_rec(list* lst) {
   _LIST_FOR_EACH_VOID(lst, elem)
      free(_LIST.elem);
   free(lst->data);
   free(lst);
}

//supplies destructor. assumes the distructor works for all pointers
inline void delete_list_rec_func(list* lst, void(*custom_free)(void*)) {
   _LIST_FOR_EACH_VOID(lst, elem)
      custom_free(_LIST.elem);
   free(lst->data);
   free(lst);
}

inline void list_add(void* elem, list* lst) {
   if (lst->num_elem == lst->size)
      lst->data = realloc(lst->data, (lst->size *= 3) * sizeof(void*));
   lst->data[lst->num_elem++] = elem;
}

inline void* list_pop(list* lst) {
   void* ret = lst->data[lst->num_elem--];
   list_shrink(lst);
   return ret;
}

inline void list_shrink(list* lst) {
   if (lst->num_elem > lst->size)
      lst = realloc(lst->data, lst->size = lst->num_elem);
}

inline void* list_get(list* lst, int elem) {
   return lst->data[i];
}

