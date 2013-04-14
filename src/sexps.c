#include "sexps.h"
#include "misc/types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int* _get_next_quotes(const char* str, int i) {
   size_t len = strlen(str);
   
   int* to_return = (int*)malloc(sizeof(uint) * 2);
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

//I tried to optimize this, but ended up wasting at least 5 hours...
int _increment_counter(const char* str, int i, bool_ init) {
   int* quotes; //TODO: free this...
 
   int to_add = 1;
   if (init)
      to_add = 0;
  
   quotes = _get_next_quotes(str, i);
   
   if (quotes[0] == quotes[1])
      return i + to_add; 
 
   if (i >= (quotes[0] - to_add) && i <= quotes[1])
      return quotes[1] + 1;
   else
      return i + to_add; 
}

struct Sexps* parse_sexps(const char* sexps) {
   int len = strlen(sexps);

   _bool found_paren = _false;
    
   int i; 
   for (i = _increment_counter(sexps, 0, _true);
        i < len;
        _increment_counter(sexps, i, _false))
   {
      if (sexps[i] == '(')
   }

}


