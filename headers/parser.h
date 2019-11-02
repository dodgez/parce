#ifndef parser_h
#define parser_h

#include "parce.h"

int matchesLexeme(Lexeme lexeme, TokenList token_list, int index);
int matchesRule(Rule rule, TokenList token_list, int index);

extern int parse(RuleList rule_list, TokenList token_stream, ASTNode* root);

#endif
