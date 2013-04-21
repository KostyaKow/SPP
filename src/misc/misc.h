#ifndef MISC_H_INCLUDE
#define MISC_H_INCLUDE

#include "../config.h"

char getch(void);

//is there a good reason no-one tabed defines???
#ifdef DEBUG
   #include <stdio.h>
   #define BUG(str) printf("\n%s: line %d (file %s): %s", __FUNCTION__, __LINE__, __FILE__, str)
   #define BUG_(str) do { BUG(str); getch(); printf("\n"); } while (0) //with getch
#else
   #define BUG(s) printf("no DEBUG defined") //gotta do #define DEBUGGIN_DEBUG xD
   #define BUG_(s) BUG(s)
#endif

#endif //MISC_H_INCLUDE
