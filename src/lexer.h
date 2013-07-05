#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include "misc.h"
#include "errors.h"

typedef struct lexeme {
   enum { IDENTIFIER, NUMBER, STRING, CHAR };

    void *val, *str_val;
} lexeme_t;

typedef struct lex_table {
   const char* str_val; int str_val_len;

   void* val;

   uint8_t type;
   bool atom;
   bool single_sexps;

   list* lexemes;

   uint16_t size_sub_sexps, sub_sexps_len;
} lex_table_t;

extern lex_table_t* lex_table;

error lex_table_add(const char* str, int len);

inline char* remove_comments(const char* str) {
    return (char*)str;
}


#endif // LEXER_H_INCLUDED
