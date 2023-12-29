#ifndef COMPILE_H
#define COMPILE_H

#include "scan.h"

struct parser {
  token current;
  token previous;
  bool had_error = false;

  parser();
};

int compile(char*);
#endif
