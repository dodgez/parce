#ifndef parce_h
#define parce_h

#include <regex.h>
#include <stdlib.h>

#define LEX_SUCCESS 0

// flags: bit 1 set if ignored
typedef struct Lexeme {
  char* name;
  int flags;
  regex_t regex;
} Lexeme;

typedef struct LexemeList {
  int size;
  Lexeme* lexemes;
} LexemeList;

typedef struct Token {
  char* name;
  char* data;
} Token;

typedef struct TokenStream {
  int size;
  int index;
  Token* tokens;
} TokenStream;

// flags: 0 for nothing, 1 for optional, and 2 for one or more
typedef struct Option {
  int flags;
  int size;
  void* sub_option;
} Option;

typedef struct Rule {
  char* name;
  int size;
  Option* options;
} Rule;

// type: 0 for Lexeme and 1 for Rule
typedef struct LexemeRule {
  int type;
  Lexeme lexeme;
  Rule rule;
} LexemeRule;

typedef struct RuleList {
  int size;
  Rule* rules;
} RuleList;

typedef struct ASTNode {
  char* name;
  int children_size;
  struct ASTNode* children;
  char* token;
} ASTNode;

#endif
