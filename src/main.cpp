#include "main.h"
#include "SList.h"
#include "SStr.h"
#include "SError.h"
#include "SStateMachine.h"
#include "SSexps.h"


#include "SList.h"

using namespace std;
using namespace SLib;
using namespace SStr;
using namespace SList;
using namespace SSexps;

int main()  {
   for (string input; input != "quit"; getline(cin, input))
      cout << formatSexps(input) << '\n';

   return 0;
}

