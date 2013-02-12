#include "main.h"
#include "SList.h"
#include "SStr.h"
#include "SError.h"
#include "SStateMachine.h"



#include "SList.h"

using namespace std;
using namespace SLib;
using namespace SStr;
using namespace SList;
using namespace SSexps;

int main()  {
   //cout << list(1.2, 2.4 __ 5);



   string input;

   while(input != "quit") {
      cin >> input;

      cout << "\n" << (isCharInQuotes(5, input) ? "true\n\n" : "false\n\n");

   }

   /*cout << filter<int>(
                  [](int c) { return c > 16;},
                  list(3, 6 __ 42)
                  );
   cout << contains<int>(list(1, 5), 42);*/

   return 0;
}

