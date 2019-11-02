#include "parser.h"

Token getTokenFromStream(TokenStream token_stream) {
  return token_stream.tokens[token_stream.index];
}

int streamIsEOF(TokenStream token_stream) {
  return token_stream.index >= token_stream.size;
}

int matchesLexeme(Lexeme lexeme, TokenStream token_stream) {
  return strcmp(getTokenFromStream(token_stream).name, lexeme.name) == 0;
}

int matchesRule(Rule rule, TokenStream token_stream) {
  for (int i = 0; i < rule.size; ++i) {
    LexemeRule sub_option = ((LexemeRule*)rule.options[i].sub_option)[0];

    if (sub_option.type == 0 && matchesLexeme(sub_option.lexeme, token_stream)) {
      return 1;
    } else if (sub_option.type == 1 && matchesRule(sub_option.rule, token_stream)) {
      return 1;
    }
  }

  return 0;
}

int parseLexeme(Lexeme lexeme, TokenStream token_stream, ASTNode* root) {
  root->name = lexeme.name;
  root->children_size = 0;
  root->children = NULL;
  root->token = getTokenFromStream(token_stream).data;

  return 0;
}

int parse(Rule rule, TokenStream token_stream, ASTNode* root) {
  int max_children_length = 1;
  root->name = rule.name;
  root->children_size = 0;
  root->children = (ASTNode*)malloc(sizeof(ASTNode) * max_children_length);
  memset(root->children, 0, sizeof(ASTNode) * max_children_length);
  root->token = NULL;

  for (int i = 0; i < rule.size; ++i) {
    Option option = rule.options[i];
    int optional = ((option.flags & 1) == 1);
    int one_or_more = ((option.flags & 2) == 2);
    int occurances = 0;
    int option_passed = 1;

    do {
      for (int j = 0; j < option.size; ++j) {
        LexemeRule lexeme_rule = ((LexemeRule*)option.sub_option)[j];

        if (root->children_size == max_children_length) {
          max_children_length *= 2;
          root->children = (ASTNode*)malloc(sizeof(ASTNode) * max_children_length);
          memset(root->children, 0, sizeof(ASTNode) * max_children_length);
        }

        if (lexeme_rule.type == 0) {
          if (matchesLexeme(lexeme_rule.lexeme, token_stream) == 1) {
            parseLexeme(lexeme_rule.lexeme, token_stream, &(root->children[root->children_size]));
            root->children_size += 1;
            token_stream.index += 1;
            option_passed = 1;
            occurances++;
            break;
          }
        } else if (lexeme_rule.type == 1) {
          if (matchesRule(lexeme_rule.rule, token_stream) == 1) {
            parse(lexeme_rule.rule, token_stream, &(root->children[root->children_size]));
            root->children_size += 1;
            option_passed = 1;
            occurances++;
            break;
          }
        }

        option_passed = 0;
      }
    } while (one_or_more && option_passed && !streamIsEOF(token_stream));

    if (!option_passed && !optional && (!one_or_more || (one_or_more && occurances == 0))) {
      return 1;
    }
  }

  return 0;
}
