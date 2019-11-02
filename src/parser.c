#include "parser.h"

int matchesLexeme(Lexeme lexeme, TokenList token_list, int index) {
  return token_list.tokens[index].name == lexeme.name;
}

int matchesRule(Rule rule, TokenList token_list, int index) {
  for (int i = 0; i < rule.size; ++i) {
    LexemeRule* sub_option = (LexemeRule*)rule.options[i].sub_option[0];

    if (sub_option->type == 0 && matchesLexeme(sub_option->lexeme, token_list, index)) {
      return 1;
    } else if (sub_option->type == 1 && matchesRule(sub_option->rule, token_list, index)) {
      return 1;
    }
  }

  return 0;
}

int parseLexeme(Lexeme lexeme, TokenList token_list, int index, ASTNode* root) {
  root->name = lexeme.name;
  root->children_size = 0;
  root->children = NULL;
  root->token = token_list.tokens[index].data;

  return 0;
}

int parseRule(Rule rule, TokenList token_list, ASTNode* root) {
  root->name = rule.name;
  root->children_size = 0;
  root->children = NULL;
  root->token = NULL;

  for (int i = 0; i < rule.size; ++i) {
    Option option = rule.options[i];
    int optional = (option.flags & 1 == 1);
    int one_or_more = (option.flags & 2 == 2);
  }
}
