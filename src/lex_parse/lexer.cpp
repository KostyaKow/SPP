#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

typedef const string& string;

//returns a list [a..b]; ex: list(1,5) = {1,2,3,4,5}. useful for loops..
vector<int> list(int a, int b) {
   vector<int> vec;
   if (a < b) {
      while (a < b)
         vec.push_back(a++);
   }
   else {
      while (b < a)
         vec.push_back(b++);
   }
   return vec;
}


class Lexer {
public:
   //regular regex interface for users of the class
   typedef pair<
                string,
                function<void(void)>
               > Regex; 
private:
   struct Regex__internal {
      function<int(string, place)> test; //returns 0 if no match...
      function<void(void)>   action;
   };

   Regex__internal makeRegex__internal(Regex _regex) {
      Regex__internal regex;
      regex.first = _regex.first;
       
      for (char c : _regex.first) {
         
      } 
   }

   vector<Regex__internal> regexes;

public:

   Lexer(const vector<Regex>& _regexes = {})
      : str(_str)
   {
      for (auto reg : _regexes)
         regexes.push_back(makeRegex__internal(reg));
   }

   void add_regex(const Regex& regex) {
      regexes.push_back(makeRegex__internal(regex));
   }

   void add_regexes(const vector<Regex>& _regexes) {
      for (auto regex : _regexes)
         regexes.push_back(makeRegex__internal(regex));
   }
   
   void run(string str) {
      int i = 0;
      for (auto regex : regexes) {
         regex.test(i
         for (auto i : list(0, str.length())) {
            if (regex.test(str, i)
         }
      }
   }

};


int main() {
   
}
