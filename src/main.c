#include "config.h"

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

void printcnf(char c, int n, const char* str) { //print character c n times, before printing str
   while (n > 0) {
      printf("%c", c);
      n--;
   }
   printf("%s", str);
}

void _print_sexps(struct Sexps* sexps, int nesting_level) {
   BUG_("calling _print_sexps");
   if (sexps == NULL)
      error("Null pointer passed to _print_sexps", NULL_PTR );
   
   char str[100]; //for output
   
   sprintf(str, "\nnumber of sexps: %i; size for array: %i", sexps->sub_sexps_len, sexps->size_sub_sexps); 
   printcnf('\t', nesting_level, str);
   
   if (sexps->atom) {
      printcnf('\t', nesting_level, "atom of type ");
      switch (sexps->type) {
         case SEXPS_INT:
           printf("int with value: %i", *(int*)sexps->val); 
         break;
         case SEXPS_FLOAT:
            printf("float with value: %F", *(float*)sexps->val);
         break;
         case SEXPS_CHAR:
            printf("char with value: %c", *(char*)sexps->val);
         break;
      }
      char str[5]; sprintf(str, "\nstr_len: %i", sexps->str_val_len);
      printcnf('\t', nesting_level, str);
   }
   else {
      int i;
      for (i = 0; i < sexps->sub_sexps_len; i++)
         _print_sexps(sexps->sub_sexps[i], nesting_level + 1);
     
      printcnf('\t', nesting_level, "\nsexps: ");
      printf("%s", sexps->str_val);
   }
}

void print_sexps(struct Sexps* sexps) {
   _print_sexps(sexps, 0);
}

int main(void) {
   while (true) {
      printf("\n\n\n\nenter stuff: ");

      char str[100]; 
      gets(str); //scanf("%s", str);
      
      print_sexps(parse_sexps(str, 0)); 
   }
      /* 
      int* n = _get_next_quotes(str, 0, 0); 

      //printf("\n********\nnumbers: %i  %i\n********\n", n[0], n[1]);


      int i;
      for (i = _increment_counter(str, 0, 0, true);
           i < strlen(str);
           i = _increment_counter(str, 0, i, false))
      {
         //printf("%c", str[i]);
      }

   }
   */

   return 0;
}

