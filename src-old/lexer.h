#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include "errors.h"
#include "list.h"

typedef enum lexeme_t_type { IDENTIFIER, NUM, STR, CHAR, PAREN } lexeme_t_type_e;

typedef struct {
   lexeme_t_type_e type;

   char *value;
   uint8_t len;

   struct list_head list;

} lexeme_t;

//specific instance of input
typedef struct source_code {
   char *str;
   int len;

   lexeme_t lexemes;

} source_code_t;


error_e lex_analyze(source_code_t* src_RETURN, const char *str, int len);

inline error_e remove_comments(char *str) {
    return NO_ERROR;
}




#endif // LEXER_H_INCLUDED
