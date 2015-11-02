#include "regex.h"

int main() {
   Regex r("a-z");
   cout << r.match("b");
}



