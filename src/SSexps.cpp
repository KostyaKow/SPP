#include <string>
#include <vector>

#include "SSexps.h"
#include "SStr.h"
#include "SList.h"
#include "SError.h"

#include "misc.h" //delete

namespace SLib {
namespace SSexps { //S-Expression

void Sexps::eval() {

}

void Sexps::parseExps() {
   //I call values separated by spaces "words".
   auto h_groupWords = [](const std::string& str) -> std::vector<std::string> {
      std::vector<std::string> r_words;

      for (int i = 0; i < str.length(); i++) {
         std::string s;
         for (; str[i] != ' ' && i < str.length(); i++)
            s.push_back(str[i]);

         //check if previous is one of the quotes or ~, and concat to this s
         if (r_words.size() && (r_words[r_words.size()-1] == "~" || r_words[r_words.size()-1] == "'" || r_words[r_words.size()-1] == "`"))
            r_words[r_words.size()-1] += s;
         else
            r_words.push_back(s);
      }

      return r_words;
   };

   std::vector<std::string> vecVal = h_groupWords(val);

   if (vecVal[0] != "(")
      if (val[0] != '\'')
         if (val[0] != '`') {
            is_atom = true;
            if (isDigit(val[0]))
               for (char )


         }
         else
            is_backQuoted = true;
      else
         is_quoted = true;

   else {}

   std::vector<std::string> vectorVal = h_groupWords(val);

   int n_openParens, n_closeParens;

for (string str : vectorVal) {
      //if (str[0] == '(' || ((str[0] == '\'' || str[0] == '\`') && str[]
      //                )
   }

   //delete val;
}


int handleError(SSexps::ParseError error) {
   using SSexps::ParseError;

   switch (error) {
   case ParseError::NO_BEGIN_PARENTHESIS:
      printError(ErrorLevel::BAD_INPUT,
                 "An expression  has to start with an ' or an (",
                 SStateMachine::line,
                 SStateMachine::file);
      break;

   case ParseError::NO_END_PARENTHESIS:
      printError(ErrorLevel::BAD_INPUT,
                 "An expression has to end with an )",
                 SStateMachine::line,
                 SStateMachine::file);
      break;

   case ParseError::UNMATCHED_QUOTES:
      printError(ErrorLevel::BAD_INPUT,
                 "Unmatched quote",
                 SStateMachine::line,
                 SStateMachine::file);
      break;

   default:
      printError(ErrorLevel::FATAL_ERROR,
                 "Unkown Error has occured",
                 SStateMachine::line,
                 SStateMachine::file);
      break;

   }
}


//side effect:   if first quote character is present, changes m_start, else m_start and m_end are -1
//return value:  true if 2 quotes are found; otherwise false
bool getNextQuote(const std::string& str, int current, int& m_start, int& m_end) { //FIXME: change to return a struct of bool * start * end
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


//TODO: fix the removal of extra white spaces in strings ("     " becomes " ").
std::string formatSexps(const std::string& sexpsWithSpaces) {
   vector<char> beforeParens = {'\'', '`', '~'};
   vector<char> openParens = {'(', ')'}, closeParens = {')', ']'}; //TODO

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
         //if (i && sexps[i-1] != ' ') r_sexps.push_back(' ');
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

      //r_sexps.push_back(sexps[i]);

      if (i == m_quoteStart)
         while(i != m_quoteEnd)
            r_sexps.push_back(sexps[i++]);

      r_sexps.push_back(sexps[i]);
   }

   return h_removeExtraWhitespaces(r_sexps, 0, r_sexps.length());
}


}} //namespace

