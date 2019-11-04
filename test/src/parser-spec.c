#include <stdlib.h>
#include <string.h>

#include "parce.h"
#include "parser.h"
#include "expect.h"

void test_rule_one_option(void) {
  ASTNode tree;

  Lexeme ID;
  regex_t ID_regex;
  ID.name = "ID";
  regcomp(&ID_regex, "^[a-zA-Z]\\+$", 0);
  ID.regex = ID_regex;
  ID.flags = 0;

  Rule rule;
  rule.name = "ID rule";
  rule.size = 1;
  rule.options = (Option*)malloc(sizeof(Option) * rule.size);
  memset(rule.options, 0, sizeof(Option) * rule.size);

  rule.options[0].size = 1;
  rule.options[0].flags = 0;
  rule.options[0].sub_option = (LexemeRule*)malloc(sizeof(LexemeRule) * rule.options[0].size);
  memset(rule.options[0].sub_option, 0, sizeof(LexemeRule) * rule.options[0].size);
  LexemeRule* sub_option0 = (LexemeRule*)rule.options[0].sub_option;
  sub_option0[0].type = 0;
  sub_option0[0].lexeme = ID;

  TokenStream token_stream;
  token_stream.size = 1;
  token_stream.index = 0;
  token_stream.tokens = (Token*)malloc(sizeof(Token) * token_stream.size);
  memset(token_stream.tokens, 0, sizeof(Token) * token_stream.size);
  token_stream.tokens[0].name = "ID";
  token_stream.tokens[0].data = "test";

  int parse_result = parse(rule, token_stream, &tree);
  if (expect_equal_int(parse_result, PARSE_SUCCESS) == TEST_FAILED) return;
  if (expect_equal_str(tree.name, rule.name) == TEST_FAILED) return;
  if (expect_equal_int(tree.children_size, 1) == TEST_FAILED) return;
  
  if (expect_equal_str(tree.children[0].name, token_stream.tokens[0].name) == TEST_FAILED) return;
  if (expect_equal_int(tree.children[0].children_size, 0) == TEST_FAILED) return;
  if (expect_equal_str(tree.children[0].token, token_stream.tokens[0].data) == TEST_FAILED) return;
  return;
}

void test_rule_two_options(void) {
  ASTNode tree;

  Lexeme NUM;
  regex_t NUM_regex;
  NUM.name = "NUM";
  regcomp(&NUM_regex, "^[0-9]\\+$", 0);
  NUM.regex = NUM_regex;
  NUM.flags = 0;

  Lexeme ID;
  regex_t ID_regex;
  ID.name = "ID";
  regcomp(&ID_regex, "^[a-zA-Z]\\+$", 0);
  ID.regex = ID_regex;
  ID.flags = 0;

  Rule rule;
  rule.name = "NUM/ID rule";
  rule.size = 1;
  rule.options = (Option*)malloc(sizeof(Option) * rule.size);
  memset(rule.options, 0, sizeof(Option) * rule.size);

  rule.options[0].size = 2;
  rule.options[0].flags = 0;
  rule.options[0].sub_option = (LexemeRule*)malloc(sizeof(LexemeRule) * rule.options[0].size);
  memset(rule.options[0].sub_option, 0, sizeof(LexemeRule) * rule.options[0].size);
  LexemeRule* sub_option0 = (LexemeRule*)rule.options[0].sub_option;
  sub_option0[0].type = 0;
  sub_option0[0].lexeme = NUM;
  sub_option0[1].type = 0;
  sub_option0[1].lexeme = ID;

  TokenStream token_stream;
  token_stream.size = 1;
  token_stream.index = 0;
  token_stream.tokens = (Token*)malloc(sizeof(Token) * token_stream.size);
  memset(token_stream.tokens, 0, sizeof(Token) * token_stream.size);
  token_stream.tokens[0].name = "NUM";
  token_stream.tokens[0].data = "123";

  int parse_result = parse(rule, token_stream, &tree);
  if (expect_equal_int(parse_result, PARSE_SUCCESS) == TEST_FAILED) return;
  if (expect_equal_str(tree.name, rule.name) == TEST_FAILED) return;
  if (expect_equal_int(tree.children_size, 1) == TEST_FAILED) return;
  
  if (expect_equal_str(tree.children[0].name, token_stream.tokens[0].name) == TEST_FAILED) return;
  if (expect_equal_int(tree.children[0].children_size, 0) == TEST_FAILED) return;
  if (expect_equal_str(tree.children[0].token, token_stream.tokens[0].data) == TEST_FAILED) return;

  token_stream.tokens[0].name = "ID";
  token_stream.tokens[0].data = "test";
  parse_result = parse(rule, token_stream, &tree);
  if (expect_equal_int(parse_result, PARSE_SUCCESS) == TEST_FAILED) return;
  if (expect_equal_str(tree.name, rule.name) == TEST_FAILED) return;
  if (expect_equal_int(tree.children_size, 1) == TEST_FAILED) return;
  
  if (expect_equal_str(tree.children[0].name, token_stream.tokens[0].name) == TEST_FAILED) return;
  if (expect_equal_int(tree.children[0].children_size, 0) == TEST_FAILED) return;
  if (expect_equal_str(tree.children[0].token, token_stream.tokens[0].data) == TEST_FAILED) return;
  return;
}

int main(void) {
  run_suite("Parser");

  run_test("Parses a rule with one option");
  test_rule_one_option();
  end_test();

  run_test("Parses a rule with two options");
  test_rule_two_options();
  end_test();

  end_suite();
}
