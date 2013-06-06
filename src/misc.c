#include "misc.h"

#include <stdlib.h>
#include <stdio.h>
#include <termios.h>

void error(const char* str, enum error_type how_bad) {
   printf("\n\terror occured: %s\n\texiting...\n", str);
   exit(-1);
}

void free(void* ptr) {
   ptr = realloc(ptr, 0); //"ptr = " to shut up gcc
}

bool isDigit(char c) {
   return c >= '0' && c <= '9';
}

char* str_cpy(const char* str, int len) {
   len = (len == 0) ? strlen(str) : len;

   char* new_str = (char*)malloc(sizeof(char) * (len + 1));

   int i;
   for (i = 0; i < len && str[i] != '\0'; i++)
      new_str[i] = str[i];

   new_str[len] = '\n';

   return new_str;
}


static struct termios old, new;

//Initialize new terminal i/o settings
void initTermios(int echo) {
   tcgetattr(0, &old); //grab old terminal i/o settings
   new = old; //make new settings same as old settings
   new.c_lflag &= ~ICANON; // disable buffered i/o
   new.c_lflag &= echo ? ECHO : ~ECHO; //set echo mode
   tcsetattr(0, TCSANOW, &new); //use these new terminal i/o settings now
}

//Restore old terminal i/o settings
void resetTermios(void) {
     tcsetattr(0, TCSANOW, &old);
}

// Read 1 character - echo defines echo mode
char getch_(int echo) {
   char ch;
   initTermios(echo);
   ch = getchar();
   resetTermios();
   return ch;
}

//Read 1 character without echo
char getch(void) {
     return getch_(0);
}

//Read 1 character with echo
char getche(void) {
     return getch_(1);
}
