#include "hashtable.h"
#include "linkedlist.h"
#include <stdio.h>

//  #include "file.h"
// #include "lexer.h"
// #include "parser.h"

extern unsigned int num_read;

int main() {
  printf("Raw contents\n");
  // open_file(argv[1]);
  // char cd = *advance();
  // printf("%c \n", cd);
  // printf("%d \n", offset);

  // tokenize_file(argv[1]);
  // unsigned short int same;
  // const char *test[] = {"in", "if", "michael", "case", "default", "auto",
  // "continue", "do", "double"}; int i = 0; while ((gettok() == 0) && (i < 8))
  // { printf("---\n"); printf("%s vs. ", test[i]); printlexeme();
  // printf("\n---\n");
  // same = compare(test[i]);
  // ++i;
  // printf("Are they the same? %d\n", same);
  // }

  // Node *code = parse();
  // printf("%d\n", code->type);
  // printf("%d\n", code->children[0]->type);
  const char *test[] = {"in", "if", "michael", "case"};
  struct list *l = list_new();
  for (int i = 0; i < 4; i++) {
    printf("Here\n");
    list_append(l, test[i]);
  }
  printf("Finding Michael");
  struct node *n = list_find(l, "michael\n");
  if (n == NULL) {
    printf("OOPSIES! YOU COULD BARELY DO A LEETCODE EASY. STEP UP.");
  } else {
    printf("Oh thank god. We found michael at %p. Here he is: %s", n, n->value);
  }

  return 0;
}
