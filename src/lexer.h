#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

typedef struct lexeme {
    enum { STRING, CHAR, NUM } type;

    void *val, *str_val;
};

typedef struct lex_table {
   const char* str_val; int str_val_len;

   void* val;

   uint8_t type;
   bool atom;
   bool single_sexps;

   struct Sexps** sub_sexps;

   uint16_t size_sub_sexps, sub_sexps_len;
} lex_table;


char* remove_comments(const char* str);

lex_table* format_sexps(const char* str, size_t length) {

}


#endif // LEXER_H_INCLUDED
