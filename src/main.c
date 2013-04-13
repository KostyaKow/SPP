#include "config.h"

#include "sexps.h"
#include "misc/types.h"
#include "misc/misc.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
   while (_true) {
      printf("\nenter stuff: ");

      char* str = (char*)malloc(sizeof(char)*100);
      gets(str); //scanf("%s", str);
      
      BUG
      
      int* n = _get_next_quotes(str, 0); 

      printf("\n\n******\nnumbers: %i  %i\n********\n\n\n", n[0], n[1]);
   }
}
