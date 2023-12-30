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

static void paren(compiler* c, scanner* s) {
  printf("c->current:%d\n", c->current.type);
  if (!match(c, s, TOKEN_LEFT_PAREN)) {
    mark_error(c, "unexpected token: left_paren expected");
    return;
  }
  advance(c, s);
}

void compile(compiler* c, char* code) {
  scanner s{code};
  
  advance(c, &s);

  if (!match(c, &s, TOKEN_EOF)) {
    paren(c, &s);
  }
}
