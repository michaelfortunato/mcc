#include <ctype.h>
#include <stdio.h>

#include "file.h"
#include "lexer.h"

extern unsigned int num_read;

void tok_type_to_str(TokenType tokType) {
  switch (tokType) {
    case 0:
      printf("KEYWORD\n");
      return;
    case 1:
      printf("IDENTIFIER\n");
      return;
    case 2:
      printf("CONSTANT\n");
      return;
    case 3:
      printf("STRING_LITERAL\n");
      return;
    case 4:
      printf("STRING_PUNCTUATOR\n");
      return;
    default:
      printf("ERROR");
      return;
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    return 1;
  }
  /*
  tokenize_file(argv[1]);
  char *et, *forward;
  int b;
  int seeker = 0;
  while ((b = gettok()) >= 0) {
    tok_type_to_str(token.type);
    et = token.lexeme_start;
    // char *cp = token.lexeme_start;
    // printf("%c", *et);
    seeker = et - buffer;
    while ((buffer + seeker) != token.lexeme_end) {
      if (buffer[seeker] != EOF) {
        printf("%c", buffer[seeker]);
      }
      seeker = (seeker + 1) % BUFF_SIZE;
    }
    printf("\n-----------------------------------------------------------------\n");
    printf("\n");
  }
  */
  // printf("FIN : %d\n", b);
  printf("Raw contents\n");
  open_file(argv[1]);
  char next_char;
  while ((next_char = advance()) != EOF) {
    printf("%c", next_char);
  }
  printf("\n");
  close_file();

  open_file(argv[1]);
  for (;;) {
    switch (next_char = advance()) {
      case EOF: {
        return 0;
      }
      case 'i': {
        char luc1 = advance();
        char luc2 = advance();
        char luc3 = advance();
        if (luc1 == 'n' && luc2 == 't' && (isspace(luc3) || luc3 == EOF)) {
          printf("FOUND INT\n");
          if (luc3 == EOF) {
            return 0;
          }
          break;
        } else if (luc1 == 'f' && (isspace(luc2) || luc2 == EOF)) {
          printf("FOUND IF\n");
          if (luc3 == EOF) {
            return 0;
          }
          break;
        }
        goto id;
      }
      default:
      id:
        printf("FOUND IDENTIFIER\n");
        while ((next_char = advance()) != EOF && !isspace(next_char)) {
          printf("%c", next_char);
        }
        if (next_char == EOF) {
          return 0;
        }
        break;
    }
  }

  /*
  // printf("\n%s", buffer);
  debug();
  */
  // printf("[STRING] : %.*s\n", (char)(token.lexeme_end - token.lexeme_start), token.lexeme_start);
  return 0;
}
