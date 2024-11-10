#include <stdio.h>
#include <string.h>

int numProductions;
char productions[50][50];
char firstSets[26][50];
int isFirstSetComputed[26];
char followSets[26][50];
int isFollowSetComputed[26];

// Checks if a symbol is a terminal
int isTerminal(char symbol) {
    return (symbol < 'A' || symbol > 'Z');
}

// Computes the FIRST set for a given non-terminal
void computeFirstSet(char nonTerminal) {
    int firstSetIndex = 0; // Index to track positions in the current FIRST set
    char currentFirstSet[50]; // Temporary array to store the current FIRST set

    // Loop through productions to find those of the form nonTerminal -> ...
    for (int prodIndex = 0; prodIndex < numProductions; prodIndex++) {

        // Check if the production's LHS matches the given non-terminal
        if (productions[prodIndex][0] == nonTerminal) {
            int rhsIndex = 2; // Start reading after '->' in the production
            int continueSearch = 0;

            // Traverse the RHS of the production to find FIRST set elements
            while (productions[prodIndex][rhsIndex] != '\0' && continueSearch == 0) {
                continueSearch = 1;

                // If it's a terminal, add it directly to the FIRST set
                if (isTerminal(productions[prodIndex][rhsIndex])) {
                    currentFirstSet[firstSetIndex] = productions[prodIndex][rhsIndex];
                    firstSetIndex++;
                    break;
                }

                // If it's a non-terminal, calculate its FIRST set if not already done
                char currentNonTerminal = productions[prodIndex][rhsIndex];
                if (!isFirstSetComputed[currentNonTerminal - 'A']) {
                    computeFirstSet(currentNonTerminal);
                }

                // Add elements from the FIRST set of this non-terminal
                int nestedFirstIndex = 0;
                while (firstSets[currentNonTerminal - 'A'][nestedFirstIndex] != '\0') {
                    currentFirstSet[firstSetIndex] = firstSets[currentNonTerminal - 'A'][nestedFirstIndex];

                    // If epsilon ('e') is present, continue to the next symbol in the RHS
                    if (firstSets[currentNonTerminal - 'A'][nestedFirstIndex] == 'e') {
                        rhsIndex++;
                        continueSearch = 0;
                    }
                    firstSetIndex++;
                    nestedFirstIndex++;
                }
            }
        }
    }
    currentFirstSet[firstSetIndex] = '\0'; // End of the FIRST set string
    strcpy(firstSets[nonTerminal - 'A'], currentFirstSet); // Save to the global FIRST array
    isFirstSetComputed[nonTerminal - 'A'] = 1; // Mark this non-terminal's FIRST set as computed
}

// Computes the FOLLOW set for a given non-terminal
void computeFollowSet(char nonTerminal) {
    int followSetIndex = 0;
    char currentFollowSet[50];

    // If the non-terminal is the start symbol, add '$' to its FOLLOW set
    if (nonTerminal == productions[0][0]) {
        currentFollowSet[followSetIndex] = '$';
        followSetIndex++;
    }

    // Loop through each production to find occurrences of the non-terminal in the RHS
    for (int prodIndex = 0; prodIndex < numProductions; prodIndex++) {
        int rhsIndex = 2;
        int includeLHSFollowSet;

        while (productions[prodIndex][rhsIndex] != '\0') {
            includeLHSFollowSet = 0;

            // If the non-terminal appears in the RHS of the production
            if (productions[prodIndex][rhsIndex] == nonTerminal) {
                // Check the next symbol in the RHS
                if (productions[prodIndex][rhsIndex + 1] != '\0') {

                    // If it's a terminal, add it directly to the FOLLOW set
                    if (isTerminal(productions[prodIndex][rhsIndex + 1])) {
                        currentFollowSet[followSetIndex] = productions[prodIndex][rhsIndex + 1];
                        followSetIndex++;
                        break;
                    }

                    // Add elements from the FIRST set of the following non-terminal
                    int nestedFirstIndex = 0;
                    while (firstSets[productions[prodIndex][rhsIndex + 1] - 'A'][nestedFirstIndex] != '\0') {
                        if (firstSets[productions[prodIndex][rhsIndex + 1] - 'A'][nestedFirstIndex] == 'e') {
                            includeLHSFollowSet = 1;
                            nestedFirstIndex++;
                            continue;
                        }

                        // Avoid duplicate entries in the FOLLOW set
                        int isDuplicate = 0;
                        for (int i = 0; i < followSetIndex; i++) {
                            if (firstSets[productions[prodIndex][rhsIndex + 1] - 'A'][nestedFirstIndex] == currentFollowSet[i]) {
                                isDuplicate = 1;
                                nestedFirstIndex++;
                                break;
                            }
                        }
                        if (isDuplicate) continue;

                        currentFollowSet[followSetIndex] = firstSets[productions[prodIndex][rhsIndex + 1] - 'A'][nestedFirstIndex];
                        followSetIndex++;
                        nestedFirstIndex++;
                    }
                }

                // If at the end of the RHS or epsilon is present, include FOLLOW of LHS
                if (productions[prodIndex][rhsIndex + 1] == '\0' || includeLHSFollowSet) {
                    if (productions[prodIndex][0] != nonTerminal) {
                        if (!isFollowSetComputed[productions[prodIndex][0] - 'A']) {
                            computeFollowSet(productions[prodIndex][0]);
                        }

                        int lhsFollowIndex = 0;
                        while (followSets[productions[prodIndex][0] - 'A'][lhsFollowIndex] != '\0') {
                            int isDuplicate = 0;
                            for (int i = 0; i < followSetIndex; i++) {
                                if (followSets[productions[prodIndex][0] - 'A'][lhsFollowIndex] == currentFollowSet[i]) {
                                    isDuplicate = 1;
                                    lhsFollowIndex++;
                                    break;
                                }
                            }
                            if (isDuplicate) continue;

                            currentFollowSet[followSetIndex] = followSets[productions[prodIndex][0] - 'A'][lhsFollowIndex];
                            followSetIndex++;
                            lhsFollowIndex++;
                        }
                    }
                }
            }
            rhsIndex++;
        }
    }
    currentFollowSet[followSetIndex] = '\0';
    strcpy(followSets[nonTerminal - 'A'], currentFollowSet);
    isFollowSetComputed[nonTerminal - 'A'] = 1;
}

int main() {
    printf("Enter the number of productions:\n");
    scanf("%d", &numProductions);

    printf("Enter the productions (in the form A->...):\n");
    for (int i = 0; i < numProductions; i++)
        scanf("%s", productions[i]);

    // Initialize computation tracking arrays
    for (int i = 0; i < 26; i++) {
        isFirstSetComputed[i] = 0;
        isFollowSetComputed[i] = 0;
    }

    // Compute FIRST sets for all non-terminals
    for (int i = 0; i < numProductions; i++) {
        if (!isFirstSetComputed[productions[i][0] - 'A']) {
            computeFirstSet(productions[i][0]);
        }
    }

    // Compute FOLLOW sets for all non-terminals
    for (int i = 0; i < numProductions; i++) {
        if (!isFollowSetComputed[productions[i][0] - 'A']) {
            computeFollowSet(productions[i][0]);
        }
    }

    // Display the FIRST sets
    printf("FIRST sets:\n");
    for (int i = 0; i < 26; i++) {
        if (isFirstSetComputed[i]) {
            printf("%c : %s\n", i + 'A', firstSets[i]);
        }
    }

    // Display the FOLLOW sets
    printf("FOLLOW sets:\n");
    for (int i = 0; i < 26; i++) {
        if (isFollowSetComputed[i]) {
            printf("%c : %s\n", i + 'A', followSets[i]);
        }
    }
}
