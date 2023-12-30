#ifndef VM_H
#define VM_H

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

#endif

