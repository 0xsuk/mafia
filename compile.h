#ifndef PARSE_H
#define PARSE_H

#include "scan.h"
#include <vector>
#include "vm.h"

struct compile_error {
  int line;
  char* message;
};

struct compiler {
  token previous;
  token current;
  bool had_error = false;
  bool panic_mode = false;
  std::vector<uint8_t> codes; // stores byte codes
  std::vector<int> lines;    // stores lines for byte codes seperately
  std::vector<value> constants;
  std::vector<compile_error> errors;
};

#define NUMBER_VAL(v) ((value){VAL_NUMBER, {.number = v}})


static void expression(compiler* c, scanner* s);
void compile(compiler* c, char* code);
#endif
