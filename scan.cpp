#include <stdio.h>
#include "scan.h"

scanner::scanner(char* code) {
  this->start = code;
  this->current = code;
  this->line = 1;
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
      if (peek_next(s) == '/') {
        //comment til end of line
        while (peek(s) != '\n' && !at_end(s)) {
          advance(s);
        }
      } else {
        return;
      }
      break;
    default:
      return;
    }
  }
}

token scan_token(scanner* s) {
  skip_space(s);
  
  printf("%c\n", *s->current);

  return token{};
}
