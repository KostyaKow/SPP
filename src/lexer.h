#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include "list.h"

#include "misc.h"
#include "errors.h"

typedef enum lexeme_t_type { IDENTIFIER, NUMBER, STRING, CHAR, PAREN } lexeme_t_type_e;

typedef struct {
   lexeme_t_type_e type;

   char *value;
   uint8_t len;

   struct list_head list;

} lexeme_t;


//if a REPL is running, or there is multiple files, this will store each input set
//TODO: if there is no extra info, why not just use char** instead of all this?
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
