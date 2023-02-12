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
  token.filepath = filepath;
  open_file(filepath);

  return 0;
}
void printtoktype(TokenType toktype) {
  switch (toktype) {
    case TOKEN_KEYWORD:
      printf("TOKEN_KEYWORD");
      return;
    case TOKEN_IDENTIFIER:
      printf("TOKEN_IDENTIFIER");
      return;
    case TOKEN_CONSTANT:
      printf("TOKEN_CONSTANT");
      return;
    case TOKEN_STRLIT:
      printf("TOKEN_STRLIT");
      return;
    case TOKEN_PUNCTUATOR:
      printf("TOKEN_PUNCTUATOR");
      return;
    default:
      printf("INVALID TOKEN TYPE!");
      return;
  }
}

void printlexeme() {
  char *forward = token.lexeme_start;
  while (forward != token.lexeme_end) {
    switch (*forward) {
      case EOF:
        if (AT_EOB1_NEW(forward)) {
          ++forward;
          break;
        } else if (AT_EOB2_NEW(forward)) {
          forward = buffer;  // probably should make buffer private
          break;
        } else {
          printf("PRINT LEXEME ERROR!\n");
          return;
        }
      default:
        printf("%c", *forward);
        ++forward;
        break;
    }
  }
}

void printtok() {
  printf("Token\n");
  printf("------------------------------\n");
  printf("  - TokenType: ");
  printtoktype(token.type);
  printf("\n");
  if (token.type == TOKEN_CONSTANT) {
    printf("  - Token Value: %d\n", token.val);
  }
  printf("  - Token Lexeme: ");
  printlexeme();
  printf("\n");
  printf("  - Filepath: %s\n", token.filepath);
  printf("  - Line number: %d\n", token.row_num);
  printf("  - Column number: %d\n", token.col_num);
  printf("------------------------------\n");
}

int gettok() {
  // declare the current char * c and some lookaheads;
  // I believe we need at most 8 lookaheads to recognize C keywords.
  char *c, *lut1, *lut2, *lut3, *lut4, *lut5, *lut6, *lut7, *lut8;
  for (;;) {
    // I am not proud of this switch statement in someways. But I do
    // think its faster than average
    // There are 32 keywords in C
    // auto	break	case	char
    // const	continue	default	do
    // double	else	enum	extern
    // float	for	goto	if
    // int	long	register	return
    // short	signed	sizeof	static
    // struct	switch	typedef	union
    // unsigned	void	volatile	while
    switch (*(c = advance())) {
      case EOF:
        return -1;
      case 'a':
        lut1 = advance();  // 'u' ?
        lut2 = advance();  // 't' ?
        lut3 = advance();  // 'o' ?
        lut4 = advance();
        if (*lut1 == 'u' && *lut2 == 't' && *lut3 == 'o' && (isspace(*lut4) || *lut4 == EOF)) {
          token.type = TOKEN_KEYWORD;
          token.lexeme_start = c;
          token.lexeme_end = lut4;
          cp = lut4;
          return 0;
        }
        // otherwise we have an identifier, so reset the state and go there
        cp = lut1;
        goto id;
      case 'b':
        lut1 = advance();  // 'r' ?
        lut2 = advance();  // 'e' ?
        lut3 = advance();  // 'a' ?
        lut4 = advance();  // 'k' ?
        lut5 = advance();  // EOF/<whitespace> ?
        if (*lut1 == 'r' && *lut2 == 'e' && *lut3 == 'a' && *lut4 == 'k' && (isspace(*lut5) || *lut5 == EOF)) {
          token.type = TOKEN_KEYWORD;
          token.lexeme_start = c;
          token.lexeme_end = lut5;
          cp = lut5;
          return 0;
        }
        cp = lut1;
        goto id;
      case 'c':
        lut1 = advance();  // 'o' ?
        lut2 = advance();  // 'n' ?
        lut3 = advance();  // 't' ?
        lut4 = advance();  // 'i' ?
        lut5 = advance();  // 'n' ?
        lut6 = advance();  // 'u' ?
        lut7 = advance();  // 'e' ?
        lut8 = advance();  // EOF/<whitespace>?
        // is keyword continue?
        if (*lut1 == 'o' && *lut2 == 'n' && *lut3 == 't' && *lut4 == 'i' && *lut5 == 'n' && *lut6 == 'u' && *lut7 == 'e' && (isspace(*lut8) || *lut8 == EOF)) {
          token.type = TOKEN_KEYWORD;
          token.lexeme_start = c;
          token.lexeme_end = lut8;
          cp = lut8;
          return 0;
        }
        // case ?
        if (*lut1 == 'a' && *lut2 == 's' && *lut3 == 'e' && (isspace(*lut4) || *lut4 == EOF)) {
          token.type = TOKEN_KEYWORD;
          token.lexeme_start = c;
          token.lexeme_end = lut4;
          cp = lut4;
          return 0;
        }
        // char ?
        if (*lut1 == 'h' && *lut2 == 'a' && *lut3 == 'r' && (isspace(*lut4) || *lut4 == EOF)) {
          token.type = TOKEN_KEYWORD;
          token.lexeme_start = c;
          token.lexeme_end = lut4;
          cp = lut4;
          return 0;
        }
        // const ?
        if (*lut1 == 'o' && *lut2 == 'n' && *lut3 == 's' && *lut4 == 't' && (isspace(*lut5) || *lut5 == EOF)) {
          token.type = TOKEN_KEYWORD;
          token.lexeme_start = c;
          token.lexeme_end = lut5;
          cp = lut5;
          return 0;
        }
        cp = lut1;
        goto id;
      // default do or double
      case 'd':
        lut1 = advance();  // 'e'
        lut2 = advance();  // 'f'
        lut3 = advance();  // 'a'
        lut4 = advance();  // 'u'
        lut5 = advance();  // 'l'
        lut6 = advance();  // 't'
        lut7 = advance();  // EOF
        if (*lut1 == 'e' && *lut2 == 'f' && *lut3 == 'a' && *lut4 == 'u' && *lut5 == 'l' && *lut6 == 't' && (isspace(*lut7) || *lut7 == EOF)) {
          token.type = TOKEN_KEYWORD;
          token.lexeme_start = c;
          token.lexeme_end = lut7;
          cp = lut7;
          return 0;
        }
        if (*lut1 == 'o' && *lut2 == 'u' && *lut3 == 'b' && *lut4 == 'l' && *lut5 == 'e' && (isspace(*lut6) || *lut6 == EOF)) {
          token.type = TOKEN_KEYWORD;
          token.lexeme_start = c;
          token.lexeme_end = lut6;
          cp = lut6;
          return 0;
        }
        if (*lut1 == 'o' && (isspace(*lut2) || *lut2 == EOF)) {
          token.type = TOKEN_KEYWORD;
          token.lexeme_start = c;
          token.lexeme_end = lut2;
          cp = lut2;
          return 0;
        }
        cp = lut1;
        goto id;
      // else enum extern
      case 'e':
        lut1 = advance();
        lut2 = advance();
        lut3 = advance();
        lut4 = advance();

        // else
        if (*lut1 == 'l' && *lut2 == 's' && *lut3 == 'e' && (isspace(*lut4) || *lut4 == EOF)) {
          token.type = TOKEN_KEYWORD;
          token.lexeme_start = c;
          token.lexeme_end = lut4;
          cp = lut4;
          return 0;
        }

        // enum
        if (*lut1 == 'n' && *lut2 == 'u' && *lut3 == 'm' && (isspace(*lut4) || *lut4 == EOF)) {
          token.type = TOKEN_KEYWORD;
          token.lexeme_start = c;
          token.lexeme_end = lut4;
          cp = lut4;
          return 0;
        }
        cp = lut1;
        goto id;
      // float for
      case 'f':
        lut1 = advance();
        lut2 = advance();
        lut3 = advance();
        lut4 = advance();
        lut5 = advance();
        // float
        if (*lut1 == 'l' && *lut2 == 'o' && *lut3 == 'a' && *lut4 == 't' && (isspace(*lut5) || *lut5 == EOF)) {
          token.type = TOKEN_KEYWORD;
          token.lexeme_start = c;
          token.lexeme_end = lut5;
          cp = lut5;
          return 0;
        }
        if (*lut1 == 'o' && *lut2 == 'r' && (isspace(*lut3) || *lut3 == EOF)) {
          token.type = TOKEN_KEYWORD;
          token.lexeme_start = c;
          token.lexeme_end = lut4;
          cp = lut4;
          return 0;
        }
        cp = c;
        goto id;
      case 'g':
        lut1 = advance();
        lut2 = advance();
        lut3 = advance();
        lut4 = advance();
        if (*lut1 == 'o' && *lut2 == 't' && *lut3 == 'o' && (isspace(*lut4) || *lut4 == EOF)) {
          token.type = TOKEN_KEYWORD;
          token.lexeme_start = c;
          token.lexeme_end = lut4;
          cp = lut4;
          return 0;
        }
        goto id;
      case 'i':
        lut1 = advance();
        lut2 = advance();
        lut3 = advance();
        if (*lut1 == 'n' && *lut2 == 't' && (isspace(*lut3) || *lut3 == EOF)) {
          token.type = TOKEN_KEYWORD;
          token.lexeme_start = c;
          token.lexeme_end = lut3;
          cp = lut3;
          return 0;
        } else if (*lut1 == 'f' && (isspace(*lut2) || *lut2 == EOF)) {
          token.type = TOKEN_KEYWORD;
          token.lexeme_start = c;
          token.lexeme_end = lut2;
          cp = lut2;
          return 0;
        }
        // otherwise its an identifier so go there.
        // make sure you restore the state of the stream reader
        cp = lut1;
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
        token.lexeme_start = c;
        token.type = TOKEN_IDENTIFIER;
        token.col_num += 1;
        while (isalnum(*(c = advance()))) {
          token.col_num += 1;
        }
        token.lexeme_end = c;
        return 0;
      case '\n':
        token.row_num += 1;
      case '\t':
      case '\r':
      case ' ':
        continue;
      // STRLIT
      case '"':
        token.lexeme_start = c;
        token.type = TOKEN_STRLIT;
        while (*(c = advance()) != '"' && *c != EOF) {
        }
        token.lexeme_end = *c == EOF ? c : cp;
        return 0;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        token.lexeme_start = c;
        token.type = TOKEN_CONSTANT;
        // calculate the value here
        while (isdigit(*(c = advance()))) {
        }
        token.lexeme_end = c;
        return 0;
      case '+':
        token.lexeme_start = c;
        token.type = TOKEN_PUNCTUATOR;
        token.lexeme_end = advance();
        return 0;
      case '-':
        token.lexeme_start = c;
        token.type = TOKEN_PUNCTUATOR;
        token.lexeme_end = advance();
        return 0;
      case '/':
        token.lexeme_start = c;
        token.type = TOKEN_PUNCTUATOR;
        token.lexeme_end = advance();
        return 0;
      case '*':
        token.lexeme_start = c;
        token.type = TOKEN_PUNCTUATOR;
        token.lexeme_end = advance();
        return 0;
      case '(':
        token.lexeme_start = c;
        token.type = TOKEN_PUNCTUATOR;
        token.lexeme_end = advance();
        return 0;
      case ')':
        token.lexeme_start = c;
        token.type = TOKEN_PUNCTUATOR;
        token.lexeme_end = advance();
        return 0;
      default:
        // printf("%p\n", buffer);
        // printf("%s\n", buffer);
        // printf("%p\n", cp);
        printf("BAD\n");
        return -2;
    }
  }
}
