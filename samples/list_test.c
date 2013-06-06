#include "../src/misc/list.h"


#include <unistd.h>
#include <stdio.h>

int main() {

   while (true) {
      list* lst = new_list();

      for (int i = 0; i < 100000; i++) {
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
