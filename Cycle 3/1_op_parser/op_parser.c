#include <stdio.h>
#include <string.h>

void main() {
    // Define variables
    char stack[20], input[20], opt[10][10][2], ter[10];
    int i, j, k, n, top = 0, col, row;

    // Initialize the operator precedence table to null characters
    for (i = 0; i < 10; i++) {
        stack[i]='\0';
        input[i]='\0';
        for (j = 0; j < 10; j++) {
            opt[i][j][0] = '\0';
        }
    }

    // Input number of terminals (operators)
    printf("Enter the number of terminals:\n");
    scanf("%d", &n);

    // Input terminal symbols (operators) as a string
    printf("\nEnter the terminals:\n");
    scanf("%s", ter);

    // Input operator precedence values for each pair of terminals
    printf("\nEnter the table values:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("Enter the precedence between %c and %c: ", ter[i], ter[j]);
            scanf("%s", opt[i][j]);
        }
    }

    // Display the operator precedence table
    printf("\n**** OPERATOR PRECEDENCE TABLE ****\n");
    printf("\t");
    for (i = 0; i < n; i++) {
        printf("%c\t", ter[i]);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("%c", ter[i]);
        for (j = 0; j < n; j++) {
            printf("\t%c", opt[i][j][0]);
        }
        printf("\n");
    }

    // Initialize stack with end-of-input marker '$'
    stack[top] = '$';

    // Input the string to be parsed and append '$'
    printf("\nEnter the input string: ");
    scanf("%s", input);
    strcat(input, "$");

    // Begin parsing
    int currentinput = 0; // Index for input string
    printf("\nSTACK\t\t\tINPUT STRING\t\t\tACTION\n");
    printf("\n%s\t\t\t%s\t\t\t", stack, input);

    // Parsing loop
    while (currentinput < strlen(input)) {
        // Find column and row in the precedence table for top of stack and current input symbol
        for (k = 0; k < n; k++) {
            if (stack[top] == ter[k]){
                row = k;
            } 
            if (input[currentinput] == ter[k]){
                col = k;
            } 
        }

        // Check if we reached the end of both stack and input, indicating success
        if ((stack[top] == '$') && (input[currentinput] == '$')) {
            printf("String is accepted\n");
            break;
        }
        
        // Shift operation if precedence is '<' or '='
        else if ((opt[row][col][0] == '<') || (opt[row][col][0] == '=')) {
            stack[++top] = '<'; // Push precedence symbol onto stack
            stack[++top] = input[currentinput]; // Push current input symbol onto stack
            printf("Shift %c", input[currentinput]);
            currentinput++; // Move to next input symbol
        } 
        
        // Reduce operation if precedence is '>'
        else if (opt[row][col][0] == '>') {
            while (stack[top] != '<') {
                --top; // Pop from stack until '<' is encountered
            }
            top--; // Discard the '<'
            printf("Reduce");
        } 
        
        // If no valid action, string is rejected
        else {
            printf("\nString is not accepted\n");
            break;
        }

        // Print current stack contents
        printf("\n");
        for (k = 0; k <= top; k++) {
            printf("%c", stack[k]);
        }
        printf("\t\t\t");

        // Print remaining input
        for (k = currentinput; k < strlen(input); k++) {
            printf("%c", input[k]);
        }
        printf("\t\t\t");
    }

    getchar(); // Pause at the end to view results in some environments
}
