#ifndef SSEXPS_H_INCLUDED
#define SSEXPS_H_INCLUDED

#include <memory>
#include <stdexcept>

#include <vector>
#include <string>

#include "SStr.h"
#include "SList.h"
#include "SError.h"
#include "SStateMachine.h"

#include "misc.h"


enum class ParseError {
   NO_BEGIN_PARENTHESIS = -42, NO_END_PARENTHESIS, UNMATCHED_QUOTES, OTHER_STUFF }; //other_stuff?


std::string formatSexps(const std::string& sexpsWithSpaces);

//string checking

/*
***delete***
bool isCharInQuotes(int charPlace, const std::string& str);                      //checks if char inside "quotes"
bool isStrInsideQuotes(int start, int end, const std::string& str);              //checks if str[start]..str[end] is inside "quotes"
*/


class Sexps {
   friend Sexps parseExpression(const std::string& expr);

   enum class Type : byte { BOOL, INT, FLOAT, CHAR, STR,
                            ATOM, //NOT_ATOM
                            QUOTE_SEXPS, BACK_QUOTE_SEXPS, EVAL_SEXPS, SEXPS };
   Type type;


   const std::string val;
   void* pVal; //cast this to needed type
   std::vector<Sexps>* subSexps;


public:

   Sexps(const std::string &_val = 0)
      : val(formatSexps(_val))
   {
      parseExps();
   }

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

   std::string getVal() const {
      return val;
   }

   void eval();
   void parseExps();


#ifdef DEBUG_SPP
   void printType() {
      using std::cout;

      switch (type) {
      case Type::BOOL:
         cout << "\nBOOL";
      break;

      case Type::INT:
         cout << "\nINT";
      break;

      case Type::FLOAT:
         cout << "\nFLOAT";
      break;

      case Type::CHAR:
         cout << "\nCHAR";
      break;

      case Type::STR:
         cout << "\STR";
      break;
      //
      case Type::ATOM:
         cout << "\nATOM";
      break;
      //
      case Type::QUOTE_SEXPS:
         cout << "\nQUOTE_SEXPS";
      break;

      case Type::BACK_QUOTE_SEXPS:
         cout << "\nBACK_QUOTE_SEXPS";
      break;

      case Type::EVAL_SEXPS:
         cout << "\nEVAL_SEXPS";
      break;

      case Type::SEXPS:
         cout << "\nSEXPS";
      break;

      default:
         cout << "\ncould not find the type of sexps";
      break;
      }
   }
#endif
};





int handleError(ParseError error);


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
