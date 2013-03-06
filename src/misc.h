#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

#define DEBUG_SPP


#include <string>

// Some C++ formatters (such as Code::Blocks's) cannoot handle :
// in C++11 range-based for loops, so I use _in_, in place of :
#define _in_ :


typedef char byte;

inline bool inRange(int b, int a, int c) {
    if (b >= a && b <= c)
        return true;
    else return false;
}

//I was pretty stoned when I wrote previous version..
inline bool strToBool(const std::string& str) {
   if (str == "true")
      return true;
   if (str == "false")
      return false;

   else
      throw "bad parameter to StrToBool";
   return false;
}

#ifdef DEBUG_SPP

//Debug print
#define BUG(x) ;std::cout << "^^ "#x"\n"; //std::cin.getline(new char[0], 0); std::cout << "\n";
#else
#define BUG(x)
#endif

#endif // MISC_H_INCLUDED
