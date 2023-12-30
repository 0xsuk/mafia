#include <stdio.h>
#include "scan.h"
#include <string.h>
#include "compile.h"

bool is_complete(char* code) {
  compiler c;
  compile(&c, code);
  
  if (c.had_error) {
    printf("error:\n");
    for (int i = 0; i<c.errors.size(); i++) {
      printf("%s\n", c.errors[i].message);
    }
    return true;
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
