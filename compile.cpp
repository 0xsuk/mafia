#include "compile.h"

parser::parser() {
  
}

void advance(parser* p, scanner* s) {
  p->previous = p->current;
  while(true) {
    scan_token(s);
    break;
  }
}

int compile(char* code) {
  scanner s{code};
  parser p{};

  advance(&p, &s);
  return 0;
}
