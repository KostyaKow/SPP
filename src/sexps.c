#include "config.h"
#include "sexps.h"
#include "misc/types.h"
#include "misc/misc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free(void* ptr) {
   ptr = realloc(ptr, 0); //"ptr = " to shut up gcc
}

void error(const char* str, enum error_type how_bad) {
   printf("error occured: %s\nexiting...", str);
   exit(-1);
}


int* _get_next_quotes(const char* str, size_t len, int i) {
   BUG_("_get_next_quotes called");
   len = (len == 0) ? strlen(str) : len;
    
   int* to_return = (int*)malloc(sizeof(int) * 2);
   to_return[0] = to_return[1] = -1;

   if (len <= i)
      return to_return;
   
   bool_t have_1st_quote = false;
   while (i < len) {
      if (str[i] == '"') {
         if (!have_1st_quote) {
            to_return[0] = i;
            have_1st_quote = true;
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

//TODO: optimize
int _increment_counter(const char* str, size_t len, int i, bool_t init) {
   BUG_("_increment counter called"); 
   len = (len == 0) ? strlen(str) : len;

   int* quotes;
 
   int to_add = 1;
   if (init)
      to_add = 0;
  
   quotes = _get_next_quotes(str, len, i);
   
   if (quotes[0] == quotes[1]) {
      free(quotes);
      return i + to_add; 
   }
    
   if (i >= (quotes[0] - to_add) && i <= quotes[1]) {
      i = quotes[1] + 1;
      free(quotes);
      return i;
   }
   free(quotes);
   return i + to_add; 
}

bool_t parse_type(struct Sexps* s) {
   return true;
}


struct Sexps* parse_sexps(const char* sexps, size_t len) {
   len = (len == 0) ? strlen(sexps) : len; 
   BUG_("parse_sexps called");
   
   int begin_paren, end_paren, num_open_paren, num_closed_paren;
   begin_paren = end_paren = -1;
   num_open_paren = num_closed_paren = 0;
  
   struct Sexps* to_ret = (struct Sexps*)malloc(sizeof(struct Sexps)); 
   to_ret->str_val = sexps; to_ret->str_val_len = len;
   to_ret->atom = 0;
   if (!parse_type(to_ret)) {
      free(to_ret);
      error("could not deduce the type of sexps", BAD_INPUT);
      return NULL;
   }
   to_ret->sub_sexps = NULL;
   to_ret->sub_sexps_len = to_ret->size_sub_sexps = 0;
   
   if (to_ret->atom)
      return to_ret;
  
   int counter = 0; 
   while (counter < len) {
      BUG("beginning of while loop");
      int i; 
      for (i = _increment_counter(sexps, len, i, true);
           i < len;
           _increment_counter(sexps, len, i, false))
      {
         if (sexps[i] == '(') {
            if (num_open_paren == 0)
               begin_paren = i;
           num_open_paren++;
         }

         if (sexps[i] == ')') {
            if (num_open_paren == 0) {
               error("found close parenthesis without matching open parenthesis", BAD_PAREN);
               return NULL;
            }
            num_closed_paren++;
            
            if (num_closed_paren == num_open_paren) {
               end_paren = i;
               break;
            }
         }
      }
      counter = i;
      
      if (begin_paren == -1 || end_paren == -1)
        continue;
   
      BUG("Got here (only for sexps with sub_sexps)");
      
      if (to_ret->sub_sexps == NULL) {
         to_ret->sub_sexps = (struct Sexps**)malloc(sizeof(struct Sexps**));
         to_ret->sub_sexps_len = to_ret->size_sub_sexps = 1;
      }
      
      //TODO: change to a nice container implementation (tree). 
      if (to_ret->sub_sexps_len + 1 == to_ret->size_sub_sexps)
         to_ret->sub_sexps =
            (struct Sexps**)realloc(to_ret, sizeof(struct Sexps**) * (to_ret->size_sub_sexps *= 2)); 
      
      to_ret->sub_sexps[to_ret->sub_sexps_len++] = parse_sexps(sexps + begin_paren, begin_paren - end_paren);

   }
   return to_ret;
}




