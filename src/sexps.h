#ifndef SEXPS_H_INCLUDE
#define SEXPS_H_INCLUDE

#include "misc.h"

enum sexps_type { SEXPS_INT, SEXPS_FLOAT, SEXPS_CHAR };


struct Sexps {
   const char* str_val; int str_val_len;

   void* val;

   uint8_t type;
   bool atom;
   bool single_sexps;

   struct Sexps** sub_sexps;

   uint16_t size_sub_sexps, sub_sexps_len;
};


struct Sexps* parse_sexps(const char* sexps, size_t len);
int* _get_next_quotes(const char* str, size_t len, int i);
int _increment_counter(const char* str, size_t len, int i, bool init);

#endif //SEXPS_H_INCLUDE
