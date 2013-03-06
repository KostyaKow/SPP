#ifndef SSEXPS_H_INCLUDED
#define SSEXPS_H_INCLUDED

#include <memory>
#include <stdexcept>

#include <string>
#include <vector>
#include <map>
#include <tuple>

#include "SStr.h"
#include "SList.h"
#include "SError.h"
#include "SStateMachine.h"

#include "misc.h"


enum class ParseError {
   NO_BEGIN_PARENTHESIS = -42, NO_END_PARENTHESIS, UNMATCHED_QUOTES, OTHER_STUFF }; //other_stuff?


std::string formatSexps(const std::string& sexpsWithSpaces);


class Sexps {
   friend Sexps parseExpression(const std::string& expr);

   enum class Type : byte { BOOL, INT, FLOAT, CHAR, STR,
                            ATOM, EMPTY, //NOT_ATOM
                            QUOTE_SEXPS, BACK_QUOTE_SEXPS, EVAL_SEXPS, SEXPS };
   Type type;

   const std::string val;

   void* pVal; //cast this to needed type

   std::tuple<Type, void*, std::string> typedVal; //TODO: delete the other things (string val, and void *pVal and Type type)

   std::vector<Sexps>* subSexps;

public:

   Sexps(const std::string &_val = 0)
      : val(formatSexps(_val))
   {
      parseExps();
   }

   /* TODO: delete?
   inline bool isQuoted()     const { return type == Type::QUOTE_SEXPS;       }
   inline bool isBackQuoted() const { return type == Type::BACK_QUOTE_SEXPS;  }
   inline bool isEvaled()     const { return type == Type::EVAL_SEXPS;        }

   inline bool isSexps()      const { return type == Type::SEXPS; } //normal

   inline bool isBool()       const { return type == Type::BOOL;  }
   inline bool isInt()        const { return type == Type::INT;   }
   inline bool isFloat()      const { return type == Type::FLOAT; }
   inline bool isChar()       const { return type == Type::CHAR;  }
   inline bool isStr()        const { return type == Type::STR;   }

   inline bool isAtom() const { return isBool() || isInt() || isFloat() || isChar() || isStr(); }
   */

   std::string getVal() const {
      return val;
   }

   void eval();
   void parseExps();

#ifdef DEBUG_SPP
   void printVal();
   void printType();
#endif

};

int handleError(ParseError error);

class Function {
   Sexps _Function;

   struct function {
      std::string name;
      Sexps parameter;
      Sexps body;
   } function;

   //std::function<SExps(SExps)> eval; //runtime??

public:

};

//why not just do function pointers
/*template <class return_type = Exception::invalid, class p1 = Exception::invalid, class p2 = Exception::invalid>
class builtInFunction : public Function
{
   std::function<Sexps(Sexps)> eval;
public:
   builtInFunction(function<SExps(SExps)> _eval) {
      eval = _eval;
   }
};*/


/*
TODO: Merge this into main code, and delete the ugly comment wall...

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
