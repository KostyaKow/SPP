#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED

#include "misc.h"

typedef enum error { NO_ERROR, ERROR_INIT, WARNING_INIT } error_e;

bool handle_error(error_e error_code, const char* msg);

inline bool E(error_e error_code) {
   return handle_error(error_code, "unknown");
}

#endif // ERRORS_H_INCLUDED
