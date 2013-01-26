#include "SError.h"

#include "SStateMachine.h"

namespace SLib {
namespace SError {

void printError(ErrorLevel level,
                std::string msg,
                int lineNumber,
                std::string fileName) {

    std::string levelStr;
    switch(level) {
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

int handleError(SSexps::ParseError error) {
    switch (error) {
        case SSexps::ParseError::NO_BEGIN_PARENTHESIS:
            printError(ErrorLevel::BAD_INPUT,
                       "An expression  has to start with an ' or an (",
                       SStateMachine::line,
                       SStateMachine::file);
        break;

        case SSexps::ParseError::NO_END_PARENTHESIS:
            printError(ErrorLevel::BAD_INPUT,
                       "An expression has to end with an )",
                       SStateMachine::line,
                       SStateMachine::file);

    }
}

}} //namespace
