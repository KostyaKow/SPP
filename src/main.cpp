#include "main.h"

int main()  {
   for (string input; input != "quit"; getline(cin, input)) {
      cout << "lexed sexps: " << Sexps(input).getStrLexeme() << "\n\n$ ";
   }

   return 0;
}
