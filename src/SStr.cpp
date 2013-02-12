#include "SList.h"
#include "SStr.h"

#include "misc.h"

namespace SLib {
namespace SStr {

//TODO: use IFDEFS for BOOST and maybe define my own version
std::string intToCppStr(int num) {}
int cppStrToInt(std::string str) {}


bool isNumber(std::string s) {
   if (s.length() < 1)
      return false;

for (char c in s)
      if (!isDigit(c))
         return false;

   return true;
}



bool isDigit(char c) { //messy, but fast
   if ((int)c >= 48 && (int)c <= 57) //if (SList::contains(SList::list('0' __ '9'), c))
      return true;
   else return false;
}

}}

