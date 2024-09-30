#include<stdio.h>
#include<stdlib.h>
#define MAX_STATES 20

struct Node{
        int state;
        struct Node *next;
};

//Helper method to find the index of the given symbol in the alphabet array
int findalpha(char symbol,char alphabet[20]){

    for(int i=0;i<20;i++){
        if(alphabet[i] == symbol){
            return i;
        }
    }
    return -1;
}


//Helper method to fill the transition table
void insertIntoTransitionTable(int start,char symbol,int end,struct Node *transition[20][20],char alphabet[20]){
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->state = end;
    temp->next = NULL;

    int symbolIndex = findalpha(symbol,alphabet); //Find the index of the symbol in the alphabet array
    if (symbolIndex == -1){
        printf("Error: Symbol not found in the alphabet array\n");
        exit(0);
    }
    

    //If there is no transition for the given symbol, create a new linked list
    if(transition[start][symbolIndex] == NULL){
        transition[start][symbolIndex] = temp;
    }
    else{ //Hndling Multiple Transitions:
        struct Node *p = transition[start][symbolIndex];
        while(p->next != NULL){
            p = p->next;
        }
        p->next = temp;
    }
}

//Helper method to find the epsilon closure of a state
void findclosure(int start_state, int current_state, struct Node *transition[][MAX_STATES], int e_closure[], int visited[]) {
    visited[current_state] = 1;
    e_closure[current_state] = 1;

    struct Node *temp = transition[current_state][0]; // Assuming epsilon transitions are stored in transition[current_state][0]
    while (temp != NULL) {
        if (!visited[temp->state]) {
            findclosure(start_state, temp->state, transition, e_closure, visited);
        }
        temp = temp->next;
    }
}

int main(){

    //Transition table storing linked lists of transitions for each state and alphabet.
    struct Node *transition[20][20] = {NULL}; 

    int no_alphabets;
    char alphabet[20];
    printf("Enter the number of alphabets: ");
    scanf("%d",&no_alphabets);
    


    int no_states;
    printf("\nEnter the number of states: ");
    scanf("%d",&no_states);


    int no_transition;
    printf("\nEnter no of transition:");
    scanf("%d",&no_transition);

    getchar(); // Clear the newline character left by the previous scanf

    //Read the alphabets
    printf("NOTE:- [ use letter e as epsilon]\n");
    printf("NOTE:- [e must be first character ,if it is present]\n");
    printf("NOTE:- [add space before each alphabet]\n");
    printf("\nEnter alphabets:");
    getchar();  

    for (int i = 0; i < no_alphabets; i++) {
        scanf(" %c", &alphabet[i]);  // " %c" will skip any leading spaces
    }

    alphabet[no_alphabets]='\0'; //null turminal character

    //Read the transitions
    printf("NOTE:- [Transition is in the form–> qno alphabet qno]\n");
    printf("NOTE:- [States number must start from zero]\n");
    printf("\nEnter transition\n(state1 <space> alphabet <space> state2?)\n");
    for (int i = 0; i < no_transition; i++){
        int start,end; //states
        char symbol; //alphabet
        scanf("%d %c %d",&start,&symbol,&end);
        insertIntoTransitionTable(start,symbol,end,transition,alphabet);
    }

    printf("\n");
    
    //Print the transition table
    printf("Transition Table:\n");
    printf("States/Symbols\t");
    for(int i = 0; i < no_alphabets; i++){
        printf("%c\t", alphabet[i]);
    }
    printf("\n");
    printf("———————————————————————————————————————\n");
    for(int i = 0; i <no_states; i++){
        printf("q%d\t\t|", i);
        for(int j = 0; j < no_alphabets; j++){
            struct Node *temp = transition[i][j];
            if (temp == NULL) {
                printf(" -\t");
            } else {
                while(temp != NULL){
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


    // E-closure of states
    printf("\nE-closure of states……\n");
    printf("—————————–\n");
    for (int i = 0; i < no_states; i++) {
        int visited[MAX_STATES] = {0}; // visited array
        int e_closure[MAX_STATES] = {0}; // epsilon closure array for each state

        // Find the epsilon closure of the current state
        findclosure(i, i, transition, e_closure, visited);

        // Print the epsilon closure of the current state
        printf("\nE-closure(q%d): {", i);
        for (int j = 0; j < MAX_STATES; j++) {
            if (e_closure[j] != 0) {
                printf("%d,", j);
            }
        }
        printf("}\n");
    
    }
    
}