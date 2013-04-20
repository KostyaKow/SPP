#include "misc/config.h"

#include "sexps.h"
#include "misc/types.h"
#include "misc/misc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

void get_some() {
   char* n = (char*)malloc(100*sizeof(char));
   gets(n);
   n = (char*)realloc(n, 0);
}

int main(void) {
 
   while (_true) {
      printf("\n\n\n\nenter stuff: ");

      char str[100]; 
      gets(str); //scanf("%s", str);
      
      BUG
      
      int* n = _get_next_quotes(str, 0, 0); 

      printf("\n********\nnumbers: %i  %i\n********\n", n[0], n[1]);

      int i;
      for (i = _increment_counter(str, 0, 0, _true);
           i < strlen(str);
           i = _increment_counter(str, 0, i, _false))
      {
         printf("%i: %c\n", i, str[i]);
      }
      

      for (i = _increment_counter(str, 0, 0, _true);
           i < strlen(str);
           i = _increment_counter(str, 0, i, _false))
      {
         printf("%c", str[i]);
      }

   }

   return 0;
}



