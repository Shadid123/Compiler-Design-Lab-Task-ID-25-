# Tokenizer & Lexical Analyzer (C++)

Author: Shadid Mazumder (GitHub: Shadid123)
Assignment: Compiler Design Lab Task (ID-25)

## Overview

A simple tokenizer / lexical analyzer written in C++. The lexer recognizes:
- Identifiers and keywords
- Integer and floating-point numeric literals
- String and character literals
- Single-line (`//`) and block (`/* ... */`) comments
- Single- and multi-character operators (e.g. `==`, `!=`, `<=`, `>=`, `++`, `--`, `&&`, `||`, `+=`, etc.)
- Delimiters (parentheses, braces, semicolons, commas, etc.)

The lexer prints each token with its type, lexeme (raw token text), and source position (line:column).

## Files

- `tokenizer.cpp` — Main C++ implementation of the lexer.
- `README.md` — This file.

## Requirements

- A C++17-compatible compiler (g++ or clang++)

## Build

Compile with:

```bash
g++ -std=c++17 tokenizer.cpp -O2 -o lexer
```

## Usage

Run the lexer on a source file:

```bash
./lexer sample.c
```

Or feed input via stdin:

```bash
cat sample.c | ./lexer
```

Output format (one token per line):

```
TokenType "lexeme"  at line:column
```

Example (default format):

```
Keyword "int"  at 1:1
Identifier "main"  at 1:5
Delimiter "("  at 1:9
...
[EOF] at 10:1
```

## Sample input (sample.c)

```c
int main() {
  // single-line comment
  float x = 3.14;
  int i = 0;
  if (x > 0) x += 1;
  /* block
     comment */
  printf("Hello, \"world\"!\n");
  return 0;
}
```


## Sample output



```
This --> Identifier  
is --> Identifier  
a --> Identifier  
int --> Keyword  
sum --> Identifier  
= --> Operator  
10 --> Constant (Integer)  
; --> Separator  
and --> Identifier  
a --> Identifier  
+ --> Operator  
b --> Identifier  
= --> Operator  
20 --> Constant (Integer)  
; --> Separator
```



## Token types recognized

- Keyword
- Identifier
- Integer (Constant)
- Float
- String
- Operator
- Delimiter / Separator
- Comment
- EOF

## Limitations

- Not a fully standard-compliant C lexer. Hex/octal/binary/scientific numeric formats are not fully supported.
- Preprocessor directives are not specially parsed.
- String and character escape semantics are not fully validated — string content is treated as a lexeme.

## Extensions (suggested)

- Add support for hex/octal/scientific notation and character literal parsing.
- Output tokens in machine-readable formats (JSON/CSV).
- Build a parser on top of the lexer.

## Academic integrity

This implementation was prepared for the Compiler Design Lab assignment (ID-25). Ensure your submission complies with your institution's collaboration and plagiarism policies.
