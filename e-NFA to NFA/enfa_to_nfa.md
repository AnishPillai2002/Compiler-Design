# NFA with Epsilon Transition to NFA Without Epsilon Transitions

## Overview

This program converts an NFA (Non-deterministic Finite Automaton) with epsilon transitions (ε) to an NFA without epsilon transitions. It takes a set of states, an alphabet, transitions (including epsilon transitions), and computes the equivalent NFA without epsilon transitions using epsilon closures.

## Features

- Input the number of states, alphabet, transitions, start state, and final states.
- Calculates epsilon closures for each state.
- Converts NFA with epsilon transitions to NFA without epsilon transitions.
- Outputs both the original transition table and the new transition table without epsilon transitions.

## Algorithm

### Steps to Convert NFA with Epsilon Transitions to NFA Without Epsilon Transitions:

1. **Initialize Transition Table:**
   - Define the structure of a `Node` to represent states.
   - Create a 2D array (`transition[20][20]`) to store transitions where each element is a linked list of states.
   
2. **Input the Alphabets and States:**
   - Read the number of alphabets (`no_alphabets`) and states (`no_states`) from the user.
   - Read the starting state, number of final states (`nofinal`), and the final states from the user.
   - Store the input alphabet and final states.

3. **Input the Transitions:**
   - Read the number of transitions (`no_transition`) from the user.
   - For each transition, input the starting state, symbol, and the target state.
   - Insert the transitions into the transition table using the `insertIntoTransitionTable` function.

4. **Print the Transition Table:**
   - Display the transition table with the list of states that each state transitions to for each symbol, including epsilon.

5. **Calculate Epsilon Closure:**
   - Define a 2D array `e_closure[20][20]` to store the epsilon closures for each state.
   - For each state, calculate the epsilon closure using the `findclosure` function by recursively checking all states reachable through epsilon transitions.
   
6. **Print Epsilon Closures:**
   - Display the epsilon closures for each state, which is the set of all states that can be reached from that state via epsilon transitions.

7. **Initialize New Transition Table Without Epsilon:**
   - Create a new 2D transition table (`newTransition[20][20]`) to store transitions for the NFA without epsilon transitions.
   
8. **Update Transition Table Without Epsilon:**
   - For each state and each symbol (excluding epsilon), compute the transitions based on the epsilon closures.
   - For each state in the epsilon closure, check for transitions based on the input symbol and update the new transition table accordingly using the `unionclosure` function.

9. **Print the NFA Without Epsilon Transitions:**
   - Display the transition table for the equivalent NFA without epsilon transitions, where each state points to a set of states for each input symbol, excluding epsilon.

10. **End:**
   - The program concludes by outputting the equivalent NFA without epsilon transitions.


