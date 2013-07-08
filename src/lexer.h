#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include "list.h"

#include "misc.h"
#include "errors.h"

typedef enum lexeme_t_type { IDENTIFIER, NUM, STR, CHAR, PAREN } lexeme_t_type_e;

typedef struct {
   lexeme_t_type_e type;

   char *value;
   uint8_t len;

   struct list_head list;

} lexeme_t;

//TODO move lexeme_t to source
typedef struct {
   char *str;
   int len;

   struct list_head list;

} source_code_t;


///
typedef struct {
   source_code_t   src;
   lexeme_t        lexemes;

} lex_table_t;
///

error_e lex_table_add(const char *str, int len);

inline error_e remove_comments(char *str) {
    return NO_ERROR;
}

extern lex_table_t lex_table;


#endif // LEXER_H_INCLUDED
