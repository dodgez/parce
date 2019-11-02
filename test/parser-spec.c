#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parce.h"
#include "parser.h"

int main(void) {
  ASTNode tree;

  regex_t NUM_regex;
  regcomp(&NUM_regex, "^[0-9]\\+$", 0);

  Lexeme NUM;
  NUM.name = "NUM";
  NUM.regex = NUM_regex;
  NUM.flags = 0;

  regex_t ID_regex;
  regcomp(&ID_regex, "^[a-zA-Z]\\+$", 0);

  Lexeme ID;
  ID.name = "ID";
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
  LexemeRule* sub_option1 = (LexemeRule*)rule.options[0].sub_option;
  sub_option1[1].type = 0;
  sub_option1[1].lexeme = ID;

  TokenStream token_stream;
  token_stream.size = 1;
  token_stream.index = 0;
  token_stream.tokens = (Token*)malloc(sizeof(Token) * token_stream.size);
  memset(token_stream.tokens, 0, sizeof(Token) * token_stream.size);
  token_stream.tokens[0].name = "ID";
  token_stream.tokens[0].data = "test";

  int parse_result = parse(rule, token_stream, &tree);

  if (parse_result == PARSE_SUCCESS) {
    printf("Tree \"%s\" at %p with size %d\n", tree.name, &tree, tree.children_size);
    
    if (tree.children_size > 0) {
      printf("Tree has child \"%s\" at %p with size %d and token \"%s\"\n", tree.children[0].name, &tree.children[0], tree.children[0].children_size, tree.children[0].token);
    }
  }

  return 0;
}
