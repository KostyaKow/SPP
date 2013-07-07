#include "list.h"

#include "misc.h"
#include "lexer.h"
#include "errors.h"

error_e init(int nargs, char** args) {
   INIT_LIST_HEAD(&lex_table.src.list);
   INIT_LIST_HEAD(&lex_table.lexemes.list);
}


int main(int nargs, char** args) {
   E(init(nargs, args));

   printf("\n\n*********\n>");

   char str[10000];

   bool terminate = false;
   int i = 0;
   while (!terminate) {
      if (scanf("%10000[^\n]", str))
         terminate = E(lex_table_add(str, strlen(str)));
      printf("\n\n\n>");
      getch();
      i++;
      if (i > 10)
         break;
   }

   return 0;
}

