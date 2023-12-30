#ifndef VM_H
#define VM_H

#include <vector>
#include <stdlib.h>
#include "compile.h"

struct obj_closure {
  
};

struct frame {
  obj_closure* closure;
  size_t ip; //index of bytecode
  value* slots;
};

struct vm {
  std::vector<frame> frames;
  std::vector<value> stack;
};

int run(compiler* c);

#endif

