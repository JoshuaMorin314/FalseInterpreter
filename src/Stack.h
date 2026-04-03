#ifndef STACK_H
#define STACK_H

//Implement a tagged union for data storage
typedef enum DT{
    INT, // val.integer holds a number 
    STR, // val.string holds a string containing the inside of a set of quotation marks ""
    FUN, // val.string holds a string containing the inside of a set of square brackets []
    VAR, // val.character holds a single letter
    OP   // val.character holds one of the operation characters
} DT;

typedef struct Data{
    DT tag;             // the type of token being stored
    union {
        int integer;    // if tag is INT
        char* string;   // if tag is STR or FUN
        char character; // if tag is VAR or OP
    } val;
} Data;

// linked list to hold the stack
typedef struct Node{
    Data value; 
    struct Node* next;
} Node;

// creates an empty stack
extern Node** create_stack();

// pushes value onto the stack
extern void push(Node** stack, Data value);

// pops the top of the stack off
extern Data pop(Node** stack);

// outputs the top stack value without popping it
extern Data peek(Node** stack);

// output methods
extern void print_stack(Node** stack);

// checks if empty
extern int empty(Node** stack);

#endif // STACK_H