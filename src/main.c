#include "config.h"

#include "sexps.h"
#include "misc/types.h"
#include "misc/misc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 


int main(void) {
   while (_true) {
      printf("\n\n\n\nenter stuff: ");

      char str[100]; 
      gets(str); //scanf("%s", str);
      
      BUG
      
      int* n = _get_next_quotes(str, 0); 

      printf("\n********\nnumbers: %i  %i\n********\n", n[0], n[1]);

      int i;
      for (i = 0; i < strlen(str); i = increment_counter(str, i)) printf("%i: %c\n", i, str[i]); 
      for (i = 0; i < strlen(str); i = increment_counter(str, i)) printf("%c", str[i]);    
   }
}
