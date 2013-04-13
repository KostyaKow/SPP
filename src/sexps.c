#include "sexps.h"
#include "misc/types.h"

#include <string.h>
#include <stdlib.h>

int* _get_next_quotes(char* str, int i) {
   int len = strlen(str);
   
   int* to_return = (int*)malloc(sizeof(int) * 2);
   to_return[0] = to_return[1] = -1;

   if (len <= i)
      return to_return;
   
   _bool have_1st_quote = _false;
   while (i < len) {
      if (str[i] == '"') {
         if (!have_1st_quote) {
            to_return[0] = i;
            have_1st_quote = _true;
         }

         else {
            to_return[1] = i;
            break;  
         }
      }
      i++;
   }

   return to_return;
}

struct Sexps* parse_sexps(const char* sexps) {
   int len = strlen(sexps);
 
   int i = 0; 
   while (i < len || sexps[i] != ')') {
   
   }

}
