#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

// Some C++ formatters (such as Code::Blocks's) cannoot handle
// : in C++11 range-based for loops, so I try to use in, in place of :
#define in :

//file for random stuff, which doesn't yet have it's own header+cpp

inline bool inRange(int b, int a, int c) { //inclusive (so >= <=)
    if (b >= a && b <= c)
        return true;
    else return false;
}

#endif // MISC_H_INCLUDED
