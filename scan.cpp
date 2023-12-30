#include <stdio.h>
#include "scan.h"
#include <string.h>

token::token(scanner* s, token_type type) {
  this->type = type;
  this->start = s->start;
  this->len = (int)(s->current - s->start);
  this->line = s->line;
}

token error_token(scanner* s, char* error) {
  token t;
  t.type = TOKEN_ERR;
  t.start = error;
  t.len = strlen(error);
  t.line = s->line;
  return t;
}

scanner::scanner(char* code) {
  this->start = code;
  this->current = code;
  this->line = 1;
}

void print_token(token* t) {
  printf("token {\n");
  printf("\ttype %d\n", t->type);
  printf("\tstart %c\n", *t->start);
  printf("\tlen %d\n", t->len);
  printf("\tline %d\n", t->line);
  printf("}\n");
}

static bool at_end(scanner* s) {
  return *s->current == '\0';
}

static char peek(scanner* s) {
  return *s->current;
}

static char peek_next(scanner* s) {
  if (at_end(s)) {
    return '\0';
  }
  return s->current[1];
}

static char peek_prev(scanner* s) {
  return s->current[-1];
}

static void advance(scanner* s) {
  s->current++;
}

void skip_space(scanner* s) {
  while (true) {
    char c = peek(s);
    switch (c) {
    case ' ':
    case '\r':
    case '\t':
      advance(s);
      break;
    case '\n':
      s->line++;
      advance(s);
      break;
    case '/':
      if (peek_next(s) != '/') {
        return;
      }
      //comment til end of line
      while (peek(s) != '\n' && !at_end(s)) {
        advance(s);
      }
      break;
    default:
      return;
    }
  }
}

static bool is_alpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || c == '-' || c == '*' || c == '!';
}


static bool is_digit(char c) { return '0' <= c && c <= '9'; }

static token identifier(scanner* s, char c)  {
  while (is_alpha(peek(s)) || is_digit(peek(s))) {
    advance(s);
  }

  return token{s, TOKEN_IDENTIFIER};
}

static token number(scanner* s, char c) {
  while (is_digit(peek(s))) {
    advance(s);
  }

  if (peek(s) == '.' && is_digit(peek_next(s))) {
    advance(s);
    while (is_digit(peek(s))) {
      advance(s);
    }
  }
  
  return token{s, TOKEN_NUMBER};
}

token string(scanner* s) {
  while ((peek(s) != '"' && !at_end(s)) || peek_prev(s) != '\\') {
    if (peek(s) == '\n') s->line++;
    advance(s);
  }

  if (at_end(s)) {
    return error_token(s, "incomplete string");
  }

  return token{s, TOKEN_STRING};
}

token scan_token(scanner* s) {
  skip_space(s);
  s->start = s->current;
  
  if (at_end(s)) {
    return token{s, TOKEN_EOF};
  }
  
  char c = peek(s);
  advance(s);
  
  if (is_digit(c)) {
    return number(s, c);
  }
  
  switch (c) {
  case '(':
    return token{s, TOKEN_LEFT_PAREN};
  case ')':
    return token{s, TOKEN_RIGHT_PAREN};
  case '"':
    return string(s);
  }
  if (is_alpha(c)) {
    return identifier(s, c);
  }
  

  
  return error_token(s, "unexpected character");
}
