#ifndef MISC_H_INCLUDE
#define MISC_H_INCLUDE

#include "../config.h"
#include "types.h"

enum error_type { BAD_INPUT, BAD_PAREN, NULL_PTR };

char getch(void);
void error(const char* str, enum error_type how_bad);
void free(void* ptr);
bool_t isDigit(char c);
char* str_cpy(const char* str, int len);


//is there a good reason no-one tabes defines???
#ifdef DEBUG
   #include <stdio.h>
   #define _helper_BUG(str, ...) do { \
      char _stuff[1000]; sprintf(_stuff, "\n%s: line %d (file %s): %s\%c", __FUNCTION__, __LINE__, __FILE__, str); \
      printf(_stuff, __VA_ARGS__); \
   } while (0)

   #define BUG(...) do { _helper_BUG(__VA_ARGS__, ' '); } while (0)

   #define BUG_(...) do { BUG(__VA_ARGS__); getch(); printf("\n"); } while (0) //with getch
   #define BUG_PRINT(...) do { printf("\n"); printf(__VA_ARGS__); } while(0)
   #define BUG_PRINT_(...) do { printf("\n"); printf(__VA_ARGS__); getch(); } while(0)

#else
   #define BUG(...)
   #define BUG_(...)
   #define BUG_PRINT(...)
   #define BUG_PRINT_(...)
#endif

#endif //MISC_H_INCLUDE
