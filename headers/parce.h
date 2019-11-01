#ifndef parce_h
#define parce_h

#include <regex.h>

#define LEX_SUCCESS 0

// Options flag has bit 1 set if ignored
typedef struct {
  char* name;
  int options;
  regex_t regex;
} Lexeme;

typedef struct {
  int size;
  Lexeme* lexemes;
} LexemeStream;

typedef struct {
  char* name;
  char* data;
} Token;

typedef struct {
  int size;
  Token* tokens;
} TokenStream;

#endif
