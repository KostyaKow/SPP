#include <iostream>

#include "SError.h"
#include "SStateMachine.h"

namespace SLib {
namespace SError {

void printError(ErrorLevel level,
                std::string msg,
                int lineNumber,
                std::string fileName) {

   std::string levelStr;

   switch (level) {
   case ErrorLevel::FATAL_ERROR:   levelStr = "fatal error";           break;
   case ErrorLevel::BAD_INPUT:     levelStr = "incorrect input";       break;
   case ErrorLevel::WARNING:       levelStr = "warning";               break;
   default:                        levelStr = "unkown error level";    break;
   }

   std::cout << "\n";

   if (!fileName.empty())
      std::cout << fileName << ":: ";

   if (lineNumber)
      std::cout << lineNumber << ": ";

   std::cout << levelStr << " - " << msg;
}

}
} //namespace
