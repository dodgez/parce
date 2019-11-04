#include <stdlib.h>
#include <string.h>

#include "parce.h"
#include "lexer.h"
#include "expect.h"

void test_single_token(void) {
  TokenStream token_stream;

  LexemeList lexeme_list;
  lexeme_list.size = 1;
  Lexeme* lexemes = (Lexeme*)malloc(sizeof(Lexeme) * lexeme_list.size);
  memset(lexemes, 0, sizeof(Lexeme) * lexeme_list.size);
  lexemes[0].name = "ID";
  lexemes[0].flags = 0;
  regcomp(&lexemes[0].regex, "^[a-zA-Z]\\+$", 0);

  lexeme_list.lexemes = lexemes;
  int lex_result = lex(lexeme_list, "Test", &token_stream);
  if (expect_equal_int(lex_result, LEX_SUCCESS) == TEST_FAILED) return;
  if (expect_equal_str(token_stream.tokens[0].name, "ID") == TEST_FAILED) return;
  if (expect_equal_str(token_stream.tokens[0].data, "Test") == TEST_FAILED) return;

  free(token_stream.tokens);
  free(lexemes);
}

void test_adjacent_tokens(void) {
  TokenStream token_stream;

  LexemeList lexeme_list;
  lexeme_list.size = 2;
  Lexeme* lexemes = (Lexeme*)malloc(sizeof(Lexeme) * lexeme_list.size);
  memset(lexemes, 0, sizeof(Lexeme) * lexeme_list.size);
  lexemes[0].name = "ID";
  lexemes[0].flags = 0;
  regcomp(&lexemes[0].regex, "^[a-zA-Z]\\+$", 0);
  lexemes[1].name = "NUM";
  lexemes[1].flags = 0;
  regcomp(&lexemes[1].regex, "^[0-9]\\+$", 0);

  lexeme_list.lexemes = lexemes;
  int lex_result = lex(lexeme_list, "Test123", &token_stream);
  if (expect_equal_int(lex_result, LEX_SUCCESS) == TEST_FAILED) return;
  if (expect_equal_str(token_stream.tokens[0].name, "ID") == TEST_FAILED) return;
  if (expect_equal_str(token_stream.tokens[0].data, "Test") == TEST_FAILED) return;
  if (expect_equal_str(token_stream.tokens[1].name, "NUM") == TEST_FAILED) return;
  if (expect_equal_str(token_stream.tokens[1].data, "123") == TEST_FAILED) return;

  free(token_stream.tokens);
  free(lexemes);
}

int main(void) {
  run_suite("Lexer");

  run_test("lexes a single token");
  test_single_token();
  end_test();

  run_test("lexes adjacent tokens");
  test_adjacent_tokens();
  end_test();

  end_suite();
}
