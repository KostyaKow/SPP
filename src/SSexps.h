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
   Type tokenClass;
   const std::string strLexeme;
   void* ptrLexeme; //cast this to needed type
   std::tuple<Type, void*, std::string> token; //TODO: delete the other things (string val, and void *pVal and Type type)
   std::vector<Sexps>* subSexps;

public:

   Sexps(const std::string &_val = 0)
      : val(formatSexps(_val))
   {
      parseExps();
   }

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

   struct Function_struct {
      Function_struct() = default;
      Function_struct(std::string _name, Sexps _args, Sexps _body) : name(_name), args(_args), body(_body) {}
      Function_struct(const Function_struct& other) : name(other.name), args(other.args), body(other.body) {}

      std::string name;
      Sexps args;
      Sexps body;

   } function_struct;

   //std::function<SExps(SExps)> eval; //runtime??
   void* buildInFunction;

public:

   Function() = default;
   Function(const Function_struct& _function_struct) : function_struct(_function_struct) {}
   Function(std::string _name, Sexps _args, Sexps _body) : function_struct(_name, _args, _body) {}
   Function(void* _buildInFunction) : buildInFunction(_buildInFunction) {}

   Sexps eval(Sexps args) {

   }

};


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
