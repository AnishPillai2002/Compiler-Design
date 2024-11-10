#include<stdio.h>
#include<stdlib.h>
#define MAX_STATES 20

struct Node {
    int state;
    struct Node *next;
};

// Helper method to find the index of the given symbol in the alphabet array
int findalpha(char symbol, char alphabet[20], int no_alphabets) {
    for(int i = 0; i < no_alphabets; i++) {
        if(alphabet[i] == symbol) {
            return i;
        }
    }
    return -1;
}

// Helper method to fill the transition table
void insertIntoTransitionTable(int start, char symbol, int end, struct Node *transition[20][20], char alphabet[20], int no_alphabets) {
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->state = end;
    temp->next = NULL;

    int symbolIndex = findalpha(symbol, alphabet, no_alphabets); // Find the index of the symbol in the alphabet array
    if (symbolIndex == -1) {
        printf("Error: Symbol not found in the alphabet array\n");
        exit(0);
    }

    // If there is no transition for the given symbol, create a new linked list
    if (transition[start][symbolIndex] == NULL) {
        transition[start][symbolIndex] = temp;
    }
    else { // Handling Multiple Transitions
        struct Node *p = transition[start][symbolIndex];
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = temp;
    }
}

// Helper method to find the epsilon closure of a state
void findclosure(int current_state, struct Node *transition[][MAX_STATES], int e_closure[], int visited[], int no_alphabets) {
    visited[current_state] = 1;
    e_closure[current_state] = 1;

    // Assuming epsilon transitions are stored in transition[current_state][no_alphabets - 1]
    struct Node *temp = transition[current_state][no_alphabets - 1];
    while (temp != NULL) {
        if (!visited[temp->state]) {
            findclosure(temp->state, transition, e_closure, visited, no_alphabets);
        }
        temp = temp->next;
    }
}

// Helper method to merge epsilon closures
void unionclosure(int state, int e_closure[], int final_closure[], int no_states) {
    for (int i = 0; i < no_states; i++) {
        if (e_closure[i]) {
            final_closure[i] = 1;
        }
    }
}

void convertToNFAWithoutEpsilon(struct Node *transition[20][20], int no_states, int no_alphabets, int e_closure[][MAX_STATES], char alphabet[20]) {
    // NFA without epsilon transitions
    struct Node *newTransition[20][20] = {NULL};

    // For each state, for each alphabet (excluding epsilon), update the new transition table
    for (int state = 0; state < no_states; state++) {
        for (int symbolIndex = 0; symbolIndex < no_alphabets - 1; symbolIndex++) { // Exclude epsilon
            int combinedClosure[MAX_STATES] = {0};

            // Traverse all states in the epsilon closure of the current state
            for (int closureState = 0; closureState < no_states; closureState++) {
                if (e_closure[state][closureState]) {
                    struct Node *temp = transition[closureState][symbolIndex]; // Original transition for that symbol
                    while (temp != NULL) {
                        // For each target state of the original transition, include the epsilon closure of that state
                        unionclosure(temp->state, e_closure[temp->state], combinedClosure, no_states);
                        temp = temp->next;
                    }
                }
            }

            // Insert the combined closure into the new transition table
            for (int targetState = 0; targetState < no_states; targetState++) {
                if (combinedClosure[targetState]) {
                    insertIntoTransitionTable(state, alphabet[symbolIndex], targetState, newTransition, alphabet, no_alphabets);
                }
            }
        }
    }

    // Print the new transition table without epsilon transitions
    printf("\nEquivalent NFA without epsilon transitions:\n");
    printf("States/Symbols\t");
    for (int i = 0; i < no_alphabets - 1; i++) { // Exclude epsilon from the output
        printf("%c\t", alphabet[i]);
    }
    printf("\n");
    printf("———————————————————————————————————————\n");
    for (int i = 0; i < no_states; i++) {
        printf("q%d\t\t|", i);
        for (int j = 0; j < no_alphabets - 1; j++) {
            struct Node *temp = newTransition[i][j];
            if (temp == NULL) {
                printf(" -\t");
            } else {
                while (temp != NULL) {
                    printf("%d", temp->state);
                    temp = temp->next;
                    if (temp != NULL) {
                        printf(",");
                    }
                }
                printf("\t");
            }
        }
        printf("\n");
    }
}

int main() {

    // Transition table storing linked lists of transitions for each state and alphabet
    struct Node *transition[20][20] = {NULL}; 

    int no_alphabets;
    char alphabet[20];
    printf("Enter the number of alphabets: ");
    scanf("%d", &no_alphabets);

    int no_states;
    printf("\nEnter the number of states: ");
    scanf("%d", &no_states);

    int start;
    printf("Enter the start state: ");
    scanf("%d", &start);

    int nofinal;
    printf("Enter the number of final states: ");
    scanf("%d", &nofinal);

    int no_transition;
    printf("\nEnter no of transitions: ");
    scanf("%d", &no_transition);

    getchar(); // Clear the newline character left by the previous scanf

    // Read the final states
    int finalstate[20];
    printf("Enter the final states: ");
    for (int i = 0; i < nofinal; i++) {
        scanf("%d", &finalstate[i]);
    }

    // Read the alphabets
    printf("NOTE:- [Use letter 'e' as epsilon]\n");
    printf("NOTE:- [e must be the last character, if present]\n");
    printf("NOTE:- [Add space before each alphabet]\n");
    printf("\nEnter alphabets: ");
    getchar();  

    for (int i = 0; i < no_alphabets; i++) {
        scanf(" %c", &alphabet[i]);  // " %c" will skip any leading spaces
    }

    alphabet[no_alphabets] = '\0'; // Null terminator character

    // Read the transitions
    printf("NOTE:- [Transition is in the form -> qno alphabet qno]\n");
    printf("NOTE:- [States number must start from zero]\n");
    printf("\nEnter transitions (state1 alphabet state2):\n");
    for (int i = 0; i < no_transition; i++) {
        int start, end; // States
        char symbol; // Alphabet
        scanf("%d %c %d", &start, &symbol, &end);
        insertIntoTransitionTable(start, symbol, end, transition, alphabet, no_alphabets);
    }

    printf("\n");

    // Print the transition table
    printf("Transition Table:\n");
    printf("States/Symbols\t");
    for (int i = 0; i < no_alphabets; i++) {
        printf("%c\t", alphabet[i]);
    }
    printf("\n");
    printf("———————————————————————————————————————\n");
    for (int i = 0; i < no_states; i++) {
        printf("q%d\t\t|", i);
        for (int j = 0; j < no_alphabets; j++) {
            struct Node *temp = transition[i][j];
            if (temp == NULL) {
                printf(" -\t");
            } else {
                while (temp != NULL) {
                    printf("%d", temp->state);
                    temp = temp->next;
                    if (temp != NULL) {
                        printf(",");
                    }
                }
                printf("\t");
            }
        }
        printf("\n");
    }

    // NFA without epsilon
    printf("Equivalent NFA without epsilon\n");
    printf("-----------------------------------\n");

    // Epsilon closure of each state
    int e_closure[20][20] = {0};
    for (int i = 0; i < no_states; i++) {
        int visited[20] = {0};
        findclosure(i, transition, e_closure[i], visited, no_alphabets);
    }

    // Print epsilon closures
    printf("Epsilon Closures:\n");
    for (int i = 0; i < no_states; i++) {
        printf("Epsilon closure of state %d: {", i);
        for (int j = 0; j < no_states; j++) {
            if (e_closure[i][j]) {
                printf("%d,", j);
            }
        }
        printf("}\n");
    }

    // Convert to NFA without epsilon transitions
    convertToNFAWithoutEpsilon(transition, no_states, no_alphabets, e_closure, alphabet);

    return 0;
}
