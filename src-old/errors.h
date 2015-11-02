#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED

#include <stdbool.h>

typedef enum error
   { NO_ERROR, ERROR_INIT, WARNING_INIT, ERROR_QUOTES_WITHOUT_PARENTHESIS,
     ERROR_SINGLE_DOUBLE_QUOTE
   } error_e;

bool handle_error(error_e error_code, const char* msg);

static inline bool E(error_e error_code) {
   return handle_error(error_code, "unknown");
}

#endif // ERRORS_H_INCLUDED
