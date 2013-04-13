#ifndef SEXPS_H_INCLUDE
#define SEXPS_H_INCLUDE

struct Sexps {
   char* str_val;
   void* val;

   struct Sexps *sub_sexps;

};

struct Sexps* parse_sexps(const char* sexps);

unsigned int* _get_next_quotes(const char* str, int i);


#endif //SEXPS_H_INCLUDE
