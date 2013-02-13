#ifndef SSEXPS_H_INCLUDED
#define SSEXPS_H_INCLUDED

#include <memory>
#include <stdexcept>

#include <vector>
#include <string>


//#include <tuple> //don't need



namespace SLib {
namespace SSexps { //Scheme S-Expression

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

   bool is_quoted, is_backQuoted, is_atom;
   bool is_bool, is_int, is_float, is_char, is_str;

   const std::string val;
   std::vector<Sexps>* subSexps;

public:

   Sexps(const std::string &_val = 0)
      : is_quoted(is_backQuoted(is_atom(is_bool(is_int(is_float(is_char(is_str(false))))))))
   {

      val = formatSexps(_val);
      parseExps();
   }


   bool isQuoted()      const { return is_quoted;     }
   bool isBackQuoted()  const { return is_backQuoted; }

   bool isAtom()        const { return is_atom;       }

   bool isInt()         const { return is_int;        }
   bool isFloat()       const { return is_float;      }
   bool isChar()        const { return is_char;       }

   void eval();
   void parseExps();

};







int handleError(SSexps::ParseError error);

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
