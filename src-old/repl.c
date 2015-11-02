#include "repl.h"
#include "lookuptable.h"
#include "lexer.h"
#include "errors.h"
#include "misc.h" //TAB and BUG

int repl() {
   printf("\n\n*********Welcome to spp.*********");

   char str[1000];

   //100 cycles is to avoid infinite loop when something goes wrong.
   for (int i = 0; i < 100; i++) {
      printf("\n\n>");
      int input_result = scanf("%999[^\n]", str);getch();

      if (E(lookup_table_add(str, strlen(str))) || !input_result || input_result == -1 || !strcmp(str, "(exit)")) {
         T;T;STAR(16);BUG_LVL(2, "exiting REPL");T;STAR(16);
         break;
      }
   }

   print_session_summary();

   return 0;
}


void print_session_summary() {TAB = 0;
   BUG_PRINT_LVL(20, "\nsession summary:");
   lookup_table_t* tmp; int i = 1;
   list_for_each_entry_reverse(tmp, &lookup_table.list, list) {
      BUG_PRINT_LVL(20, "\ninfo for table #%i\n", i++);
      TAB = 3;
      BUG_PRINT_LVL(20, "source code:");
      BUG_PRINTN_LVL(20, tmp->src.str, tmp->src.len);T;

      lexeme_t* tmp_lex;
      list_for_each_entry_reverse(tmp_lex, &tmp->src.lexemes.list, list) {
         BUG_PRINTN_LVL(20, "-", 1);
         BUG_PRINTN_LVL(20, tmp_lex->value, tmp_lex->len);
      }
      BUG_PRINTN_LVL(20, "-", 1);
      BUG_PRINT_LVL(20, "\n\n");
   }
}
