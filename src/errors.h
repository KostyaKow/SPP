#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED

#include "misc.h"

enum error { NO_ERROR, ERROR_INIT, WARNING_INIT };

bool handle_error(error error_code);

#endif // ERRORS_H_INCLUDED
