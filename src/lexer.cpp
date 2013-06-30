#include "lexer.h"

char* remove_comments(const char* str) {
    return str;
}


int* _get_next_quotes(const char* str, size_t len, int i);
int _increment_counter(const char* str, size_t len, int i, bool init);
