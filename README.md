# Lexical Analyzer in C

A simple **Lexical Analyzer** implemented in C that reads a C source file and classifies lexemes into different token types.

## Features

- Identifies C keywords
- Detects identifiers
- Recognizes operators
- Classifies integer and floating-point constants
- Identifies separators and special characters
- Reads source code from a file (`code.c`)

## Technologies Used

- C Programming
- Standard C Libraries (`stdio.h`, `string.h`, `ctype.h`)

## Project Structure

```text
Lexical_Analyzer/
├── lexer.c    # Lexical analyzer implementation
├── code.c     # Input C source file
└── README.md  # Project documentation
```

## How to Compile and Run

```bash
gcc -Wall -Wextra lexer.c -o lexer
./lexer
```

## Sample Input

```c
int main()
{
    int num = 25;
    float value = 3.14;
    num = num + 10;
    return 0;
}
```

## Sample Output

```text
LEXEME               TOKEN TYPE
----------------------------------------
int                  KEYWORD
main                 IDENTIFIER
(                    SEPARATOR
)                    SEPARATOR
{                    SEPARATOR
int                  KEYWORD
num                  IDENTIFIER
=                    OPERATOR
25                   INTEGER CONSTANT
;                    SEPARATOR
float                KEYWORD
value                IDENTIFIER
=                    OPERATOR
3.14                 FLOAT CONSTANT
;                    SEPARATOR
num                  IDENTIFIER
=                    OPERATOR
num                  IDENTIFIER
+                    OPERATOR
10                   INTEGER CONSTANT
;                    SEPARATOR
return               KEYWORD
0                    INTEGER CONSTANT
;                    SEPARATOR
}                    SEPARATOR
```

*Note: The sample output is abbreviated. The analyzer's current implementation supports basic token recognition and may not handle all C language constructs.*

## Learning Outcomes

- Understanding lexical analysis and tokenization
- Practicing file handling in C
- Using character classification and string-handling functions
- Applying modular programming concepts

