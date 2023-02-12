#ifndef PARSER_H
#define PARSER_H
/**
 * @brief Our grammar so far (we start with simple math grammar)
 * <expr> ::= <term> <expr_sub>
 * <expr_sub> ::= "+" <expr_sub> | "-" <expr_sub> | ""
 * <term> ::= <factor> <term_sub>
 * <term_sub> ::= "*" <term_sub> | "/" <term_sub> | ""
 * <factor> ::= digit | "(" <expr> ")"k
 */
typedef enum {
  EXPR,
  EXPR_SUB,
  TERM,
  TERM_SUB,
  FACTOR,
  DIGIT,
  ADD,
  SUB,
  MUL,
  DIV
} NodeType;

typedef struct Node {
  NodeType type;
  Node **children;
} Node;

Node *parse(int(gettok)());

#endif