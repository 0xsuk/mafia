#include <stdio.h>
#include "scan.h"
#include <string.h>
#include "compile.h"

bool is_complete(char* code) {
  if (compile(code) == 1) {
    return false;
  }
  
  return true;
}

int main() {
  printf("testing\n");
  char code[1024*10];
  while (true) {
    printf("> ");
    char line[1024]; //ignore overflow
    if (!fgets(line, sizeof(line), stdin)) {
      break;
    }

    int len = strlen(line);
    strcat(code, line);
    if (is_complete(code)) {
      break;
    }
  }
}
