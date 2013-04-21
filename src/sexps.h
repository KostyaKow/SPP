#ifndef SEXPS_H_INCLUDE
#define SEXPS_H_INCLUDE

#include "config.h"

#include "misc/types.h"
#include "string.h"

enum error_type { BAD_INPUT, BAD_PAREN, NULL_PTR };
enum sexps_type { SEXPS_INT, SEXPS_FLOAT, SEXPS_CHAR }; 


struct Sexps {
   const char* str_val; int str_val_len;

   void* val;
   
   byte_t type;
   bool_t atom;

   struct Sexps** sub_sexps;

   uint_t size_sub_sexps, sub_sexps_len;
};


struct Sexps* parse_sexps(const char* sexps, size_t len);
int* _get_next_quotes(const char* str, size_t len, int i);
int _increment_counter(const char* str, size_t len, int i, bool_t init);
void error(const char* str, enum error_type how_bad);

#endif //SEXPS_H_INCLUDE
