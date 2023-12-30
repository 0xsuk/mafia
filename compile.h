#ifndef COMPILE_H
#define COMPILE_H

#include "scan.h"
#include <stdint.h>
#include <vector>

enum op_code {
  OP_CONSTANT,
  OP_NIL,
  OP_TRUE,
  OP_CALL,
  OP_PRINT,
};

enum value_type {
  VAL_BOOL,
  VAL_NIL,
  VAL_NUMBER,
  VAL_OBJ,
};

struct value {
  value_type type;
  union {
    bool boolean;
    double number;
  };
};

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

void print_bytecode(compiler* c);
static void expression(compiler* c, scanner* s);
void compile(compiler* c, char* code);
#endif
