#include "main.h"

int main()  {
   for (string input; input != "quit"; getline(cin, input)) {
      cout << Sexps(input).getVal() << '\n';
   }

   return 0;
}

