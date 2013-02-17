#include "main.h"

int main()  {
   for (string input; input != "quit"; getline(cin, input))
      cout << formatSexps(input) << '\n';

   return 0;
}

