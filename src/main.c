#include "config.h"
#include "misc.h"
#include "sexps.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(void) {
   while (true) {
      printf("\n\n************************\nenter stuff: ");

      char str[100];
      scanf("%s", str);

      print_sexps(parse_sexps(str, 0));
   }

   return 0;
}

