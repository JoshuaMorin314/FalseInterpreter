#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

Data variables[26];

/**** FALSE FUNCTIONS *****/
//Stack
void dup(Node** stack) {
    push(stack, peek(stack));
}

void drop(Node** stack) {
    pop(stack);
}

void swap(Node** stack) {
    Data v1 = pop(stack);
    Data v2 = pop(stack);
    push(stack, v1);
    push(stack, v2);
}

void rot(Node** stack) {
    Data v1 = pop(stack);
    Data v2 = pop(stack);
    Data v3 = pop(stack);
    push(stack, v2);
    push(stack, v1);
    push(stack, v3);
}

void pick(Node** stack) {
    Data idx = pop(stack);
    if (idx.tag != TYPE_INT) {
        printf("Type Error: Pick index must be int");
        exit(EXIT_FAILURE);
    }
    
    Node* traverse = *stack;
    for(int i = idx.val.integer; i != 0; i--) {
        traverse = traverse->next;
    }
    push(stack, traverse->value);
}

//Variables
void store(Node** stack, char ch) {
    Data val = pop(stack);        //Get data from the stack
    variables[ch - 'a'] = val;    //Do the thing
}

void fetch(Node** stack, char ch) {
    push(stack, variables[ch - 'a']);
}


//Control Flow
char* getlambda(Node** stack) {
    Data lmb = pop(stack);
    if (lmb.tag == TYPE_FUN) {
        return lmb.val.string;
    } else {
        return "ERROR";
    }
}


//Arithmatic
void plus(Node** stack) {
    Data a = pop(stack);
    Data b = pop(stack);
    Data* ret = (Data*)malloc(sizeof(Data*));
    if (a.tag == TYPE_INT && b.tag == TYPE_INT) {
        ret->val.integer = a.val.integer + b.val.integer;
        ret->tag = TYPE_INT;
        push(stack, *ret);
    }
}