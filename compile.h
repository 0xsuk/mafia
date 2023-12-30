#ifndef PARSE_H
#define PARSE_H

#include "scan.h"
#include <vector>

struct compile_error {
  int line;
  char* message;
};

struct compiler {
  token current;
  bool had_error = false;
  bool panic_mode = false;
  std::vector<compile_error> errors;
};
static void expression(compiler* c, scanner* s);
void compile(compiler* c, char* code);
#endif
