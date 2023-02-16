# C Compiler

## Lexer

Run the lexer on a .c file and it will output a list of tokens.
```bash
make
```

## Parser

### $\mathrm{FIRST}(\alpha)$

Consider the following productions of a grammar:
```bnf
<stmt> ::= "expr" ";"
  | "if" "(" "expr" ")" <stmt>
  | "for" "(" <optexpr> ";" <optexpr> ";" <optexpr> ")" <stmt>
  | "other"
<optexpr> ::= "" | "expr"
```

Let $\alpha$ be a string of grammar symbols; i.e., let $\alpha$ be a sequence of terminals and/or nonterminals.
Then we define $\mathrm{FIRST}(\alpha)$ to be the set of terminals that appear as the first symbols of one or 
more strings of terminals generated from $\alpha$. 

Here are some examples, given the terminals and nonterminals defined above

- If $\alpha = \{stmt\}$, then $\mathrm{FIRST}(\alpha) = \{ \mathrm{expr}, \mathrm{if}, \mathrm{for}, \mathrm{other}\}$
- If $\alpha = \{\mathrm{expr} \mathrm{;} \}$, then $\mathrm{FIRST}(\alpha) = \{ \mathrm{expr} \}$

### Predictive Parsing
Recursive descent parsing is a top-down method of syntax analysis in which a set of recursive procedure is used to process the input. Each nonterminal in the grammar is associated with a procedure.
Predictive parsing is a specialization of recursive descent parsing in which the lookahead symbol unabmiguoulsy determines the flow of control through the procedure body for each nonterminal. 
#### _match(t)_
The book defines a helper method called match(t) which returns true and 
advances the $lookahead$ if lookahead is equal to $t$, otherwise it returns false.
```c
int match(terminal t) {
  if (t == lookahead) {
    lookahead = nextTerminal(t);
    return 1;
  }
  return 0;
}
```

