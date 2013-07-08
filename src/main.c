#include "repl.h"
#include "lookuptable.h"
#include "misc.h"
#include "lexer.h"
#include "errors.h"
#include "list.h"

error_e init(int nargs, char** args) {
   if (nargs == 1) //if no arguments, start repl
      mode = 2;

   TAB = 1;

   INIT_LIST_HEAD(&lookup_table.list);

   return NO_ERROR;
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



