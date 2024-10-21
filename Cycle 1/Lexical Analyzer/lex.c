#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// List of keywords in C
char keywords[32][20] = {
    "int", "char", "float", "double", "void", "struct", "union", "enum",
    "static", "extern", "const", "volatile", "unsigned", "signed", "short",
    "long", "typedef", "return", "continue", "break", "for", "while", "do",
    "if", "else", "switch", "case", "default", "goto", "sizeof", "typedef",
    "printf"
};

// Check if the given word is a keyword
bool isKeyword(char *word) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return true;  // Return true if the word matches a keyword
        }
    }
    return false;  // Return false if not found in the list
}

// Check if the word is a number (constant)
bool isNumber(char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!isdigit(word[i])) {
            return false;  // If any character is not a digit, it's not a number
        }
    }
    return true;  // All characters are digits, so it's a number
}

// Check if the character is an operator
bool isOperator(char ch) {
    char operators[] = "=+-*/><.%";
    for (int i = 0; i < strlen(operators); i++) {
        if (ch == operators[i]) {
            return true;  // Return true if it's a valid operator
        }
    }
    return false;
}

// Check if the character is a special symbol
bool isSpecial(char ch) {
    char special[] = ";{}()?,!";
    for (int i = 0; i < strlen(special); i++) {
        if (ch == special[i]) {
            return true;  // Return true if it's a special symbol
        }
    }
    return false;
}

// Check if the word is a valid identifier
bool isValidIdentifier(char *word) {
    // First character should be a letter or underscore
    if (!isalpha(word[0]) && word[0] != '_') {
        return false;
    }
    
    // Remaining characters can be letters, digits, or underscore
    for (int i = 1; word[i] != '\0'; i++) {
        if (!isalnum(word[i]) && word[i] != '_') {
            return false;
        }
    }

    return true;
}

int main() {
    FILE *src = fopen("input.txt", "r");  // Open file to read input
    if (src == NULL) {
        printf("Failed to open input file.\n");
        return 1;
    }

    char token, temp[200];  // Token to store character, temp to store words
    int i = 0;

    // Read the file character by character
    while ((token = fgetc(src)) != EOF) {
        // Ignore spaces and newlines
        if (token == ' ' || token == '\n') {
            continue;
        }
        // Handle string literals properly
        else if (token == '"') {
            i = 0;
            temp[i++] = token;
            while ((token = fgetc(src)) != EOF && token != '"') {
                temp[i++] = token;
            }
            temp[i++] = '"';
            temp[i] = '\0';
            printf("String Literal : %s\n", temp);
        }
        // Check if the character is a special symbol
        else if (isSpecial(token)) {
            printf("Special : %c\n", token);
        }
        // Check if the character is an operator
        else if (isOperator(token)) {
            printf("Operator : %c\n", token);
        }
        // Handle identifiers, keywords, or constants
        else {
            i = 0;  // Reset index for each new word
            while (token != ' ' && token != '\n' && token != EOF && 
                   !isSpecial(token) && !isOperator(token)) {
                temp[i++] = token;  // Build the word character by character
                token = fgetc(src);  // Get the next character
            }
            temp[i] = '\0';  // Null-terminate the word

            // Skip if the token is empty (prevent blank identifiers)
            if (strlen(temp) == 0) {
                continue;
            }

            // Check if the word is a number
            if (isNumber(temp)) {
                printf("Constant : %s\n", temp);
            }
            // Check if the word is a keyword
            else if (isKeyword(temp)) {
                printf("Keyword : %s\n", temp);
            }
            // Otherwise, it's an identifier, but check if it's valid
            else if (isValidIdentifier(temp)) {
                printf("Identifier : %s\n", temp);
            }

            // If the loop stopped because of a delimiter, push it back for the next check
            if (token != EOF) {
                fseek(src, -1, SEEK_CUR);
            }
        }
    }

    fclose(src);  // Close the file
    return 0;
}
