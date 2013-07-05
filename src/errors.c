#include "errors.h"

bool handle_error(error error_code, const char* msg) {
   switch (error_code) {
   case ERROR_INIT:
      printf("\nerror: could not initialize!");
      return true;
      break;

   case WARNING_INIT:
      printf("\nwarning during initialization");
      return false;
      break;

   case NO_ERROR:
      return false;
      break;

   default:
      printf("\nunknown error has occured...\ntrying to continue execution");
      return false;
   }
}
