#ifndef SEXPS_H_INCLUDE
#define SEXPS_H_INCLUDE

#include "lexer.h"
#include "list.h"
#include "errors.h"

typedef struct sexps {
   struct sexps **sexps;
} sexps_t;


error_e parse_sexps(sexps_t* sexps_RETURN, const source_code_t* src);

#endif //SEXPS_H_INCLUDE
