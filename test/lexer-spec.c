#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parce.h"
#include "lexer.h"

int main(void) {
  TokenList token_list;

  LexemeList lexeme_list;
  lexeme_list.size = 3;
  Lexeme* lexemes = (Lexeme*)malloc(sizeof(Lexeme) * lexeme_list.size);
  lexemes[0].name = "ID";
  lexemes[0].flags = 0;
  regcomp(&lexemes[0].regex, "^[a-zA-Z]\\+$", 0);

  lexemes[1].name = "number";
  lexemes[1].flags = 0;
  regcomp(&lexemes[1].regex, "^[0-9]\\+$", 0);

  lexemes[2].name = "whitespace";
  lexemes[2].flags = 1;
  regcomp(&lexemes[2].regex, "^\\s\\+$", 0);

  lexeme_list.lexemes = lexemes;
  int lex_result = lex(lexeme_list, "Test 0123", &token_list);
  if (lex_result == LEX_SUCCESS) {
    for (int i = 0; i < token_list.size; ++i) {
      printf("Found token %s with type %s\n", token_list.tokens[i].data, token_list.tokens[i].name);
    }

    free(token_list.tokens);
  }

  free(lexemes);
  return 0;
}
