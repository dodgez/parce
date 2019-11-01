#ifndef lexer_h
#define lexer_h

#include <stdlib.h>
#include <string.h>
#include "parce.h"

extern int lex(LexemeStream lexeme_stream, char* stream, TokenStream* token_stream);

#endif
