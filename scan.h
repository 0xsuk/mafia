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
  TOKEN_LET
};

struct token {
  token_type type;
  char* start;
  int len;
  int line;
};

struct scanner {
  char* start;
  char* current;
  int line = 0;
  scanner(char*);
};

token scan_token(scanner* s);
int scan(char* code);

#endif
