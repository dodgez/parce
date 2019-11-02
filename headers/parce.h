#ifndef parce_h
#define parce_h

#include <regex.h>
#include <stdlib.h>

#define LEX_SUCCESS 0

// flags: bit 1 set if ignored
typedef struct {
  char* name;
  int flags;
  regex_t regex;
} Lexeme;

typedef struct {
  int size;
  Lexeme* lexemes;
} LexemeList;

typedef struct {
  char* name;
  char* data;
} Token;

typedef struct {
  int size;
  Token* tokens;
} TokenList;

// flags: 0 for nothing, 1 for optional, and 2 for one or more
typedef struct {
  int flags;
  int size;
  void* sub_option;
} Option;

typedef struct {
  char* name;
  int size;
  Option* options;
} Rule;

// type: 0 for Lexeme and 1 for Rule
typedef struct {
  int type;
  Lexeme lexeme;
  Rule rule;
} LexemeRule;

typedef struct {
  int size;
  Rule* rules;
} RuleList;

typedef struct {
  char* name;
  int children_size;
  struct ASTNode* children;
  char* token;
} ASTNode;

#endif
