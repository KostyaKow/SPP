#ifndef SSTR_H_INCLUDED
#define SSTR_H_INCLUDED

#include <string>
#include "misc.h"

enum class NumType : byte { NONE, INT, FLOAT };

NumType getNumType(std::string s);


#endif // SSTR_H_INCLUDED
