#include "sexps.h"
#include "misc/types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


//this code looks a bit weird, because it is optimized to not call _get_next_quotes, until it is needed.
//this will probably not work in parallel
int _increment_counter(const char* str, int i) {
   static _bool first_run = _true;
   static uint* quotes; //TODO: free this...
   static const char* _str = NULL;
  
   
   if (_str != str) { //we are doing a new string...
       first_run = _true; 
       _str = str;
   } 

   int num_to_add = 1; //if called during initialization (as opposed to updating)
   if (i == 0 && first_run)
      num_to_add = 0;

   if (first_run || !(i <= quotes[1])) { //I think this shaves off a few cycles :p 
      quotes = _get_next_quotes(str, i);
      first_run = _false;
   }
   
   if (quotes[0] == quotes[1]) //no quotes found. both of them should be 0. (assert?)
      return i + num_to_add; 
 
   if (quotes[0] == 0)
      return quotes[1] + 1;
    
   if (i >= (quotes[0] - 1) && i <= quotes[1])
      return quotes[1] + 1;
   else
      return i + num_to_add; 

}

struct Sexps* parse_sexps(const char* sexps) {
   int len = strlen(sexps);
 
   int i = 0; 
   for (i = 0; i < len || sexps[i] != ')'; _increment_counter(sexps, i)) {
   
   }

}


