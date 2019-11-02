#include "lexer.h"

int lex(LexemeList lexeme_list, char* stream, TokenStream* token_stream) {
  int token_index = 0;
  int max_token_length = 256;
  token_stream->tokens = (Token*)malloc(sizeof(Token) * max_token_length);
  memset(token_stream->tokens, 0, sizeof(Token) * max_token_length);
  int expr_index = 0;
  int max_expr_length = 256;
  char* expr = (char*)malloc(sizeof(char) * max_expr_length);
  memset(expr, 0, sizeof(char) * max_expr_length);
  Lexeme* last_lexeme = NULL;
  Lexeme* cur_lexeme = NULL;

  while (strlen(stream) > 0) {
    if (expr_index >= max_expr_length) {
      max_expr_length *= 2;
      expr = (char*)realloc(expr, max_expr_length);
    }

    expr[expr_index++] = stream[0];

    cur_lexeme = NULL;

    for (int i = 0; i < lexeme_list.size; ++i) {
      if (!regexec(&lexeme_list.lexemes[i].regex, expr, 0, NULL, 0)) {
        cur_lexeme = &lexeme_list.lexemes[i];
        break;
      }
    }

    if (!cur_lexeme) {
      if (last_lexeme) {
        if ((last_lexeme->flags & 1) == 0) {
          if (token_index >= max_token_length) {
            max_token_length *= 2;
            token_stream->tokens = (Token*)realloc(token_stream->tokens, max_token_length);
          }

          token_stream->tokens[token_index].name = last_lexeme->name;
          token_stream->tokens[token_index].data = (char*)malloc(sizeof(char) * (expr_index - 1));
          memcpy(token_stream->tokens[token_index].data, expr, sizeof(char) * (expr_index - 1));
          token_index++;
        }

        expr_index = 0;
        memset(expr, 0, sizeof(char) * max_expr_length);
        last_lexeme = cur_lexeme;
        continue;
      } else {
        free(expr);
        free(token_stream->tokens);
        token_stream->size = 0;
        return 1;
      }
    }

    stream += sizeof(char);
    last_lexeme = cur_lexeme;
  }

  if (last_lexeme && (last_lexeme->flags & 1) == 0) {
    if (token_index >= max_token_length) {
      max_token_length *= 2;
      token_stream->tokens = (Token*)realloc(token_stream->tokens, max_token_length);
    }

    token_stream->tokens[token_index].name = last_lexeme->name;
    token_stream->tokens[token_index].data = (char*)malloc(sizeof(char) * expr_index);
    strcpy(token_stream->tokens[token_index].data, expr);
    token_index++;
  }

  token_stream->size = token_index;
  free(expr);
  return 0;
}
