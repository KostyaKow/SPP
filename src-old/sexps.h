#ifndef SEXPS_H_INCLUDE
#define SEXPS_H_INCLUDE

#include "lexer.h"
#include "list.h"
#include "errors.h"

/* sexps are stored like this:
 *   ((this) (sexps))
 *    /         \
 * sexps[0]   sexps[1]
 ******************************/


typedef struct sexps {
   struct sexps *sub_sexps;
   int num_sub_sexps;


} sexps_t;


error_e parse_sexps(sexps_t* sexps_RETURN, const source_code_t* src);
error_e eval_sexps();

#endif //SEXPS_H_INCLUDE
