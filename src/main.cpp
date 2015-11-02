/*
//functions & predefined stuff
+ - / =
list, car, cdr, cons, length
null //empty list

//random syntax
(+ 3 5)
(lambda (x y) (+ x y))
(def x val)
(if (x) a b)

1. input string
3. interpret :: string -> session -> sexpr --modifies Session so maybe copy it
      lex :: string -> [string]
      parse :: [string] -> sexps
      eval :: sexps -> session -> sexps

*/

#include <iostream>
#include <vector>
using namespace std;

typedef vector<string> stringvec;
typedef const string& cstring;
typedef const stringvec& cstringvec;

bool isNum(char c) {
   return c >= 48 && c <=57;
}
bool isNum(cstring s) {
   for (auto c : s) {
      if (!isNum(c))
         return false;
   }
   return true;
}

stringvec lex(cstring s) {
   stringvec lexemes;
   string currLex;

   for (auto c : s) {
      if (c == ' ') {
         if (!currLex.empty()) {
            lexemes.push_back(currLex);
            currLex = "";
         }
      }
      else if (c == '(' || c == ')') {
         string s(1, c);
         lexemes.push_back(s);
      }
      else
         currLex += c;
   }
   return lexemes;
}

enum class SexpsType {
   SEXPS, NUM, VAR, NONE
};

struct Sexpr {
   SexpsType t;
   //void* v; //value either string or vector<Sexpr>
   union {
      string* s;
      vector<Sexpr>* v;
   };

   Sexps() : t(NONE) {}
};

struct Session {};

Sexps parse(cstring lex) {
   Sexps s;
   if (isNum(lex)) {
      s.t = SexpsType::NUM;
      s.v = new string;
      *s.v = lex;
   }
}

Sexps parse(cstringvec lexemes) {
   Sexps s;

   if (lexemes.length() == 1)
      return parse(lexemes[0]);

   for (int i = 0; i < lexemes.length(); i++) {
      string lex = lexemes[i];

      if (lex == "(") {
         s.t = SexpsType::SEXPS;
         s.v = new vector<Sexps>;

         stringvec sub;
         for (; i < lexemes.length(); i++) {
            lex = lexemes[i];
            if (lex == ")")
               break;
            //else sub.push_back(lex);
            s.v->push_back(parse(lex));
         }
         //s.v->push_back()
      }
   }
}

Sexpr eval(Sexpr sexps, Session& session) {}

sexpr interpret(cstring s, Session& session) {
   stringvec lexemes = lex(s);

   Sexpr s = parse(lexemes);
   return eval(s, session);
}

int main() {
   string s = "(+ 3   5     ";
   Session session;
   auto a = interpret(s);


   /*Session session;

   while (true) {
      string s;
      cin >> s;
      sexps s = interpret(s, session);
      //now define $n as what we got back
   }*/
}
