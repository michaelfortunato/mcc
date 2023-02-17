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
 * @brief prints TokenType to io.
 *
 */
void printtoktype(TokenType toktype);

/**
 * @brief Token emmited by lexer
 *
 */
typedef struct Token {
  TokenType type;
  int val;            /**< If type is TOKEN_CONSTANT */
  char *lexeme_start; /**< closed endpoint */
  char *lexeme_end;   /**< open endpoint */
  char *filepath;     /**< The source file where the token occurred */
  int row_num;        /**< The line number in the source file where the token occurred */
  int col_num;        /**< The offset in the line where the token started */
} Token;
extern Token token;
int tokenize_file(char *filepath);

/**
 * @brief Advances the lexer to the next token.
 * @returns Returns 0 if successful, -1 if at end of stream, and 1 if error.
 */
int gettok();

/**
 * @brief Prints the token to the current i/o device along with its lexeme
 * primarly used for debugging.
 */
void printtok();

/**
 * @brief Prints the lexeme of the token, avoiding sentinels in the buffer
 *
 */
void printlexeme();

unsigned short int compare(const char *value);

#endif