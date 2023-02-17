#include <ctype.h>
#include <stdio.h>

#include "file.h"
#include "lexer.h"
#include "parser.h"

extern unsigned int num_read;

int main(int argc, char **argv) {
  if (argc != 2) {
    return 1;
  }
  printf("Raw contents\n");
  open_file(argv[1]);
  // char cd = *advance();
  // printf("%c \n", cd);
  // printf("%d \n", offset);

  tokenize_file(argv[1]);
  unsigned short int same;
  const char *test[] = {"in", "if", "michael", "case", "default", "auto", "continue", "do", "double"};
  int i = 0;
  while ((gettok() == 0) && (i < 8)) {
    printf("---\n");
    printf("%s vs. ", test[i]);
    printlexeme();
    printf("\n---\n");
    same = compare(test[i]);
    ++i;
    printf("Are they the same? %d\n", same);
  }

  // Node *code = parse();
  // printf("%d\n", code->type);
  // printf("%d\n", code->children[0]->type);
  return 0;
}
