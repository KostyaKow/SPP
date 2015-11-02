#ifndef CONFIG_H_INCLUDE
#define CONFIG_H_INCLUDE

//DEBUG (from 0 to 100) defines the volume of messages the program prints (0 being
//not-printing anything from stderr and 100 printing everything that's going on;
//suggested level for users is 10; for developers 20)
#define DEBUG 50

#ifdef __GNUC__
#define likely(x)    __builtin_expect((x),1)
#define unlikely(x)  __builtin_expect((x),0)
#else
#define likely(x)    (x)
#define unlikely(x)  (x)
#endif

#include <stdbool.h>

#endif //CONFIG_H_INCLUDE
