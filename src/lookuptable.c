#include "lookuptable.h"
#include "misc.h" //BUG stuff

lookup_table_t lookup_table;

error_e lookup_table_add(const char *str, int len) {
   lookup_table_t* tmp = malloc(sizeof(lookup_table_t));
   list_add(&tmp->list, &lookup_table.list);

   error_e err = NO_ERROR;

   err = lex_analyze(&tmp->src, str, len);
   if (err != NO_ERROR)
      goto cleanup;

   err = parse_sexps(&tmp->sexps, &tmp->src);
   if (err != NO_ERROR)
      goto cleanup;

   TAB=1;BUG_PRINT_LVL(20, "successfully added input to lookup_table\n\n");

   return err;
cleanup:;
   free(tmp);
   return err;
}
