#ifndef lexer_h
#define lexer_h

#include <string.h>
#include "parce.h"

extern int lex(LexemeList lexeme_list, char* stream, TokenList* token_stream);

#endif
