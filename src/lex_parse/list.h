#ifndef LIST_H_INCLUDE
#define LIST_H_INCLUDE

#include "config.h"

//returns a list [a..b]; ex: list(1,5) = {1,2,3,4,5}. useful for loops
template <class T>
vector<T> list(T a, T b) {
   vector<T> vec;
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

//TODO: is it possible to memcpy?
template <class T>
vector<T> addLists(vector<T> a, vector<T> b) {
   a.resize(a.size() + b.size());
   for (T x : b)
      a.push_back(x);
}

#endif // LIST_H_INCLUDE
