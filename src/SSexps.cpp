#include "SSexps.h"

namespace SLib { namespace SSexps { //S-Expression


Sexps parseExpression(std::string expr) {
    Sexps sexps;

	if (expr[0] != '(')
		if (expr[0] != '\'')
            sexps.atom = true;
        else
            sexps.eval = false;
}


std::string formatSexps(std::string sexps) {}

}} //namespace
