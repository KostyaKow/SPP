#ifndef MISC_H_INCLUDE
#define MISC_H_INCLUDE

#ifdef DEBUG
#include <stdio.h>
#define BUG(str) printf("\n%s: line %d (file %s): %s\n", __FUNCTION__, __LINE__, __FILE__, str);
#else
#define BUG(s)
#endif


char getch(void);

#endif //MISC_H_INCLUDE
