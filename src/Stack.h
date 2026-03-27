#ifndef STACK_H
#define STACK_H

typedef union Data{
    int integer;
    char* string;
} Data;

// linked list to hold the stack
typedef struct Node{
    union Data value;
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
extern Data empty(Node** stack);

#endif // STACK_H