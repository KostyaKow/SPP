#ifndef MISC_H_INCLUDE
#define MISC_H_INCLUDE

char getch(void);

#define SCONVERT(str_name, n, ...) char str_name[n]; sprintf(str_name, __VA_ARGS__);

//is there a good reason no-one tabs defines???
#ifdef DEBUG
   #include <stdio.h>
   #define BUG(str) printf("\n%s: line %d (file %s): %s\n", __FUNCTION__, __LINE__, __FILE__, str)
   #define BUG_(str) do { BUG(str); getch(); } while (0) //with getch
#else
   #define BUG(s)
   #define BUG_(s)
#endif

#endif //MISC_H_INCLUDE
