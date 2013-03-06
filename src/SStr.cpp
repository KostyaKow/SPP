#include "SList.h"
#include "SStr.h"

#include "misc.h"

bool isDigit(char c) {
   if (c >= '0' && c <= '9') //can also do: if (SList::contains(SList::list('0' __ '9'), c)), but this would be slower
      return true;
   else return false;
}

bool isFloat(std::string s) {
   if (s.length() < 1)
      return false;

   bool haveDot = false;

   for (char c _in_ s)
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

   for (char c _in_ s)
      if (!isDigit(c))
         return false;

   return true;
}


NumType getNumType(std::string s) { //ehh...ugly
   if (s.length() < 1)
      return NumType::NONE;

   int numDot = 0;

   for (char c _in_ s)
      if (!isDigit(c))
         if (c != '.')
            return NumType::NONE;
         else
            numDot++;

   if (!numDot)
      return NumType::INT;
   if (numDot == 1)
      return NumType::FLOAT;
   else return NumType::FLOAT;
}


