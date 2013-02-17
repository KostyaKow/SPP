#ifndef SSTR_H_INCLUDED
#define SSTR_H_INCLUDED

#include <string>
#include "misc.h"

namespace SLib {
namespace SStr {

//bool isDigit(char c);
//bool isFloat(std::string s);
//bool isInt(std::string s);

enum class NumType : byte { NONE, INT, FLOAT };

NumType getNumType(std::string s);

}} //namespace


#endif // SSTR_H_INCLUDED
