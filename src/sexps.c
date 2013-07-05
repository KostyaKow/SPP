#include "sexps.h"


int* _get_next_quotes(const char* str, size_t len, int i) {
   len = (len == 0) ? strlen(str) : len;

   int* to_return = (int*)malloc(sizeof(int) * 2);
   to_return[0] = to_return[1] = -1;

   if (len <= i)
      return to_return;

   bool have_1st_quote = false;
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

//TODO: optimize so it will call get_next_quotes only when needed!
int _increment_counter(const char* str, size_t len, int i, bool init) {
   len = (len == 0) ? strlen(str) : len;

   int* quotes;

   int to_add = 1;
   if (init)
      to_add = 0;

   quotes = _get_next_quotes(str, len, i);

   if (quotes[0] == quotes[1]) {
      free(quotes);
      return i + to_add; ///TODO: return length?
   }

   if (i >= (quotes[0] - to_add) && i <= quotes[1]) {
      i = quotes[1] + 1;
      free(quotes);
      return i;
   }
   free(quotes);
   return i + to_add;
}

bool parse_type(struct Sexps* s) { //TODO: work on this!
   if (!s->str_val || !s->str_val_len)
      return false;

   if (isDigit(s->str_val[0]))
      s->atom = true;
   else s->atom = false;

   return true;
}

struct Sexps* parse_sexps(const char* sexps, size_t len) {
   len = (len == 0) ? strlen(sexps) : len;

   printf("parsing: %s", str_cpy(sexps, len));

   int begin_paren, end_paren, num_open_paren, num_closed_paren;
   int begin_parens[100]; //100 levels of nestedness should be enough
   begin_paren = end_paren = num_open_paren = -1; num_closed_paren = -1;

   struct Sexps* to_ret = (struct Sexps*)malloc(sizeof(struct Sexps));
   to_ret->str_val = sexps; to_ret->str_val_len = len;
   to_ret->sub_sexps = NULL;
   to_ret->sub_sexps_len = to_ret->size_sub_sexps = to_ret->single_sexps = 0;
   if (!parse_type(to_ret)) {
      free(to_ret);
      error("could not deduce the type of sexps", BAD_INPUT);
      return NULL;
   }

   if (to_ret->atom)
      return to_ret;

   int i = 0;
   while (i < len) {
      BUG_PRINT("while loop!");
      bool found_begin = false;
      end_paren = -1; begin_parens[num_open_paren] = 0;
      for (i = _increment_counter(sexps, len, i, true);
           i < len;
           i = _increment_counter(sexps, len, i, false))
      {
         BUG_PRINT("Inside for loop..i: %i", i);
         if (sexps[i] == '(') {
            begin_parens[++num_open_paren] = i;
            found_begin = true;
         }

         else if (sexps[i] == ')') { //need to decrease the num_open_paren somewhere...
            BUG_PRINT("else");
            if (num_open_paren == -1) {
               error("found close parenthesis with no open parenthesis", BAD_PAREN);
               return NULL;
            }
            num_closed_paren++;
            end_paren = i;
            break;
         }
      }
      BUG_PRINT("---!!!!---%i%i", num_open_paren, begin_parens[num_open_paren]);
      //should check that num_open_paren is 1 (begin paren. then ignore, since it is our main one, and not sub_sexps
      if (!found_begin || end_paren == -1 || begin_parens[num_open_paren] == 0) { //!begin_parens[num_open_paren-1])
        BUG_PRINT("****"); i++;
        continue;
      }

      BUG_PRINT("This expression has sub_sexps!");

      if (to_ret->sub_sexps == NULL) { //allocate
         to_ret->sub_sexps = (struct Sexps**)malloc(sizeof(struct Sexps**));
         to_ret->sub_sexps_len = to_ret->size_sub_sexps = 1;
      }
      BUG_PRINT("allocated sub_sexps pointer pointers");
      //TODO: change to a nice container implementation (tree).
      /*
      if (to_ret->sub_sexps_len + 1 == to_ret->size_sub_sexps)
         to_ret->sub_sexps =
            (struct Sexps**)realloc(to_ret->sub_sexps, sizeof(struct Sexps**) * (to_ret->size_sub_sexps *= 2));
      */
      if (to_ret->sub_sexps_len + 1 >= to_ret->size_sub_sexps) {
         to_ret->size_sub_sexps *= 2;
         to_ret->sub_sexps = (struct Sexps**)realloc(to_ret->sub_sexps, sizeof(struct Sexps**) * to_ret->size_sub_sexps);
      }
      BUG_PRINT("reallocated sub_sexps pointers");

      printf("%i", begin_parens[num_open_paren]);
      BUG_PRINT("k- begin_parens[num_open_paren]: %i \nend_paren: %i", begin_parens[num_open_paren], end_paren);
      printf("got here");
      BUG("new sub_sexps: %s", str_cpy(
                                       &sexps[begin_parens[num_open_paren]],
                                       end_paren - begin_parens[num_open_paren]));
      assert(begin_paren >= 0 && end_paren > begin_paren && end_paren >= 0);
      to_ret->sub_sexps[(to_ret->sub_sexps_len++) - 1] = parse_sexps(sexps + sizeof(char) * begin_paren, end_paren - begin_parens[num_open_paren] + 1);
      num_closed_paren--; num_open_paren--;
   }
   return to_ret;
}





