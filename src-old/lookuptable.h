#ifndef LOOKUPTABLE_H_INCLUDED
#define LOOKUPTABLE_H_INCLUDED

#include "sexps.h"
#include "lexer.h"
#include "errors.h"

typedef struct {
   source_code_t  src;
   sexps_t        sexps;

   struct list_head list;

} lookup_table_t;

extern lookup_table_t lookup_table;

error_e lookup_table_add(const char *str, int len);

#endif // LOOKUPTABLE_H_INCLUDED
