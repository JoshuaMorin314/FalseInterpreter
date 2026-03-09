#ifndef STACK_H
#define STACK_H

// linked list to hold the stack
typedef struct Node{
    int value;
    struct Node* next;
} Node;

// creates an empty stack
extern Node** create_stack();

// pushes value onto the stack
extern void push(Node** stack,int value);

// pops the top of the stack off
extern int pop(Node** stack);

// outputs the top stack value without popping it
extern int peek(Node** stack);

// output methods
extern void print_stack(Node** stack);

#endif // STACK_H