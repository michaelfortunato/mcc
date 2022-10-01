#ifndef LEXER_H
#define LEXER_H

/**
 * @brief The types a token can be. Taken from ISO:9899:2.01x.
 *
 */
typedef enum {
  TOKEN_KEYWORD,    /**< A C keyword, reserved as per spec. */
  TOKEN_IDENTIFIER, /**< A C identifier, see spec for details. */
  TOKEN_CONSTANT,   /**< A C constant, see spec for details. */
  TOKEN_STRLIT,     /**< A C string literal, see spec for details. */
  TOKEN_PUNCTUATOR  /**< A C puntuator literal, see spec for details. */
} TokenType;

/**
 * @brief Token emmited by lexer
 *
 */
typedef struct Token {
  TokenType type;
  int val; /**< If type is TOKEN_CONSTANT */
  char *lexeme_start;
  char *lexeme_end;
  char *filepath; /**< The source file where the token occurred */
  int line_num;   /**< The line number in the source file where the token occurred */
  int line_col;   /**< The offset in the line where the token started */
} Token;
extern Token token;
int tokenize_file(char *filepath);
int gettok();

#endif