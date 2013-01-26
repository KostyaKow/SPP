#include "SList.h"
#include "SStr.h"

namespace SLib {
namespace SStr {

//TODO: use IFDEFS for BOOST and maybe define my own version
std::string intToCppStr(int num) {}
int cppStrToInt(std::string str) {}


bool isNumber(std::string s) {
    for (char c : s)
        if (!isDigit(c))
            return false;
    return true;
}

bool isDigit(char c) {
    if (SList::contains( SList::list('0' __ '9'), c))
        return true;
    else return false;
}

}
}
