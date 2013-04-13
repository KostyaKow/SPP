#ifndef MISC_H_INCLUDE
#define MISC_H_INCLUDE

#ifdef DEBUG
#include <stdio.h>
#define BUG printf("\nline %d (file %s)\n", __LINE__, __FILE__); //TODO: change to line number
#else
#define BUG
#endif

#endif //MISC_H_INCLUDE
