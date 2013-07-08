#include "list.h"

#include "misc.h"
#include "lexer.h"
#include "errors.h"

error_e init(int nargs, char** args) {
   if (nargs == 1) //if no arguments, start repl
      mode = 2;

   TAB = 1;

   INIT_LIST_HEAD(&lex_table.src.list);
   INIT_LIST_HEAD(&lex_table.lexemes.list);

   return NO_ERROR;
}

int repl() {
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

int main(int nargs, char** args) {
   E(init(nargs, args));

   switch (mode) {
   case 1:
      BUG_LVL(1, "compiler is not yet implemented");
      break;
   case 2:
      return repl();
      break;
   default:
      BUG_LVL(1, "unkown mode selected");
      break;
   }

   return 0;
}



