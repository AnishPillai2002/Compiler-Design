# Non-Deterministic Finite Automaton (NFA) with Epsilon Transitions

This program implements a Non-Deterministic Finite Automaton (NFA) with epsilon transitions. It takes user input for states, alphabet symbols, and transitions, and then displays the transition table along with the epsilon closures for each state.

## Features
- Handles multiple states and symbols.
- Allows for epsilon transitions (denoted as 'e').
- Displays the transition table.
- Computes and displays epsilon closures for each state.

## Algorithm

1. **Initialize Variables:**
   - Create a transition table using a 2D array of linked lists.
   - Initialize arrays to store the alphabet and state information.

2. **Input the Number of Alphabets and States:**
   - Read the number of symbols (alphabets) and states for the automaton.

3. **Input the Alphabet Symbols:**
   - Input each symbol of the alphabet. Handle epsilon ('e') as a special case.

4. **Input the Transitions:**
   - For each transition, input the start state, symbol, and end state.
   - Insert the transition into the transition table as a linked list.

5. **Insert Transitions into the Table:**
   - For each transition, use the `insertIntoTransitionTable` function to find the correct position in the transition table.
   - Append the new state to the list of transitions for the given state and symbol.

6. **Display the Transition Table:**
   - For each state, display all transitions for each symbol in the alphabet, formatted in a readable table.

7. **Initialize Epsilon Closure Arrays:**
   - Initialize an array to store the epsilon closures for each state.

8. **Compute Epsilon Closures:**
   - For each state, call the recursive function `findclosure` to compute the epsilon closure by following epsilon transitions (if any).

9. **Display Epsilon Closures:**
   - For each state, print its epsilon closure (list of states reachable via epsilon transitions).

10. **End Program:**
   - Once all closures are displayed, the program finishes.

