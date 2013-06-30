#ifndef MISC_H_INCLUDE
#define MISC_H_INCLUDE

#include "config.h"
#include "sexps.h"

#include <stdint.h>

enum error_type { BAD_INPUT, BAD_PAREN, NULL_PTR };

char getch(void);
void error(const char* str, enum error_type how_bad);
void free(void* ptr);
bool isDigit(char c);
char* str_cpy(const char* str, int len); //returns a new string with len number of characters from str

void printcnf(char c, int n, const char* str); //print character c n times, before printing str
void _print_sexps(struct Sexps* sexps, int nesting_level);

void print_sexps(struct Sexps* sexps);


//is there a good reason no-one tabes defines???
//TODO: print to stderr, not stdout
#ifdef DEBUG
   #include <stdio.h>
   #include <string.h>
   //%% instead of /% when escaping in printf
   #define _helper_BUG(str, ...) \
   do { \
      char _stuff[1000]; \
      sprintf(_stuff, "\n%s: line %d (file %s): %s%%c", __FUNCTION__, __LINE__, __FILE__, str); \
      printf(_stuff, __VA_ARGS__); \
   } while (0)

   #define BUG(...)        do { _helper_BUG(__VA_ARGS__, ' '); } while (0)
   #define BUG_(...)       do { BUG(__VA_ARGS__); getch(); printf("\n"); } while (0) //with getch

   #define BUG_PRINT(...)  do { printf("\n"); printf(__VA_ARGS__); } while(0)
   #define BUG_PRINT_(...) do { printf("\n"); printf(__VA_ARGS__); getch(); } while(0)

#else
   #define BUG(...)
   #define BUG_(...)
   #define BUG_PRINT(...)
   #define BUG_PRINT_(...)
#endif

#endif //MISC_H_INCLUDE
