#ifndef SSEXPS_H_INCLUDED
#define SSEXPS_H_INCLUDED

#include "main.h"

namespace SLib { namespace SSexps { //Scheme S-Expression

enum class ParseError { NO_BEGIN_PARENTHESIS = -42, NO_END_PARENTHESIS,
                        OTHER_STUFF,                MORE_STUFF }; //other_stuff?


class Sexps {
    friend Sexps parseExpression(std::string expr);

    bool eval;
    bool atom;
    std::string val;

    std::vector<Sexps> subSexps;

public:
    Sexps(std::string _val = 0, bool _eval = true)
        : val(_val), eval(_eval) {}

};



/*
//I suck at C++ (or rather C++ is a shitty language). I am not even sure what I am trying to do.
//use C++11 tuples or something....

template <class RetType,
            class Param1, class Param2, class Param3, class Param4, class Param5,
            class Param6, class Param7, class Param8, class Param9, class Param10,
            class Param11, class Param12, class Param13, class Param14,
            class Param15, class Param16,>
class Function {};

template<>
class Function <class RetType, class Param1> {
    RetType body(Param1 p) {}
};

template<>
class Function <class RetType, class Param1, class Param2> {
    RetType body(Param1 p1, Param2 p2) {}
};
*/


Sexps parseExpression(std::string expr);
std::string formatSexps(std::string sexps);



}} //namespace


/*

class SExps {
    bool atom;
    bool integer;
    bool floatingPoint;
    bool character;

    unique_ptr< vector<SExps> > val;
    unique_ptr<string> strVal;

public:

    unique_ptr< vector<SExps> > getVal()  { return ;  }
    unique_ptr<string> getStrVal()      { return unique_ptr(strVal);     }

    SExps(int _val)       { val.push_back((string)_val); }
    SExps(vector<SExps> _val)    { val->swap(_val); }
    SExps(SExps& _this) {  *this = &_this; }

    SExps(SExps* _this)
                    : atom(_this->atom), integer(_this->integer), floatingPoint(_this->floatingPoint), character(_this->character),
                      val(_this->val), strVal(_this->strVal)
                    { }


    bool isAtom()   { return atom; }

    bool isInt()    { return integer;       }
    bool isFloat()  { return floatingPoint; }
    bool isChar()   { return character;     }

    virtual bool isBuiltInFunction() { return false; }


};

class builtInFunction : public SExps
{
    string name;
    SExps parameter;

    bool isBuiltInFunction() { return true; }

public:

    function<SExps(SExps)> eval;

    builtInFunction(function<SExps(SExps)> _eval) {
        eval = _eval;
    }


};

int main()
{
    builtInFunction t(
                      [](SExps exps) -> SExps { cout << exps->getVal; return exps->getVal(); }
                      );

    cout << "Hello world!" << endl;
    return 0;
}*/



//.................

#endif // SSEXPS_H_INCLUDED
