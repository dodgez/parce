#ifndef parser_h
#define parser_h

#include "parce.h"

Token getTokenFromStream(TokenStream token_stream);
int streamIsEOF(TokenStream token_stream);

int matchesLexeme(Lexeme lexeme, TokenStream token_stream);
int matchesRule(Rule rule, TokenStream token_stream);

extern int parse(Rule rule, TokenStream token_stream, ASTNode* root);

#endif
