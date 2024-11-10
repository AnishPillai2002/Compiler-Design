#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char input_buffer[20];
int input_pointer=0;
char output_buffer[20];

// Utility function to remove 'e' (epsilon) from the output
void remove_epsilon() {
    char temp_buffer[20];
    int temp_index = 0;
    for (int ptr = 0; ptr < strlen(output_buffer); ptr++) {
        if (output_buffer[ptr] != 'e') {
            temp_buffer[temp_index++] = output_buffer[ptr];
        }
    }
    temp_buffer[temp_index] = '\0';
    strcpy(output_buffer, temp_buffer);
}

void E() {
    strcpy(output_buffer, "TE'");  // Initial output buffer value

    printf("E=%-25s", output_buffer);
    printf("E->TE'\n");

    T();
    EPRIME();
}

void T() {
    remove_epsilon();  // Remove 'e' (epsilon) from the current output

    int t_index = 0;
    while (t_index < strlen(output_buffer)) {
        if (output_buffer[t_index] == 'T') {
            break;
        }
        t_index++;
    }

    // Space for T=FT'
    for (int i = strlen(output_buffer); i >= t_index; i--) {
        output_buffer[i + 2] = output_buffer[i];
    }

    output_buffer[t_index++] = 'F';
    output_buffer[t_index++] = 'T';
    output_buffer[t_index++] = '\'';

    printf("E=%-25s", output_buffer);
    printf("T->FT'\n");

    F();
    TPRIME();
}

void F() {
    remove_epsilon();  // Remove 'e' (epsilon) from the current output

    int f_index = 0;
    while (f_index < strlen(output_buffer)) {
        if (output_buffer[f_index] == 'F') {
            break;
        }
        f_index++;
    }

    if (input_buffer[input_pointer] == 'i') {
        output_buffer[f_index] = 'i';
        input_pointer++;

        printf("E=%-25s", output_buffer);
        printf("F->id\n");

    } else if (input_buffer[input_pointer] == '(') {
        input_pointer++;  // Advance input pointer

        E();

        if (input_buffer[input_pointer] == ')') {
            input_pointer++;  // Advance input pointer

            for (int i = strlen(output_buffer); i >= f_index; i--) {
                output_buffer[i + 2] = output_buffer[i];
            }

            output_buffer[f_index++] = '(';
            output_buffer[f_index++] = 'E';
            output_buffer[f_index++] = ')';

            printf("E=%-25s", output_buffer);
            printf("F->(E)\n");
        }

    } else {
        printf("\n \t Syntax error");
        exit(1);
    }
}

void TPRIME() {
    remove_epsilon();  // Remove 'e' (epsilon) from the current output

    int tprime_index = 0;
    while (tprime_index < strlen(output_buffer)) {
        if (output_buffer[tprime_index] == 'T' && output_buffer[tprime_index + 1] == '\'') {
            break;
        }
        tprime_index++;
    }

    if (input_buffer[input_pointer] == '*') {
        for (int i = strlen(output_buffer); i >= tprime_index; i--) {
            output_buffer[i + 2] = output_buffer[i];
        }

        output_buffer[tprime_index++] = '*';
        output_buffer[tprime_index++] = 'F';
        output_buffer[tprime_index++] = 'T';
        output_buffer[tprime_index++] = '\'';

        printf("E=%-25s", output_buffer);
        printf("T'->*FT'\n");

        input_pointer++;

        F();
        TPRIME();
    } else {
        output_buffer[tprime_index] = 'e';
        output_buffer[tprime_index + 1] = 'e';

        for (int i = tprime_index + 1; i <= strlen(output_buffer); i++) {
            output_buffer[i] = output_buffer[i + 1];
        }

        printf("E=%-25s", output_buffer);
        printf("T'->e\n");
    }
}

void EPRIME() {
    remove_epsilon();  // Remove 'e' (epsilon) from the current output

    int eprime_index = 0;
    while (eprime_index < strlen(output_buffer)) {
        if (output_buffer[eprime_index] == 'E' && output_buffer[eprime_index + 1] == '\'') {
            break;
        }
        eprime_index++;
    }

    if (input_buffer[input_pointer] == '+') {
        for (int i = strlen(output_buffer); i >= eprime_index; i--) {
            output_buffer[i + 2] = output_buffer[i];
        }

        output_buffer[eprime_index++] = '+';
        output_buffer[eprime_index++] = 'T';
        output_buffer[eprime_index++] = 'E';
        output_buffer[eprime_index++] = '\'';

        printf("E=%-25s", output_buffer);
        printf("E->+TE'\n");

        input_pointer++;

        T();
        EPRIME();
    } else {
        output_buffer[eprime_index] = 'e';

        for (int i = eprime_index + 1; i <= strlen(output_buffer); i++) {
            output_buffer[i] = output_buffer[i + 1];
        }

        printf("E=%-25s", output_buffer);
        printf("E'->e\n");
    }
}

int main() {
    // Display the grammar rules
    printf("\nGrammar without left recursion:");
    printf("\n\t\t E->TE' \n\t\t E'->+TE'|e \n\t\t T->FT' ");
    printf("\n\t\t T'->*FT'|e \n\t\t F->(E)|i");

    // Take input expression from the user
    printf("\n Enter the input expression: ");
    scanf("%s", input_buffer);

    // Display headers for output
    printf("Expressions\t Sequence of production rules\n");

    // Start parsing with E (expression)
    E();

    // Check for invalid characters in the input
    for (int i = 0; i < strlen(input_buffer); i++) {
        if (input_buffer[i] != '+' && input_buffer[i] != '*' && input_buffer[i] != '(' && input_buffer[i] != ')'
            && input_buffer[i] != 'i') {
            printf("\nSyntax error: Invalid character '%c' in input", input_buffer[i]);
            return 0;
        }
    }
    return 0;
}
