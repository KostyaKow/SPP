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

   enum class TokenClass : byte { BOOL, INT, FLOAT, CHAR, STR, //atoms
                                  EMPTY, //also atom
                                  QUOTE_SEXPS, BACK_QUOTE_SEXPS, EVAL_SEXPS, SEXPS }; //sexps. btw EVAL_SEXPS is ~(sexps)
   TokenClass tokenClass;
   std::string strLexeme;
   void* ptrLexeme; //cast this to needed type
   std::vector<Sexps>* subSexps;

   bool atom; //do not use this. use isAtom instead!

public:

   Sexps(std::string _strLexeme = 0)
      : strLexeme(formatSexps(_strLexeme))
   {
      parseExps();
   }

   Sexps(const Sexps& other)
      : tokenClass(other.tokenClass), strLexeme(other.strLexeme),
        ptrLexeme(other.ptrLexeme), subSexps(other.subSexps) //FIXME. crash?
   {}

   Sexps(Sexps* other)
      : tokenClass(other->tokenClass), strLexeme(other->strLexeme),
        ptrLexeme(other->ptrLexeme), subSexps(other->subSexps) //FIXME
   {}

   ~Sexps() {
      // delete ptrLexeme; //crash!
      // delete[] subSexps; //crash!
   }

   std::string getStrLexeme() const { return strLexeme; }

   Sexps eval();
   void parseExps(); //todo: move majority of stuff to new function getTypeToken()

   bool isEmpty() { return tokenClass == TokenClass::EMPTY; }

   bool isAtom() {
      return (
              LET (is_atom = atom || (elem(tokenClass, {TokenClass::BOOL, TokenClass::INT, TokenClass::FLOAT, TokenClass::CHAR, TokenClass::STR, TokenClass::EMPTY})))
              IN if (is_atom) atom = true
              END (is_atom)
              );
   }

#ifdef DEBUG_SPP
   void printVal();
   void printTokenClass();
#endif

};

int handleError(ParseError error);

/*class Function {

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

   Sexps eval(Sexps args) {}

};*/

#endif // SSEXPS_H_INCLUDED
