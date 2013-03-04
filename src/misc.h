#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

#define DEBUG_SPP


#include <string>

// Some C++ formatters (such as Code::Blocks's) cannoot handle :
// in C++11 range-based for loops, so I use _in_, in place of :
#define _in_ :

typedef char byte;

//example for function that returns true if someBool is true, otherwise throws exception:
// bool test(bool someBool) {
//   return someBool ? true : ternaryThrow("someBool is false");
// }
inline bool ternaryThrow(std::string str) {
   throw str;
   return false;
}

inline bool inRange(int b, int a, int c) {
    if (b >= a && b <= c)
        return true;
    else return false;
}


inline bool strToBool(const std::string& str) { //hacky & undreadable; re-write
   return str == "true" ? true : str == "false" ? false : ternaryThrow("bad parameter to strToBool");
}

#define BUG ;std::cout << "."; std::cin.getline(new char[0], 0);

#endif // MISC_H_INCLUDED
