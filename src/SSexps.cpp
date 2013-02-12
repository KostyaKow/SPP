#include <string>
#include <vector>

#include "SSexps.h"
#include "SStr.h"
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

   if (val[0] != '(')
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


bool getNextQuote(const std::string& str, int current, int& m_start, int& m_end) { //FIXME: change to return a struct of bool * start * end
   if (current > str.length())
      return false;

   m_start = m_end = -1;


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

   return false; //if first quote character is present, fucks up m_start, else m_start and m_end are -1
}


//TODO: fix the removal of extra white spaces in strings ("     " becomes " ").
std::string formatSexps(const std::string& sexpsWithSpaces) {

   auto h_removeExtraWhitespaces = [](const std::string& str, int start, int end) {
      if ((end - start) < 1)
         return str;

      while (str[start] == ' ')
         start++;

      std::string r_str;

      for (int i = start; i < end; i++) {
         while (str[i] == ' ' && str[i+1] == ' ') i++;
         r_str.push_back(str[i]);
      }
      return r_str;
   };

   std::string sexps = h_removeExtraWhitespaces(sexpsWithSpaces, 0, sexpsWithSpaces.length());


   std::string r_sexps;

   int m_quoteStart, m_quoteEnd;

   for (int i = 0; i < sexps.length(); i++) {

      if (!getNextQuote(sexps, i, m_quoteStart, m_quoteEnd)) { //no more quotes
         if (m_quoteStart != -1) //FIXME: checks the modification of m_quoteStart; confusing; mutability sucks!
            throw std::runtime_error("there is a start quote (\"); but no end-quote");
         //return r_sexps;
      }

      if (i == m_quoteStart)
         while(i != m_quoteEnd)
            r_sexps.push_back(sexps[i++]);


      if (sexps[i] == '\'' || sexps[i] == '`' || sexps[i] == '~') {
         //if (i && sexps[i-1] != ' ') r_sexps.push_back(' ');
         if (sexps[i+1] == ' ') i++;
      }

      if (sexps[i] == '(' && (i+1 <= sexps.length()) && sexps[i+1] != ' ') //next
         r_sexps.push_back(' ');

      if (i && sexps[i-1] == '(') //previous
         r_sexps.push_back(' ');

      if (i && sexps[i] == ')' && sexps[i-1] != ' ')
         r_sexps.push_back(' ');

      r_sexps.push_back(sexps[i]);

   }

   return h_removeExtraWhitespaces(r_sexps, 0, r_sexps.length());
}


/*
***delete***
bool isCharInQuotes(int charPlace, const std::string& str) {
   if(charPlace >= str.length())
      throw std::runtime_error("isCharInQoutes incorrect args");

   bool quotes = false;

   for(int i = 0, c; i < str.length() && i < charPlace; c = str[i], i++)
      if(c == '"')
         quotes = !quotes;

   return quotes;
}


bool isStrInsideQuotes(int start, int end, const std::string& str) {
   if(start < 0 || end > str.length())
      throw std::runtime_error("bad args to isStrInsideQuotes");

   bool currentlyInsideQuotes = false;

   for (int i = 0; i < str.length(); i++) {
      if (str[i] == '\"') {
         currentlyInsideQuotes = !currentlyInsideQuotes;
      }
   }
}*/



}} //namespace

