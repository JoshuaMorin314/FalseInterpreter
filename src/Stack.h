#ifndef STACK_H
#define STACK_H

//Implement a tagged union for data storage
typedef enum DT{
    TYPE_INT,
    TYPE_STR,
    TYPE_FUN
} DT;

typedef struct Data{
    DT tag;
    union {
        int integer;
        char* string;
    } val;
} Data;

// linked list to hold the stack
typedef struct Node{
    struct Data value;
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