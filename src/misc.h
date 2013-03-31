#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

#define DEBUG_SPP


#include <string>

// Some C++ formatters (such as Code::Blocks's) cannot handle :
// in C++11 range-based for loops, so I use IN, in place of :
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


//I should get shot
//this will probably go away really soon, but for now I am having fun :p
#define LET(x) [&]() { auto x;
#define _(x) auto x;
#define IN
#define END(x) ;return x; }()
//cout << LET(x = 5)_(y = 10) IN int n = x+y END(n+x); will print 20


#endif // MISC_H_INCLUDED
