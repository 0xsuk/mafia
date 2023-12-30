#include "vm.h"

int run(compiler* c) {
  print_bytecode(c);

  
  
  for (int i = 0; i<c->codes.size(); i++) {
    uint8_t opcode = c->codes[i];

    switch (opcode) {
    case OP_CONSTANT:
      
    case OP_PRINT:
      
    }
  }
  
  return 0;
}
