#ifndef SERROR_H_INCLUDED
#define SERROR_H_INCLUDED

#include <string>

namespace SLib {
namespace SError {

///use std::runtime_error(std::string msg)

//bool indicates if the error is fatal.
//0 -- terminate program
//1 -- redo the last action with different input
//2 -- warning, but nothing serious. Continue execution

enum class ErrorLevel { FATAL_ERROR, BAD_INPUT, WARNING };

void printError(ErrorLevel level = ErrorLevel::FATAL_ERROR,
                std::string msg = "DefaultError",
                int lineNumber = 0,
                std::string fileName = "");


//BAD IDEA! TM

//Metaprogramming to the rescue!
template <class T>
class invalid {};

template <>
struct invalid <int> {
   //static operator int() const { return 9999999; }
   constexpr static int val = (int)999999999;
};

template <>
struct invalid <char> {
   constexpr static char val = 0;
};

template <>
struct invalid <float> {
   constexpr static float val = 42.16691234;
};

}} //namespace

#endif // SERROR_H_INCLUDED
