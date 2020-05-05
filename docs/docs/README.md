---
sidebar: auto
---

# Ero Documentation

## Features


## Bug List

Here lies a list of bugs. As we get to bugs, we will remove them. Considering
the compiler has existed for such a short period of time, this list does contain
some relatively major bugs as expected.

- [ ] Statements delimiters are not implemented. Semicolons should optionally separate
statements and multiline statements should be parsed correctly
- [ ] Block statements require brace to be on the same line as expression and keyword.
This is due to newline tokens preventing parsing if they occur in between.
- [ ] Constructions can only take at most two arguments. This is due to an incomplete
implementation of our argument passing.
- [ ] Constructions can only return at most one argument. To be able to return multiple
arguments we have to be able to deal with tuples which are an unimplemented feature.
- [ ] Invalid real expressions cause useless error messages since the compiler
crashses due to trying to parse the expressions.

## Todo

- [ ] Implement geometry postulates as a library. Should include the core figure types
which are ... todo
- [ ] Todo: finish this todo list among other things
