#include "main.h"


int main()  {

   for (string input; input != "quit"; getline(cin, input)) {
      cout <<  LET
                  (exps = Sexps(input))
               IN
                  ;
               END
                  ("lexed sexps:\t" + exps.getStrLexeme() + "\nevaled:\t\t" + exps.eval().getStrLexeme() + "\n\n$ ");
   }

   return 0;
}
