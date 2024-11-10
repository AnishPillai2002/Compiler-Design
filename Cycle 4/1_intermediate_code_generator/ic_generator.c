#include <stdio.h> 
#include <string.h> 

// Function to generate intermediate code for a specific operator
void gen_code_for_operator(char *inp, char operator, char *reg) 
{    
    int i = 0, j = 0; 
    char temp[100]; // Temporary array to store the modified expression after processing each operator

    // Loop through each character in the input expression
    while (inp[i] != '\0') 
    { 
        // Check if the current character matches the operator to be processed
        if (inp[i] == operator) { 
            // Print the operation in a three-address code format:
            // Operator    Destination    Operand1    Operand2
            printf("%c\t%c\t%c\t%c\n", operator, *reg, inp[i - 1], inp[i + 1]); 
            
            // Replace the processed subexpression with the register holding the result
            temp[j - 1] = *reg;  
            
            i += 2; // Skip the operator and the next operand, as they have been processed
            (*reg)--; // Decrement the register to move to the next available register
            continue; // Continue to the next character in the input expression
        } 
        
        // Copy the current character to the temp array
        temp[j] = inp[i]; 
        i++; 
        j++; 
    } 
    
    temp[++j] = '\0'; // Null-terminate the temp array
    strcpy(inp, temp); // Update the input expression with the modified temp array
} 
 
// Function to generate intermediate code for all operators based on precedence
void gen_code(char *inp) 
{ 
    // Initialize the register for storing results; 'Z' will be used for the first result, 'Y' for the next, and so on
    char reg = 'Z';  
    
    // Generate code for each operator in order of precedence
    // Highest to lowest precedence: '/', '*', '+', '-', '='
    gen_code_for_operator(inp, '/', &reg); 
    gen_code_for_operator(inp, '*', &reg); 
    gen_code_for_operator(inp, '+', &reg); 
    gen_code_for_operator(inp, '-', &reg); 
    gen_code_for_operator(inp, '=', &reg); 
} 

// Main function to take input and call the intermediate code generator
int main() 
{ 
    char inp[100]; // Array to hold the input expression
    printf("Enter expression:\n\n"); 
    scanf("%s", inp); // Read the input expression from the user
    printf("Op  \tDestn\tArg1\tArg2\n"); // Header for the output table
    gen_code(inp); // Generate intermediate code for the expression
} 
