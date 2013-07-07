#include "lexer.h"

lex_table_t lex_table;

error_e lex_table_add(const char *str, int len) {TAB = 0;

   if (len == 0) {
      len = strlen(str);
      BUG_LVL(100, "called with an empty string");
   }
   BUG_LVL(60, "called with a string of length %i", len);

   char *curr_str = str_cpy(str, len);

   source_code_t *curr_src = malloc(sizeof(source_code_t));
   curr_src->str = curr_str;
   curr_src->len = len;

   list_add(&curr_src->list, &lex_table.src.list);

   BUG_LVL(25, "");TAB = 3;
   for (char *c = curr_str; likely(c-1 != curr_str+len && *c != '\0'); c += 1) {
      lexeme_t *lexeme = malloc(sizeof(lexeme_t));

      if (*c == '(' || *c == ')') {
         lexeme->type = PAREN;
         lexeme->value = c;
         lexeme->len = 1;

         BUG_PRINT_LVL(25, "parengthesis");
         list_add(&lexeme->list, &lex_table.lexemes.list);
         continue;
      }

      else if (isLetter(*c)) {
         lexeme->type = IDENTIFIER;
         lexeme->value = c;

         for ( lexeme->len = 1;
               likely((&c[lexeme->len-1] != curr_str+len) && (c[lexeme->len] != '\0'));
               lexeme->len++)
            if (c[lexeme->len-1] == '(' || c[lexeme->len-1] == ')' || c[lexeme->len-1] == ' ' || c[lexeme->len-1] == '"' || c[lexeme->len-1] == '\'') break;
         lexeme->len--;

         c += lexeme->len;
         BUG_PRINT_LVL(25, "identifier (length %i): ", lexeme->len);
         BUG_PRINTN_LVL(25, lexeme->value, lexeme->len);
         list_add(&lexeme->list, &lex_table.lexemes.list);
         continue;
      }

   }

   return NO_ERROR;
}


int* _get_next_quotes(const char* str, size_t len, int i);
int _increment_counter(const char* str, size_t len, int i, bool init);
