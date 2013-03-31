#ifndef SLIST_H_INCLUDED
#define SLIST_H_INCLUDED

#include "SError.h"

#include <vector>
#include <iostream>
#include <functional>

//TODO: Make a separate generic library for this kind of stuff?

/*
usage for list:

cout << list( 1, 5)
> [1, 2, 3, 4, 5]

cout << list(1.2, 2.2

list('z', 'x' __ 'a');
>letters 'z' to 'a', using x as a step value
*/

#define __ ,

template <class T, class Y = T, class Z = T>
std::vector<T> list(T start, Y end_or_step, Z end_or_invalid = Exception::invalid<Z>::val) {
   std::vector<T> val;

   T step, end;

   if (end_or_invalid == Exception::invalid<Z>::val) {  //if only passed 2 variables
      end = end_or_step;

      if( end > start)
         step = 1;
      else step = -1;
   }
   else { //if passed step as end_or_step
      end = end_or_invalid;

      if (end > start)
         step = (end_or_step-start);
      else
         step = -(start-end_or_step);
   }

   for (T i = start; (start < end) ? i <= end : i >= end; i+=step)
      val.push_back(i);

   return val;
}

template <class T>
std::ostream& operator <<(std::ostream& os, const std::vector<T>& n) {
   if (n.empty())
      return os;

   os << "[";
   os << n[0];

   for (auto i = n.begin()+1; i != n.end(); ++i)
      os << ", " << *i;

   os << "]\n";

   return os;
}

template <class T>
std::vector<T> filter(std::function<bool(T)> pred, std::vector<T> list) {
   std::vector<T> filteredList;

for (auto n : list)
      if (pred(n))
         filteredList.push_back(n);

   return filteredList;
}


template <class T>
bool elem(T element, std::vector<T> list) {
for (T i : list)
      if (i == element)
         return true;

   return false;
}


#endif // SLIST_H_INCLUDED


