#ifndef SCAN_H
#define SCAN_H

enum token_type {
  TOKEN_LEFT_PAREN,
  TOKEN_RIGHT_PAREN,
  TOKEN_BANG,
  TOKEN_IDENTIFIER,
  TOKEN_STRING,
  TOKEN_NUMBER,
  TOKEN_TRUE,
  TOKEN_NIL,
  TOKEN_IF,
  TOKEN_DEFUN,
  TOKEN_DEFMACRO,
  TOKEN_LET,
  TOKEN_EOF,
  TOKEN_ERR
};

struct scanner {
  char* start;
  char* current;
  int line = 0;
  scanner(char*);
};

struct token {
  token_type type;
  char* start;
  int len;
  int line;
  token() = default;
  token(scanner*, token_type);
};

void print_token(token*);
token scan_token(scanner*);
int scan(char*);

#endif
