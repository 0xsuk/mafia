#include "compile.h"
#include <stdio.h>

static void mark_scanner_error(compiler* c) {
  compile_error ce;
  ce.line = c->current.line;
  ce.message = c->current.start;
  c->errors.push_back(ce);

  c->had_error = true;
}

static void mark_error(compiler* c, char* message) {
  compile_error ce;
  ce.line = c->current.line;
  ce.message = message;
  c->errors.push_back(ce);

  c->had_error = true;
}

static void advance(compiler* c, scanner* s) {
  while(true) {
    c->current = scan_token(s);
    
    if (c->current.type != TOKEN_ERR) {
      break;
    }

    mark_scanner_error(c);
  }
}

static bool check(token t, token_type type) {
  return t.type == type;
}

static bool match(compiler* c, scanner* s, token_type type) {
  if (!check(c->current, type)) {
    return false;
  }
  advance(c, s);
  return true;
}

static void consume(compiler* c, scanner* s, token_type type, char* message) {
  if (!match(c, s, type)) {
    mark_error(c, message);
  }
}

static void args(compiler* c, scanner* s) {
  while (!match(c, s, TOKEN_RIGHT_PAREN)) {
    expression(c, s);
  }
}

static void call(compiler* c, scanner* s) {
  expression(c, s);
}

static void expression(compiler* c, scanner* s) {
  if (match(c, s, TOKEN_LEFT_PAREN)) {
    call(c, s);
    args(c, s);
    return;
  }
  
  if (match(c, s, TOKEN_NUMBER)) {
    return;
  }

  if (match(c, s, TOKEN_STRING)) {
    return;
  }

  if (match(c, s, TOKEN_IDENTIFIER)) {
    return;
  }

  mark_error(c, "unexpected expression");
}

void compile(compiler* c, char* code) {
  scanner s{code};
  
  advance(c, &s);

  while (!match(c, &s, TOKEN_EOF)) {
    expression(c, &s);
  }
}
