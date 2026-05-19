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

Example:

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

Running `./lexer sample.c` on the sample above produces a token-per-line output similar to:

```
Keyword "int"  at 1:1
Identifier "main"  at 1:5
Delimiter "("  at 1:9
Delimiter ")"  at 1:10
Delimiter "{"  at 1:12
Comment "// single-line comment"  at 2:3
Keyword "float"  at 3:3
Identifier "x"  at 3:9
Operator "="  at 3:11
Float "3.14"  at 3:13
Delimiter ";"  at 3:17
Keyword "int"  at 4:3
Identifier "i"  at 4:7
Operator "="  at 4:9
Integer "0"  at 4:11
Delimiter ";"  at 4:12
Keyword "if"  at 5:3
Delimiter "("  at 5:6
Identifier "x"  at 5:7
Operator ">"  at 5:9
Integer "0"  at 5:11
Delimiter ")"  at 5:12
Identifier "x"  at 5:14
Operator "+="  at 5:16
Integer "1"  at 5:19
Delimiter ";"  at 5:20
Comment "/* block\n     comment */"  at 6:3
Identifier "printf"  at 8:3
Delimiter "("  at 8:10
String "\"Hello, \\\"world\\\"!\\n\""  at 8:11
Delimiter ")"  at 8:34
Delimiter ";"  at 8:35
Keyword "return"  at 9:3
Integer "0"  at 9:10
Delimiter ";"  at 9:11
Delimiter "}"  at 10:1
[EOF] at 10:2
```

Note: exact column numbers may vary slightly depending on how tabs/spaces are counted in the input file.

## Token types recognized

- Keyword
- Identifier
- Integer
- Float
- String
- Operator
- Delimiter
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
