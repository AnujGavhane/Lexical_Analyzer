
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// List of 32 C90 keywords
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

// Check whether a word is a keyword
int isKeyword(const char *word)
{
    int i;

    for (i = 0; i < 32; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

// Check whether a character is an operator
int isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == '%' || ch == '=' ||
            ch == '<' || ch == '>' || ch == '!' ||
            ch == '&' || ch == '|' || ch == '^' ||
            ch == '~');
}

// Check whether a character is a separator
int isSeparator(char ch)
{
    return (ch == '(' || ch == ')' ||
            ch == '{' || ch == '}' ||
            ch == '[' || ch == ']' ||
            ch == ';' || ch == ',' ||
            ch == '.' || ch == ':' || ch == '?');
}

// Check whether a string represents a floating constant
int isFloat(const char *word)
{
    int i, dot = 0, digit = 0;

    for (i = 0; word[i] != '\0'; i++)
    {
        if (word[i] == '.')
            dot++;
        else if (isdigit((unsigned char)word[i]))
            digit++;
        else
            return 0;
    }

    return (dot == 1 && digit > 0);
}

// Check whether a string contains only digits
int isInteger(const char *word)
{
    int i;

    if (word[0] == '\0')
        return 0;

    for (i = 0; word[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)word[i]))
            return 0;
    }

    return 1;
}

// Display the token and its category
void displayToken(const char *word)
{
    if (isKeyword(word))
        printf("%-20s KEYWORD\n", word);
    else if (isInteger(word))
        printf("%-20s INTEGER CONSTANT\n", word);
    else if (isFloat(word))
        printf("%-20s FLOAT CONSTANT\n", word);
    else
        printf("%-20s IDENTIFIER\n", word);
}

int main(void)
{
    FILE *fp;
    char word[MAX];
    int ch, next, i;

    // Open the source file
    fp = fopen("code.c", "r");

    if (fp == NULL)
    {
        printf("Error: Cannot open code.c\n");
        return 1;
    }

    printf("%-20s TOKEN TYPE\n", "LEXEME");
    printf("----------------------------------------\n");

    // Read the file character by character
    while ((ch = fgetc(fp)) != EOF)
    {
        // Skip whitespace
        if (isspace((unsigned char)ch))
            continue;

        // Collect identifiers, keywords and numbers
        if (isalnum((unsigned char)ch) || ch == '_')
        {
            i = 0;
            word[i++] = (char)ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isalnum((unsigned char)ch) ||
                    ch == '_' || ch == '.'))
            {
                if (i < MAX - 1)
                    word[i++] = (char)ch;
            }

            word[i] = '\0';

            // Put back the character that ended the token
            if (ch != EOF)
                ungetc(ch, fp);

            displayToken(word);
        }
        // Recognize operators
        else if (isOperator((char)ch))
        {
            word[0] = (char)ch;
            word[1] = '\0';

            next = fgetc(fp);

            // Check common two-character operators
            if (next != EOF &&
                ((ch == '+' && next == '+') ||
                 (ch == '-' && next == '-') ||
                 (ch == '=' && next == '=') ||
                 (ch == '!' && next == '=') ||
                 (ch == '<' && (next == '=' || next == '<')) ||
                 (ch == '>' && (next == '=' || next == '>')) ||
                 (ch == '&' && next == '&') ||
                 (ch == '|' && next == '|') ||
                 (ch == '+' && next == '=') ||
                 (ch == '-' && next == '=') ||
                 (ch == '*' && next == '=') ||
                 (ch == '/' && next == '=') ||
                 (ch == '%' && next == '=')))
            {
                word[1] = (char)next;
                word[2] = '\0';
            }
            else if (next != EOF)
            {
                ungetc(next, fp);
            }

            printf("%-20s OPERATOR\n", word);
        }
        // Recognize separators
        else if (isSeparator((char)ch))
        {
            printf("%-20c SEPARATOR\n", ch);
        }
        // Report unsupported characters
        else
        {
            printf("%-20c UNKNOWN TOKEN\n", ch);
        }
    }

    // Close the source file
    fclose(fp);

    return 0;
}

