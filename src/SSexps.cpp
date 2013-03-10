#include "SSexps.h"
#include <boost/lexical_cast.hpp>

Sexps Sexps::eval() {

   switch(tokenClass) {
   case TokenClass::QUOTE_SEXPS:
      return;
   break;

   //it would be better to write this in Lisp itself... Is it possible to expose Lisp function in C++ code?
   case TokenClass::BACK_QUOTE_SEXPS:
      std::string _new_;
      for (Sexps s : *subSexps)
         if(s.getStrLexeme()[0] == '~')
            _new_.append(s.eval().getStrLexeme());
      return Sexps(_new_);
   break;

   }
}

//side effect:   if first quote character is present, changes m_start, else m_start and m_end are -1
//return value:  true if 2 quotes are found; otherwise false
bool getNextQuote(const std::string& str, uint current, int& m_start, int& m_end) { //FIXME: change to return a struct of bool * start * end
   m_start = m_end = -1;
   if (current > str.length())
      return false;

   for (int i = current; i < str.length(); i++) {
      if (str[i] == '\"') {

         if (m_start == -1)
            m_start = i;

         else if (m_end == -1) {
            m_end = i;
            return true;
         }
      }
   }

   return false;
}

void Sexps::parseExps() {
   using boost::lexical_cast;
   using std::vector;
   using std::string;

   auto h_groupLexemes = [](const string& str) -> vector<string> {
      vector<string> r_lexemes;

      for (int i = 0; i < str.length(); i++) {
         string s;

         int startQuote, endQuote; // all lexemes in " " go together.
         if (getNextQuote(str, i, startQuote, endQuote) && i == startQuote)
            for (; i < endQuote; i++)
               s.push_back(str[i]);


         for (; str[i] != ' ' && i < str.length(); i++)
            s.push_back(str[i]);

         //check if previous is one of the quotes or ~, and concat to this s
         if (r_lexemes.size() && contains( {"~", "'", "`"}, r_lexemes[r_lexemes.size()-1]))
         r_lexemes[r_lexemes.size()-1] += s;
         else
            r_lexemes.push_back(s);
      }

      return r_lexemes;
   };

   vector<string> vecVal = h_groupLexemes(strLexeme);

   BUG(grouped lexemes)

   auto h_getTypeOfToken = [&h_groupLexemes](const string& str) -> TokenClass {
      vector<string> vecVal = h_groupLexemes(str); //FIXME: delete this. quick and dirty to not change everything

#ifdef DEBUG_SPP
      BUG(grouped words) //ugh, I am stupid. I was trying to access element o fempty vector...
      std::cout << "^^ there is " << vecVal.size() << " tokens\n";
#endif

      TokenClass tokenClass;

      if (!vecVal.size())
         return TokenClass::EMPTY;

      //if doesn't match anything then it's atom.
      if (vecVal[0] != "(")
         if (vecVal[0] != "'(")
            if (vecVal[0] != "`(")
               if (vecVal[0] != "~(")
                  tokenClass = TokenClass::ATOM;
               else tokenClass = TokenClass::EVAL_SEXPS;
            else tokenClass = TokenClass::BACK_QUOTE_SEXPS;
         else tokenClass = TokenClass::QUOTE_SEXPS;
      else tokenClass = TokenClass::SEXPS;

      BUG(matched stuff)

      if (tokenClass == TokenClass::ATOM) { //if atom, figure out if BOOL, INT, FLOAT, CHAR or STR. change the type.
         std::cout << "atom!!!\n";

         if (vecVal.size() != 1)
            throw(string("atom with " + lexical_cast<string>(vecVal.size()) + " elements"));

         NumType numType = getNumType(vecVal[0]);

         if (numType == NumType::INT) { //INT
            tokenClass = TokenClass::INT;
            ///pVal = (void*)new int; //this is where the magic happens
            ///*(int*)pVal = lexical_cast<int>(vecVal[0]);
         }

         else if (numType == NumType::FLOAT) { //FLOAT
            tokenClass = TokenClass::FLOAT;
            ///pVal = (void*)new float;
            ///*(int*)pVal = lexical_cast<float>(vecVal[0]);
         }

         //NumTokenClass::NONE
         else if (contains( {"true", "false"}, vecVal[0])) { //BOOL
            tokenClass = TokenClass::BOOL;
            //pVal = (void*)new bool;
            ///*(bool*)pVal = strToBool(vecVal[0]);
         }

         else if (vecVal[0] == "\"") { //STR
            tokenClass = TokenClass::STR;
            ///pVal = (void*)new string; //too many pointers make me confused and cause me to leak memory....
            ///*(string*)pVal = vecVal[0];
         }
         else if (vecVal[0] == "'") { //CHAR
            tokenClass = TokenClass::STR;
            ///pVal = (void*)new char;
            ///*(char*)pVal = vecVal[0][0];
            if (vecVal[0].size() != 3) //fixme: right now: 'a' <--good; '\a' <--bad.
               throw string("incorrect size of char");
         }

      }

      return tokenClass;
   };

   tokenClass = h_getTypeOfToken(strLexeme);


#ifdef DEBUG_SPP
   printTokenClass(); std::cout << "\n";
#endif

   /*
   else { //if not atom
      for (auto str _in_ vecVal) {
         if (str == "")
      }
   }
   */

}

int handleError(ParseError error) {
   using StateMachine::line;
   using StateMachine::file;
   using Exception::ErrorLevel;

   switch (error) {
   case ParseError::NO_BEGIN_PARENTHESIS:
      printError(ErrorLevel::BAD_INPUT,
                 "An expression  has to start with an ' or an (",
                 line, file);
   break;

   case ParseError::NO_END_PARENTHESIS:
      printError(ErrorLevel::BAD_INPUT,
                 "An expression has to end with an )",
                 line, file);
   break;

   case ParseError::UNMATCHED_QUOTES:
      printError(ErrorLevel::BAD_INPUT,
                 "Unmatched quote",
                 line, file);
   break;

   default:
      printError(ErrorLevel::FATAL_ERROR,
                 "Unkown Error has occured",
                 line, file);
   break;

   }
}

std::string formatSexps(const std::string& sexpsWithSpaces) {
   std::vector<char> beforeParens = {'\'', '`', '~'};
   std::vector<char> openParens = {'(', ')'}, closeParens = {')', ']'};

   //removes extra whitespaces between words (when there is more then 1). Disgregards extra white-spaces in quotes. Also removes whitespaces between ' and ( (~(, `().
   auto h_removeExtraWhitespaces = [&](const std::string& str, int start, int end) -> std::string {
      if ((end - start) < 1 || (end - start) < str.length())
         return str;

      while (str[start] == ' ') start++; ///removes ALL whitespaces from beginning!
      std::string r_str;

      for (int i = start; i < end; i++) {
         int startNextQuote, endNextQuote;

         if (getNextQuote(str, i, startNextQuote, endNextQuote) && startNextQuote == i) //checks for "'s
            for (i = startNextQuote; i < endNextQuote; i++)
               r_str.push_back(str[i]);

         while (str[i] == ' ' && str[i+1] == ' ') i++;
         r_str.push_back(str[i]);

         if (contains(beforeParens, str[i]))
            if (str[i+1] == ' ') i++;
      }
      return r_str;
   };

   std::string sexps = h_removeExtraWhitespaces(sexpsWithSpaces, 0, sexpsWithSpaces.length());

   std::string r_sexps;
   int m_quoteStart, m_quoteEnd;

   for (int i = 0; i < sexps.length(); i++) {

      if (!getNextQuote(sexps, i, m_quoteStart, m_quoteEnd))
         if (m_quoteStart != -1) throw std::runtime_error("there is a start quote (\"); but no end-quote");

      if (sexps[i] == '\'' || sexps[i] == '`' || sexps[i] == '~') {
         if (sexps[i+1] == ' ') {
            r_sexps.push_back(sexps[i]);
            i++; continue;
         }
      }

      if (sexps[i] == '(' && sexps[i+1] != ' ' && !contains(beforeParens, sexps[i-1])) //insert space for next char
         r_sexps.push_back(' ');

      if (sexps[i-1] == '(') //previous
         r_sexps.push_back(' ');//insert space for previous (

      if (i && sexps[i] == ')' && sexps[i-1] != ' ' && !contains(beforeParens , sexps[i-1]))
         r_sexps.push_back(' ');

      if (i == m_quoteStart)
         while(i != m_quoteEnd)
            r_sexps.push_back(sexps[i++]);

      r_sexps.push_back(sexps[i]);
   }

   return h_removeExtraWhitespaces(r_sexps, 0, r_sexps.length());
}

#ifdef DEBUG_SPP

void Sexps::printVal() {}

void Sexps::printTokenClass() {
   using std::cout;

   switch (tokenClass) {
   case TokenClass::BOOL:
      cout << "BOOL\n";
   break;

   case TokenClass::INT:
      cout << "INT\n";
   break;

   case TokenClass::FLOAT:
      cout << "FLOAT\n";
   break;

   case TokenClass::CHAR:
      cout << "CHAR\n";
   break;

   case TokenClass::STR:
      cout << "STR\n";
   break;
   //
   case TokenClass::ATOM:
      cout << "ATOM\n";
   break;
   //
   case TokenClass::QUOTE_SEXPS:
      cout << "QUOTE_SEXPS\n";
   break;

   case TokenClass::BACK_QUOTE_SEXPS:
      cout << "BACK_QUOTE_SEXPS\n";
   break;

   case TokenClass::EVAL_SEXPS:
      cout << "EVAL_SEXPS\n";
   break;

   case TokenClass::SEXPS:
      cout << "SEXPS\n";
   break;

   default: //TODO: add other tokenClasss.
      cout << "^^ could not find the tokenClass of sexps\n";
   break;
   }
}
#endif


