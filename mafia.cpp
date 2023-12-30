#include <stdio.h>
#include "scan.h"
#include <string.h>
#include "compile.h"
#include "vm.h"

int main() {
  printf("testing\n");
  compiler c;
  while (true) {
    printf("> ");
    char line[1024]; //ignore overflow
    if (!fgets(line, sizeof(line), stdin)) {
      break;
    }

    compile(&c, line);
    run(&c);
  }
}
