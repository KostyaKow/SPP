#ifndef MISC_H_INCLUDE
#define MISC_H_INCLUDE

#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "config.h"

enum error_type { BAD_INPUT, BAD_PAREN, NULL_PTR };

char getch(void);
void error(const char* str, enum error_type how_bad);
bool isDigit(char c);
bool isLetter(char c);
char* str_cpy(const char* str, int len); //returns a new string with len number of characters from str

void printcnf(char c, int n, const char* str);

//void _print_sexps(struct Sexps* sexps, int nesting_level);
//void print_sexps(struct Sexps* sexps);


//BUG prints out messages passed to it, and additional info
//BUG_PRINT only prints what you tell it to print
//versions with _ wait for user to press a key before continueing
//versions with LVL only print messages with appropriate debug level

//TODO: print to stderr, not stdout
#ifdef DEBUG
   extern int TAB;

   #define T do { printf("\n"); for (int i = 0; i < TAB; i++) printf(" "); } while (0)

   #include <stdio.h>
   #include <string.h>
   //%% instead of /% when escaping in printf
   #define _helper_BUG(str, ...) \
   do { \
      char _stuff[1000]; \
      sprintf(_stuff, "%s: line %d (file %s): %s%%c", __FUNCTION__, __LINE__, __FILE__, str); \
      printf(_stuff, __VA_ARGS__); \
   } while (0)

   #define BUG(...)                 do { T; _helper_BUG(__VA_ARGS__, ' '); } while (0)
   #define BUG_PRINT(...)           do { T; printf(__VA_ARGS__); } while(0)

   #define BUG_PRINTN(str, n)       do { for (int i = 0; i < n; i++) printf("%c", str[i]); } while(0)
   #define BUGN(str, n)             do { _helper_BUG("", ' '); BUG_PRINTN(str, n); } while (0)

   #define BUG_LVL(lvl, ...)        do { if (lvl <= DEBUG) BUG(__VA_ARGS__); } while (0)
   #define BUG_PRINT_LVL(lvl, ...)  do { if (lvl <= DEBUG) BUG_PRINT(__VA_ARGS__); } while (0)

   #define BUG_PRINTN_LVL(lvl, ...) do { if (lvl <= DEBUG) BUG_PRINTN(__VA_ARGS__); } while (0)
   #define BUGN_LVL(lvl, ...)       do { if (lvl <= DEBUG) BUGN(__VA_ARGS__); } while (0)

#else
   #define BUG(...)
   #define BUG_PRINT(...)
   #define BUG_PRINTN(str, n)
   #define BUGN(str, n)
   #define BUG_LVL(lvl, ...)
   #define BUG_PRINT_LVL(lvl, ...)

   #define BUG_PRINTN_LVL(lvl, ...)
   #define BUGN_LVL(lvl, ...)
#endif

#endif //MISC_H_INCLUDE
