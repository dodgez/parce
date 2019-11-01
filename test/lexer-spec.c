#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parce.h"
#include "lexer.h"

int main(void) {
  TokenStream token_stream;

  LexemeStream lexeme_stream;
  lexeme_stream.size = 3;
  Lexeme* lexemes = (Lexeme*)malloc(sizeof(Lexeme) * lexeme_stream.size);
  lexemes[0].name = "ID";
  lexemes[0].options = 0;
  regcomp(&lexemes[0].regex, "^[a-zA-Z]\\+$", 0);

  lexemes[1].name = "number";
  lexemes[1].options = 0;
  regcomp(&lexemes[1].regex, "^[0-9]\\+$", 0);

  lexemes[2].name = "whitespace";
  lexemes[2].options = 1;
  regcomp(&lexemes[2].regex, "^\\s\\+$", 0);

  lexeme_stream.lexemes = lexemes;
  int lex_result = lex(lexeme_stream, "Test 0123", &token_stream);
  if (lex_result == LEX_SUCCESS) {
    for (int i = 0; i < token_stream.size; ++i) {
      printf("Found token %s with type %s\n", token_stream.tokens[i].data, token_stream.tokens[i].name);
    }

    free(token_stream.tokens);
  }

  free(lexemes);
  return 0;
}
