#include "misc.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>

uint8_t mode;
int TAB = 0;

void error(const char* str, enum error_type how_bad) {
   printf("\n\terror occured: %s\n\texiting...\n", str);
   exit(-1);
}

void printcnf(char c, int n, const char* str) { //print character c n times, before printing str
   while (n > 0) {
      printf("%c", c);
      n--;
   }
   printf("%s", str);
}



char* str_cpy(const char* str, int len) {
   len = (len == 0) ? strlen(str) : len;

   char* new_str = (char*)malloc(sizeof(char) * (len + 1));

   for (int i = 0; i < len && str[i] != '\0'; i++)
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
inline char getch(void) {
     return getch_(0);
}

//Read 1 character with echo
inline char getche(void) {
     return getch_(1);
}

/*inline void print_sexps(struct Sexps* sexps) {
   _print_sexps(sexps, 0);
}

void _print_sexps(struct Sexps* sexps, int nesting_level) {
   BUG_PRINT("printing sexps!!!");
   if (sexps == NULL)
      error("Null pointer passed to _print_sexps", NULL_PTR);

   char str[100]; //for output

   sprintf(str, "\nnumber of sexps: %i; size for array: %i", sexps->sub_sexps_len, sexps->size_sub_sexps);
   printcnf('\t', nesting_level, str);

   if (sexps->atom) {
      printcnf('\t', nesting_level, "atom of type ");
      switch (sexps->type) {
         case SEXPS_INT:
           printf("int with value: %i", *(int*)sexps->val);
         break;
         case SEXPS_FLOAT:
            printf("float with value: %F", *(float*)sexps->val);
         break;
         case SEXPS_CHAR:
            printf("char with value: %c", *(char*)sexps->val);
         break;
      }
      char str[5]; sprintf(str, "\nstr_len: %i", sexps->str_val_len);
      printcnf('\t', nesting_level, str);
   }
   else {
      int i;
      for (i = 0; i < sexps->sub_sexps_len; i++)
         _print_sexps(sexps->sub_sexps[i], nesting_level + 1);

      printcnf('\t', nesting_level, "\nsexps: ");
      printf("%s", sexps->str_val);
   }
}*/
