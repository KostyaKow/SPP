#include "main.h"



int main()  {

   for (string input; input != "quit"; getline(cin, input)) {
      Sexps exps(input);
      cout << "lexed sexps:\t" << exps.getStrLexeme() << "\nevaled:\t\t" << exps.eval().getStrLexeme() << "\n\n$ ";
   }

   return 0;
}
