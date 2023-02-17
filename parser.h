#ifndef PARSER_H
#define PARSER_H
/**
 * @brief Our grammar so far (we start with simple math grammar)
 * <expr> ::= <term> <expr_sub>
 * <expr_sub> ::= "+" <expr_sub> | "-" <expr_sub> | ""
 * <term> ::= <factor> <term_sub>
 * <term_sub> ::= "*" <term_sub> | "/" <term_sub> | ""
 * <factor> ::= number | "(" <expr> ")"
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
  struct Node *children[10];
} Node;

Node *parse();

/**
 * @brief Consider the following situation where the production bodies
 * have circular dependencies.
 * A -> BC;
 * B -> A;
 * How can we remove the circular dependency?
 * I'd just relabel A
 * A -> BC;
 * B -> A';
 */

#endif