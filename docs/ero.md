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
| `x = y`, `x += y`, `x -= y`, `x *= y`, `x /= y`, `x //= y`, `x %= y`, `x ^= y`, ... | Assignment | Right |

## Syntactic Grammar

This is the exact definition of our language's syntactic grammar which we use to guide
our parsing efforts.

```
statements     -> statement*
statement      -> expression | if | while
if             -> IF LEFT_PAREN expression RIGHT_PAREN LEFT_BRACKET statements RIGHT_BRACKET
while          -> WHILE LEFT_PAREN expression RIGHT_PAREN LEFT_BRACE statements RIGHT_BRACE
expression     -> assignment
assignment     -> disjunction (ASSIGN disjunction)* 
disjunction    -> xdisjunction (OR xdisjunction)*
xdisjunction   -> conjunction (XOR conjunction)*
conjunction    -> comparison (AND comparison)*
comparison     -> addition ((IS | EQUALS | NOT_EQUALS | (NOT IS) | (NOT IN) | IN | LESS | GREATER | LESS_OR_EQUAL | GREATER_OR_EQUAL) addition)*
addition       -> multiplication ((MINUS | PLUS) multiplication)*
multiplication -> exponentiation ((DIVIDE | TIMES | IDIVIDE | MOD) exponentiation)*
exponentiation -> unary (POWER unary)*
unary          -> (NOT | MINUS) unary | primary
primary        -> real | string | identifier | group | tuple | call | index
string         -> STRING
real           -> REAL
identifier     -> IDENTIFIER
group          -> LEFT_PAREN expression RIGHT_PAREN
tuple          -> LEFT_PAREN (expression COMMA)+ expression? RIGHT_PAREN
call           -> expression tuple
index          -> expression LEFT_BRACKET expression RIGHT_BRACKET
```
