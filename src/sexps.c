#include "sexps.h"
#include "misc/types.h"

#include <string.h>
#include <stdlib.h>



uint* _get_next_quotes(const char* str, int i) {
   size_t len = strlen(str);
   
   uint* to_return = (uint*)malloc(sizeof(uint) * 2);
   to_return[0] = to_return[1] = 0;

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

int increment_counter(const char* str, int i) {
   static _bool first_run = _true;
   static uint* quotes; 
 
    if (first_run || !(i <= quotes[1])) { //I think this shaves off a few cycles :p
       quotes = _get_next_quotes(str, i);
       first_run = _false;
   } 
 
   if (quotes[0] == quotes[1]) //no quotes found. both of them should be 0. (assert?)
      return i + 1;

   //If quote is first character, this is needed (because unsigned). Look at next comparison
   if (quotes[0] == 0) 
      quotes[0] = 1;
  
   if (i >= (quotes[0] - 1) && i <= quotes[1])
      return quotes[1] + 1;
   else
      return i + 1;

}

struct Sexps* parse_sexps(const char* sexps) {
   int len = strlen(sexps);
 
   int i = 0; 
   while (i < len || sexps[i] != ')') {
   
   }

}











