#include "repl.h"
#include "lookuptable.h"
#include "lexer.h"
#include "errors.h"
#include "misc.h" //TAB and BUG

int repl() {
   printf("\n\n*********Welcome to spp.");

   char str[1000];

   //100 cycles is to avoid infinite loop when something goes wrong.
   for (int i = 0; i < 100; i++) {
      printf("\n\n\n>");
      int input_result = scanf("%999[^\n]", str);getch();

      if (E(lookup_table_add(str, strlen(str))) || !input_result || input_result == -1 || !strcmp(str, "(exit)")) {
         BUG_LVL(2, "an error has occured; exiting REPL");
         break;
      }
   }

   TAB=0;BUG_PRINT_LVL(15, "exiting REPL");
   print_session_summary();

   return 0;
}


void print_session_summary() {TAB = 0;BUG_LVL(25, "\nsession summary:");
   int i = 1;
   lookup_table_t* tmp;
   list_for_each_entry(tmp, &lookup_table.list, list) {TAB = 5;
      BUG_PRINT_LVL(21, "\tinfo for table #%i\n", i++);TAB = 10;
      BUG_PRINT_LVL(21, "\tsource code:");
      BUG_PRINTN_LVL(21, tmp->src.str, tmp->src.len);T;

      if (i >= 15) break;

      int j = 1;
      lexeme_t* tmp_lex;
      list_for_each_entry(tmp_lex, &tmp->src.lexemes.list, list) {TAB = 15;
         if (j++ >= 15) break;
         T;BUG_PRINTN_LVL(21, "-", 1);
         BUG_PRINTN_LVL(21, tmp_lex->value, tmp_lex->len);
      }
   }
}
