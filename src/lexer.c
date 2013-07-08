#include "lexer.h"
#include "lookuptable.h"
#include "misc.h"

error_e lex_analyze(source_code_t* src_RETURN, const char *str, int len) {TAB = 1;
   if (len == 0) {
      len = strlen(str);
      BUG_LVL(60, "called with an empty string");
   }
   BUG_LVL(60, "called with a string of length %i", len);

   char *curr_str = str_cpy(str, len);

   //src_RETURN = malloc(sizeof(source_code_t)); //this table is initialized by parent
   INIT_LIST_HEAD(&src_RETURN->lexemes.list); //INIT_LIST_HEAD(&lookup_table.src.lexemes.list);
   src_RETURN->str = curr_str;
   src_RETURN->len = len;

   BUG_LVL(25, "");TAB = 3;
   for (char *c = curr_str; likely(c != curr_str+len && *c != '\0'); c += 1) {
      lexeme_t *lexeme = malloc(sizeof(lexeme_t));
      list_add(&lexeme->list, &src_RETURN->lexemes.list);
      lexeme->value = c;

      if (isParen(*c)) {
         lexeme->type = PAREN;
         lexeme->len = 1;

         BUG_PRINT_LVL(25, "parengthesis");
         continue;
      }

      else if (isDigit(*c)) {
         lexeme->type = NUM;
         c--; int i = 1;

         for (; c+i < curr_str+len &&
                (isDigit(c[i]) || c[i] == '.' || c[i] == ',' || c[i] == '/')
              ; i++) ;

         c += (lexeme->len = i);
         BUG_PRINT_LVL(25, "found number: ");
         BUG_PRINTN_LVL(25, lexeme->value, lexeme->len);
         continue;
      }

      else if (isSpecial(*c)) { //ugly. gotta make my own regex
         //if (c is ') and  (or (c+c1+c2 = 'char' where char != ' and char != \) ex: 'a'
         //                     (c+c1+c2+c3 = '\char')                           ex: '\\'
         //                     (c+c1 = '')
         if (*c == '\'') {
            if (c+2 < curr_str+len && c[2] == '\'' && c[1] != '\'' && c[1] != '\\')
               c += (lexeme->len = 3)-1;
            else if (c+3 < curr_str+len && c[3] == '\'' && c[1] == '\\')
               c += (lexeme->len = 4)-1;
            else if (c+1 < curr_str+len && c[1] == '\'')
               c += (lexeme->len = 2)-1;
            else //first is quote; but then different
               goto place;

            lexeme->type = CHAR;
            BUG_PRINT_LVL(25, "character");
            continue;
         }
         if (*c == '`') {
place:;
            lexeme->type = PAREN;
            c--; int i = 1;
            for (; c+i < curr_str+len && (c[i] == '`' || c[i] == '\''); i++) ;
            if (c+i < curr_str+len && !isParen(c[i]))
               return ERROR_QUOTES_WITHOUT_PARENTHESIS;
            c += (lexeme->len = i);

            BUG_PRINT_LVL(25, "open parenthesis with quotes; %i characters", lexeme->len);
            continue;
         }

         if (*c == '"') {
            lexeme->type = STR;
            c--; int i = 2;

            bool found_second = false;

            for (; c+i < curr_str+len && c[i] != '\0'; i++) {
               if (c[i] == '"') {
                  if (i > 1 && c[i-1] == '\\') ; //escaped double qoute; continue
                  else {
                     found_second = true;
                     break;
                  }
               }
            }

            if (!found_second)
               return ERROR_SINGLE_DOUBLE_QUOTE;

            c += (lexeme->len = i);

            BUG_PRINT_LVL(25, "quoted string of %i found: ", lexeme->len);
            BUG_PRINTN_LVL(25, lexeme->value, lexeme->len);
         }
      }

      else if (isPossibleFuncStart(*c)) {
         lexeme->type = IDENTIFIER;
         c--;
         int lex_len = 1;

         //TODO: can't this point at last+1???
         for (; likely((c+lex_len != curr_str+len) && (c[lex_len] != '\0')); lex_len++)
            if (isSpecial(c[lex_len]) || c[lex_len] == ' ') {
               lex_len--;
               break;
            }

         lexeme->len = lex_len;

         c += lexeme->len;
         BUG_PRINT_LVL(25, "identifier (length %i): ", lexeme->len);
         BUG_PRINTN_LVL(25, lexeme->value, lexeme->len);
         list_add(&lexeme->list, &lookup_table.src.lexemes.list);
         continue;
      }

   }

   return NO_ERROR;
}


int* _get_next_quotes(const char* str, size_t len, int i);
int _increment_counter(const char* str, size_t len, int i, bool init);
