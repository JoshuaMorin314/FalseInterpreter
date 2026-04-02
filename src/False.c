#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "Tokenizer.h"

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
    if (idx.tag != INT) {
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

//Arithmatic
void plus(Node** stack) {
    Data a = pop(stack);
    Data b = pop(stack);
    Data* ret = (Data*)malloc(sizeof(Data*));
    if (a.tag == INT && b.tag == INT) {
        ret->val.integer = a.val.integer + b.val.integer;
        ret->tag = INT;
        push(stack, *ret);
    }
}

/* Control Flow */
// executes a string of False code (used for lambdas and the entire program)
void execute(Node** stack,char* str){
    char** at=&str;
    Data token=gettoken(at);
    while(!(token.tag==STR && token.val.string==NULL)){ // until the string has been completely consumed (Note: if "" is in the code it'll end early)
        if(token.tag==OP){ // if token is an operation
            processlexeme(stack,token.val.character); // execute based on value
        }else{
            push(stack,token); // add the stack
        }
        token=gettoken(at);
    }
}

