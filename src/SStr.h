#ifndef SSTR_H_INCLUDED
#define SSTR_H_INCLUDED

#include <string>

namespace SLib { namespace SStr {

std::string intToCppStr(int num);
int cppStrToInt(std::string str);

bool isNumber(std::string s);
bool isDigit(char c);

}} //namespace


#endif // SSTR_H_INCLUDED
