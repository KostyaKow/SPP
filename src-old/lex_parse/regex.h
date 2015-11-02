#ifndef REGEX_H_INCLUDE
#define REGEX_H_INCLUDE

#include <assert.h>

#include "config.h"
#include "list.h"

//TODO: for some of the cases, give a user error instead of using assert.
#define docheck(n) assert(i + n < reg.length());

class Regex {
   String reg;

   void _Regex() {

      struct Match {
         enum class Type { DOT, START_POS, END_POS, STAR, //Posix
                           QUESTION_MARK, PLUS, PIPE, CIGAR, //extended Posix
                           CHAR_CLASS, ALL, NOT_ALL, ANY, NOT_ANY };
         //bool range; //a-z 1-9
         Type type;
         vector<char> vals;
      };

      vector<Match> matches;

      //loop all the characters and break them up into matches
      for (uint16_t i = 0; i < reg.length(); i++) {
         Match m;
         m.type = Match::Type::ANY;
         //m.range = false;

         if (reg[i] == '.')
            m.type = Match::Type::DOT;
         else if (reg[i] == '^')
            m.type = Match::Type::START_POS;
         else if (reg[i] == '$')
            m.type = Match::Type::END_POS;
         else if (reg[i] == '*')
            m.type = Match::Type::STAR;
         else if (reg[i] == '?')
            m.type = Match::Type::QUESTION_MARK;
         else if (reg[i] == '+')
            m.type = Match::Type::PLUS;
         else if (reg[i] == '|')
            m.type = Match::Type::PIPE;

         //TODO: handle all escaped chars
         else if (reg[i] == '\\') {
            docheck(1)
            m.vals.push_back(reg[i+1]);
         }
         //first check for scecial characters, and then run look for the rest
         else if (reg[i] == '[') {
            i++;
            docheck(0)

            if (reg[i] == '^')
               m.type = Match::Type::NOT_ANY;
            else if (reg[i] == ':') //TODO:implement
               m.type = Match::Type::CHAR_CLASS;
            else if (reg[i] == ']' || reg[i] == '-')
               m.vals.push_back(reg[i]);
            else //normal character
               i--;
            for (++i; reg[i] != ']'; i++) {
               docheck(1)
               if (reg[i+1] == '-') {
                  docheck(2)
                  addLists<char>(m.vals, list<char>(reg[i], reg[i+2])); //range = true; m.vals.push_back(reg[i], reg[i+2]);
                  i += 2; //char-char
               }
               else
                  m.vals.push_back(reg[i]);
            }
         }
         else if (reg[i] == '(') {
            //TODO what if previous \ is actually \\ also, check for ending better
            for (; reg[i-1] != '\\' && reg[i] != ')'; i++) {
               docheck(0)
               m.vals.push_back(reg[i]);
            }
         }
         else
            throw("not implemented");

         matches.push_back(m);
      }


      match = [&](String s) -> string {
         string ret;

         if (matches[0].type == Match::Type::DOT || //check for stuff that access previous element and do something about them...

         for (int matchNum = 0, i = 0; i < s.size() && matchNum < matches.size(); i++) {
            switch (matches[i].type) {
            case Match::Type::DOT:
               ;
            break;

            case
            }
         }

      };
   }

public:
   function <string(String)> match;

   Regex(const Regex& other)
      : match(other.match), reg(other.reg)
   {}

   Regex(const char* reg)
      : reg(string(reg))
   {
      _Regex();
   }
   Regex(String _reg)
      : reg(_reg)
   {
      _Regex();
   }


   //check if str is good regex
   static bool isRegex(String str) {
      return true;
   }
};


#endif // REGEX_H_INCLUDE
