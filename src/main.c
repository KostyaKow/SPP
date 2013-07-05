#include "list.h"

#include "misc.h"
#include "lexer.h"
#include "errors.h"

lex_table_t* lex_table = NULL;

bool init(int nargs, char** args) {
   lex_table = (lex_table*)malloc(sizeof(lex_table_t));
   lex_table->lexemes = new_list();
}



int main(int nargs, char** args) {
   init(nargs, args);


   printf("\n\n*********\n>");

   char str[10000];
   bool terminate = false;


   while (!terminate) {
      terminate = handle_error(lex_table_add(scanf(str, "%10000[^\n]"), str));
      printf("\n\n\n>");

   }

   return 0;
}

