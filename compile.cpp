#include "compile.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void print_bytecode(compiler* c) {
  printf("bytecodes:\n");
  for (int i = 0; i<c->codes.size(); i++) {
    printf("%d\n", c->codes[i]);
  }
}

static uint8_t make_constant(compiler* c, value constant) {
  c->constants.push_back(constant);
  size_t size = c->constants.size();
  if (size > UINT8_MAX)  {
    printf("too many constant\n");
    return 0;
  }

  return (uint8_t)size-1;
}

static void emit_byte(compiler* c, scanner* s, uint8_t byte) {
  c->codes.push_back(byte);
  c->lines.push_back(s->line);
}

static void emit_constant(compiler* c, scanner* s, value constant) {
  emit_byte(c, s, OP_CONSTANT);
  emit_byte(c, s, make_constant(c, constant));
}

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
  c->previous = c->current;
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

static void print(compiler* c, scanner* s) {
  expression(c, s);
  emit_byte(c, s, OP_PRINT);
}

static void number(compiler* c, scanner* s) {
  double v = strtod(c->previous.start, NULL);
  emit_constant(c, s, NUMBER_VAL(v));
}

static void expression(compiler* c, scanner* s) {
  if (match(c, s, TOKEN_LEFT_PAREN)) {
    call(c, s);
    args(c, s);
    return;
  }
  
  if (match(c, s, TOKEN_PRINT)) {
    print(c, s);
    return;
  }
  
  if (match(c, s, TOKEN_NUMBER)) {
    number(c, s);
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
