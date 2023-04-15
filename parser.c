/* Parser */
#include "parser.h"

#include "lexer.h"

Node *parse_expr();
Node *parse_expr_sub();
Node *parse_term();
Node *parse_term_sub();
Node *parse_factor();

Token lookahead;

typedef const char *uterminal;

void match(const char *t) {
  printf("match %s", t);
  if (compare(t)) {
    gettok();
    lookahead = token;
  }
  exit(1);
}

Node *parse_term_sub() {
  printf("AT TERM_SUB\n");
  Node *term_sub_node = (Node *)malloc(sizeof(Node));
  if (compare("+")) {
    match("+");  // consume '+' terminal
    Node *add_node = (Node *)malloc(sizeof(Node));
    add_node->type = ADD;
    term_sub_node->children[0] = add_node;
    term_sub_node->children[1] = parse_expr_sub();
  } else if (compare("-")) {
    match("-");  // consume '-' terminal
    Node *subtract_node = (Node *)malloc(sizeof(Node));
    subtract_node->type = SUB;
    term_sub_node->children[0] = subtract_node;
    term_sub_node->children[1] = parse_term_sub();
  }
  return term_sub_node;
}

Node *parse_factor() {
  printf("AT FACTOR\n");
  Node *factor_node = (Node *)malloc(sizeof(Node));
  printtok();
  gettok();
  printtok();
  return factor_node;
}

Node *parse_expr_sub() {
  printf("AT EXPR_SUB_NODE\n");
  Node *expr_sub_node = (Node *)malloc(sizeof(Node));
  expr_sub_node->type = EXPR_SUB;
  // printtok();

  if (compare('+')) {
    match("+");  // consume '+' terminal
    Node *add_node = (Node *)malloc(sizeof(Node));
    add_node->type = ADD;
    expr_sub_node->children[0] = add_node;
    expr_sub_node->children[1] = parse_expr_sub();
  } else if (compare("-")) {
    match("-");  // consume '0' terminal
    Node *subtract_node = (Node *)malloc(sizeof(Node));
    subtract_node->type = SUB;
    expr_sub_node->children[0] = subtract_node;
    expr_sub_node->children[1] = parse_expr_sub();
  }
  return expr_sub_node;
}

Node *parse_term() {
  printf("AT TERM_NODE\n");
  Node *term_node = (Node *)malloc(sizeof(Node));
  term_node->children[0] = parse_factor();
  term_node->children[1] = parse_term_sub();
  return term_node;
}

Node *parse_expr() {
  printf("AT EXPR_NODE\n");
  Node *expr_node = (Node *)malloc(sizeof(Node));
  expr_node->children[0] = parse_term();
  expr_node->children[1] = parse_expr_sub();
  return expr_node;
};

Node *parse() {
  gettok();
  return parse_expr();
}