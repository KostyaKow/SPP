#include <stdlib.h>
#include <stdio.h>

//TODO: check if the struct in the looop really nessasary? (I am writing this at 11:20 PM...)
#define _LIST_FOR_EACH(lst, elem, type) \
   for (struct { type* elem; int i; } _LIST = {(type*)lst->data[0], 0}; _LIST.i < lst->num_elem; _LIST.i++, _LIST.elem = (type*)lst->data[_LIST.i])

#define _LIST_FOR_EACH_VOID(lst, elem) \
   _LIST_FOR_EACH(lst, elem, void)
//for (struct { void* elem; int i; } _LIST = {0, lst->data[0]}; _LIST.i < lst->num_elem; _LIST.i++, _LIST.elem = lst->data[_LIST.i])

typedef struct list {
   int num_elem, size;
   void** data;
} list;

inline void* list_get(list* lst, int elem) {
   return lst->data[elem];
}


inline list* new_list() {
   list* lst = (list*)malloc(sizeof(list));
   lst->num_elem = 0;
   lst->size = 3;
   lst->data = (void**)malloc(3 * sizeof(void*));
   return lst;
}

inline void list_push(list* lst, void* elem) {
   if (lst->num_elem >= lst->size) {
      lst->size *= 2;
      lst->data = (void**)realloc(lst->data, lst->size * sizeof(void*));
   }
   lst->data[lst->num_elem++] = elem;
}

inline void list_push_array(list* lst, void** arr, int num_elem) {
   if (lst->num_elem + num_elem >= lst->size) {
      lst->size = num_elem + lst->size * 2;
      lst->data = (void**)realloc(lst->data, lst->size * sizeof(void*));
   }
   for (int i = 0; i < num_elem; i++, lst->num_elem++)
      lst->data[lst->num_elem] = arr[i];
}

inline void list_shrink_to_fit(list* lst) {
   if (lst->num_elem > lst->size) {
      lst->size = lst->num_elem;
      lst = (list*)realloc(lst->data, lst->size);
   }
}

inline void* list_pop(list* lst) {
   void* ret = lst->data[lst->num_elem--];
   list_shrink_to_fit(lst);
   return ret;
}

inline void** list_pop_num(list* lst, int num) {
    void** ret = (void**)malloc(num * sizeof(void*));

    for (int i = 0; i < num; i++)
        ret[i] = lst->data[lst->num_elem--];

    list_shrink_to_fit(lst);

    return ret;
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

/*
int main() {
   list* lst = new_list();

   for (int i = 0; i < 10; i++) {
      list_push(lst, (void*)"hello");
   }

   _LIST_FOR_EACH(lst, elem, int) {
      printf("\ncurrent:%s", *((void**)(&_LIST)));//*_LIST.elem);//*((&_LIST)+0));
   }
}
*/
