#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//TODO: check if the struct in the looop really nessasary? (I am writing this at 11:20 PM...)
#define _LIST_FOR_EACH(lst, elem, type) \
   for (struct { int i; type* elem; } _LIST = {0, lst->data[0] }; _LIST.i < lst->num_elem; _LIST.i++, _LIST.elem = lst->data[_LIST.i])

#define _LIST_FOR_EACH_VOID(lst, elem) \
   for (struct { int i; void* elem; } _LIST = {0, lst->data[0] }; _LIST.i < lst->num_elem; _LIST.i++, _LIST.elem = lst->data[_LIST.i])

typedef struct list {
   int num_elem, size;
   void** data;
} list;

list* new_list() {
   list* lst = (list*)malloc(sizeof(list));
   lst->num_elem = 0;
   lst->size = 3;
   lst->data = malloc(3 * sizeof(void*));
   return lst;
}

void delete_list(list* lst) {
   free(lst->data);
   free(lst);
}

//delete all data in the list (TODO: not really recursively? change name?)
void delete_list_rec(list* lst) {
   _LIST_FOR_EACH_VOID(lst, elem)
      free(_LIST.elem);
   free(lst->data);
   free(lst);
}

//supplies destructor. assumes the distructor works for all pointers
void delete_list_rec_func(list* lst, void(*custom_free)(void*)) {
   _LIST_FOR_EACH_VOID(lst, elem)
      custom_free(_LIST.elem);
   free(lst->data);
   free(lst);
}

void list_add(void* elem, list* lst) {
   if (lst->num_elem == lst->size)
      lst->data = realloc(lst->data, (lst->size *= 3) * sizeof(void*));
   lst->data[lst->num_elem++] = elem;
}

void* list_pop(list* lst) {
   void* ret = lst->data[lst->num_elem--];
   list_shrink(lst);
   return ret;
}

void list_shrink(list* lst) {
   if (lst->num_elem > lst->size)
      lst = realloc(lst->data, lst->size = lst->num_elem);
}

void* list_get(list* lst, int elem) {
   return lst->data[i];
}

#define true 1
#define false 0

int main() {
   while (true) {
      list* lst = new_list();

      for (int i = 0; i < 100000; i++) { ///yey....does not seem to leak memory (with htop)
         int* n = malloc(sizeof(int*));
         *n = i;
         list_add(n, lst);
      }
      delete_list_rec(lst);
      sleep(1);
   }

   /*for (char* str = malloc(sizeof(char*) * 100);
        strcmp(str, "exit");
        str = malloc(sizeof(char*) * 100), scanf("%s", str))
      list_add(str, lst);

   //for (int i = 0; i < lst->num_elem; i++)
   //   printf("%s\n", lst->data[i]);
   LIST_FOR_EACH(lst, test, char) {
      printf("%s\n", LIST_.test);

   }*/

   return 0;
}

