#include "SList.h"
#include "SStr.h"

#include "misc.h"

namespace SLib {
namespace SStr {

bool isDigit(char c) { //messy, but fast
   if (c >= '0' && c <= '9') //if (SList::contains(SList::list('0' __ '9'), c))
      return true;
   else return false;
}

bool isFloat(std::string s) {
   if (s.length() < 1)
      return false;

   bool haveDot = false;

   for (char c in s)
      if (!isDigit(c))
         if (c != '.')
            return false;
         else
            haveDot = !haveDot;

   if (haveDot)
      return true;
   else return false;
}

bool isInt(std::string s) {
   if (s.length() < 1)
      return false;

   for (char c in s)
      if (!isDigit(c))
         return false;

   return true;
}

}}

