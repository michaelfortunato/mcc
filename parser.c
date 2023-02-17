/* Parser */
#include "parser.h"

#include "lexer.h"

Node *parse_expr();
Node *parse_expr_sub();
Node *parse_term();
Node *parse_term_sub();
Node *parse_factor();

Token lookahead;

void match(Token t) {
  if (lookahead.type == t.type) {
    gettok();
    lookahead = token;
  }
  printf("BAD");
  exit(1);
}

Node *parse_term_sub() {
  Node *term_sub_node = (Node *)malloc(sizeof(Node));
  Token t = {};
  if (lookahead.val == '+') {
    // consume '+' terminal
    t.type = TOKEN_PUNCTUATOR;
    Node *add_node = (Node *)malloc(sizeof(Node));
    add_node->type = ADD;
    term_sub_node->children[0] = add_node;
    term_sub_node->children[1] = parse_expr_sub();
  } else if (lookahead.val == '-') {
    // consume '-' terminal
    Node *subtract_node = (Node *)malloc(sizeof(Node));
    subtract_node->type = SUB;
    term_sub_node->children[0] = subtract_node;
    term_sub_node->children[1] = parse_term_sub();
  }
  return term_sub_node;
}

Node *parse_factor() {
  Node *factor_node = (Node *)malloc(sizeof(Node));
  return factor_node;
}

Node *parse_expr_sub() {
  printf("EXPR_SUB\n");
  Node *expr_sub_node = (Node *)malloc(sizeof(Node));
  expr_sub_node->type = EXPR_SUB;

  Token t = {};
  if (lookahead.val == '+') {
    // consume '+' terminal
    t.type = TOKEN_PUNCTUATOR;
    Node *add_node = (Node *)malloc(sizeof(Node));
    add_node->type = ADD;
    expr_sub_node->children[0] = add_node;
    expr_sub_node->children[1] = parse_expr_sub();
  } else if (lookahead.val == '-') {
    // consume '-' terminal
    Node *subtract_node = (Node *)malloc(sizeof(Node));
    subtract_node->type = SUB;
    expr_sub_node->children[0] = subtract_node;
    expr_sub_node->children[1] = parse_expr_sub();
  }
  return expr_sub_node;
}

Node *parse_term() {
  Node *term_node = (Node *)malloc(sizeof(Node));
  term_node->children[0] = parse_factor();
  term_node->children[1] = parse_term_sub();
  return term_node;
}

Node *parse_expr() {
  Node *expr_node = (Node *)malloc(sizeof(Node));
  expr_node->children[0] = parse_term();
  expr_node->children[1] = parse_expr_sub();
  return expr_node;
};

Node *parse() {
  gettok();
  return parse_expr();
}