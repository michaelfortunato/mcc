#include "lexer.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"

#define IS_WHITESPACE(c) (c == ' ' || c == '\t' || c == '\n')

char *curr_filepath = NULL;

unsigned int line_number = 0;

unsigned int character_number = 0;

Token token;
int tokenize_file(char *filepath) {
  curr_filepath = filepath;
  open_file(filepath);

  return 0;
}

int gettok() {
  for (;;) {
    switch (*cp++) {
      case EOF:
        if (AT_EOB1_NEW((cp - 1))) {
          reload_buffer_2();
          printf("RELOAD BUFFER 2\n");
        } else if (AT_EOB2_NEW((cp - 1))) {
          reload_buffer_1();
          printf("RELOAD BUFFER 1\n");
        } else {
          printf("At end.");
          return -1;
        }
        continue;
      case 'i':
        printf("CHAR : %c.\n", *(cp - 1));

        if (*cp == 'n' && cp[1] == 't' && (IS_WHITESPACE(cp[2]) || (cp[2] == EOF && !AT_EOB1_NEW((cp + 2)) && !AT_EOB2_NEW((cp + 2))))) {
          token.type = TOKEN_KEYWORD;
          token.lexeme_start = (cp - 1);
          token.lexeme_end = cp + 1;
          cp = cp + 2;
          return token.type;
        } else if (*cp == 'f' && (IS_WHITESPACE(cp[2]) || (cp[2] == EOF && !AT_EOB1_NEW((cp + 2)) && !AT_EOB2_NEW((cp + 2))))) {
          token.type = TOKEN_KEYWORD;
          token.lexeme_start = (cp - 1);
          token.lexeme_end = cp;
          cp = cp + 1;
          return token.type;
        }
        goto id;
      case 'h':
      case 'j':
      case 'k':
      case 'm':
      case 'n':
      case 'o':
      case 'p':
      case 'q':
      case 'x':
      case 'y':
      case 'z':
      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':
      case 'G':
      case 'H':
      case 'I':
      case 'J':
      case 'K':
      case 'M':
      case 'N':
      case 'O':
      case 'P':
      case 'Q':
      case 'R':
      case 'S':
      case 'T':
      case 'U':
      case 'V':
      case 'W':
      case 'X':
      case 'Y':
      case 'Z':
      id:
        token.type = TOKEN_IDENTIFIER;
        token.lexeme_start = cp - 1;
        while (isalnum(*cp)) {
          ++cp;
        }
        switch (*cp) {
          case EOF: {
            if (AT_EOB1_NEW((cp)) || AT_EOB2_NEW((cp))) {
              if (AT_EOB1_NEW(cp)) {
                reload_buffer_2();
                printf("RELOAD BUFFER 2\n");
              } else {
                reload_buffer_1();
                printf("RELOAD BUFFER 1\n");
              }
              while (isalnum(*cp)) {
                ++cp;
              }
              switch (*cp) {
                case EOF: {
                  if (AT_EOB1_NEW(cp) || AT_EOB2_NEW(cp)) {
                    printf("Too crazy large");
                    // fprintf(stderr, "Too crazy large");
                    return -2;
                  }
                  break;
                }
                case '\n':
                case '\t':
                case '\r':
                case ' ':
                  break;
                default:
                  printf("Unrecognized characeter");
                  // fprintf(stderr, "Unrecognized characeter");
                  return -2;
              }
            }
            break;
          }
          case '\n':
          case '\t':
          case '\r':
          case ' ':
            break;
          default:
            fprintf(stderr, "Unrecognized character");
            return -2;
        }
        token.lexeme_end = (cp - 1);
        return token.type;
      case '\n':
      case '\t':
      case '\r':
      case ' ':
        continue;
      default:
        // printf("%p\n", buffer);
        // printf("%s\n", buffer);
        // printf("%p\n", cp);
        printf("BAD\n");
        return -2;
    }
  }
}
