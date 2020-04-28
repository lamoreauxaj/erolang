# Ero

This document will eventually become the main location of our language's documentation.
This will be a work in progress as this project evolves though, so I will likely
dedicate time to the documentation later.

## Operator Precedence

| Operators | Group name | Associativity |
|---|---|---|
| `!x`, `-x` | Unary | Not applicable |
| `x ^ y` | Exponentiation | Right |
| `x * y`, `x / y`, `x // y`, `x % y` | Multiplication | Left |
| `x + y`, `x - y` | Addition | Left |
| `x in y`, `x not in y`, `x is y`, `x is not y`, `x == y`, `x != y`, `x < y`, `x > y`, `x >= y`, `x <= y` | Comparison | Left |
| `x and y`, `x && y` | Conjunction | Left |
| `x xor y`, `x ^^ y` | Exclusive Disjunction | Left |
| `x or y`, `x \|\| y` | Disjunction | Left |
| `x = y`, `x += y`, `x -= y`, `x *= y`, `x /= y`, `x //= y`, `x %= y`, `x ^= y` | Assignment | Right |

## Syntactic Grammar

This is the exact definition of our language's syntactic grammar which we use to guide
our parsing efforts.

```
expression     -> equality ;
equality       -> comparison ( ( "!=" | "==" ) comparison )* ;
comparison     -> addition ((">" | ">=" | "<" | "<=") addition)* ;
addition       -> multiplication ( ( "-" | "+" ) multiplication)* ;
multiplication -> unary ((DIVIDE | TIMES | IDIVIDE | MOD) unary)*;
unary          -> (NOT | MINUS) unary | primary ;
primary        -> REAL | STRING | IDENTIFIER | LEFT_PAREN expression RIGHT_PAREN ;
```