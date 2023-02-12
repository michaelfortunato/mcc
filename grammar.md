## Initial Commit
We start with a simple math grammar. This grammar can generate strings like:
```
4 + 40 * 2
(4 + 4) * 2
4 - 1 + 3
4 / 1 - 3
```
For today, we work with the following grammar $G$. 

_Starting symbol:_ 
```
S = expr
```
Terminals = "*", "+", "/", "-", "(", ")", digit

_Productions:_
```bnf
<expr> ::= <expr> "+" <term> 
  | <expr> "-" <term>
  | <term>
<term> ::= <term> "*" <factor>
  | <term> "/" <factor>
  | <factor>
<factor> ::= digit 
  | "(" <expr> ")"
```

We left factor the non terminals, which gives us the following equivalent grammar
$G'$

_Productions:_
```bnf
<expr> ::= <term> <expr_sub> 
<expr_sub> ::= "+" <expr_sub> | "-" <expr_sub> | ""
<term> ::= <factor> <term_sub>
<term_sub> ::= "*" <term_sub> | "/" <term_sub> | ""
<factor> ::= digit | "(" <expr> ")"
```

