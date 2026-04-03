#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "Tokenizer.h"

Data variables[26];

/**** FALSE FUNCTIONS *****/
//Stack
void drop(Node** stack) {
    pop(stack);
}

void dup(Node** stack) {
    push(stack, peek(stack));
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

//Arithmatic
void plus(Node** stack) {
    Data a=pop(stack);
    Data b=pop(stack);
    Data* ret=(Data*)malloc(sizeof(Data*));
    if(a.tag==INT && b.tag==INT){
        ret->val.integer=a.val.integer+b.val.integer;
        ret->tag=INT;
        push(stack,*ret);
    }
}

void subtract(Node** stack){
    Data a=pop(stack);
    Data b=pop(stack);
    Data* ret=(Data*)malloc(sizeof(Data*));
    if(a.tag==INT && b.tag==INT){
        ret->val.integer=b.val.integer-a.val.integer;
        ret->tag=INT;
        push(stack,*ret);
    }
}

void multiply(Node** stack){
    Data a=pop(stack);
    Data b=pop(stack);
    Data* ret=(Data*)malloc(sizeof(Data*));
    if(a.tag==INT && b.tag==INT){
        ret->val.integer=a.val.integer*b.val.integer;
        ret->tag=INT;
        push(stack,*ret);
    }
}

void divide(Node** stack){
    Data a=pop(stack);
    Data b=pop(stack);
    Data* ret=(Data*)malloc(sizeof(Data*));
    if(a.tag==INT && b.tag==INT){
        ret->val.integer=b.val.integer/a.val.integer;
        ret->tag=INT;
        push(stack,*ret);
    }
}

//Logical
void negate(Node** stack){
    Data a=pop(stack);
    Data* ret=(Data*)malloc(sizeof(Data*));
    if(a.tag==INT){
        ret->val.integer=-1*a.val.integer;
        ret->tag=INT;
        push(stack,*ret);
    }
}

void and(Node** stack){
    Data a=pop(stack);
    Data b=pop(stack);
    Data* ret=(Data*)malloc(sizeof(Data*));
    if(a.tag==INT && b.tag==INT){
        ret->val.integer=a.val.integer&b.val.integer;
        ret->tag=INT;
        push(stack,*ret);
    }
}

void or(Node** stack){
    Data a=pop(stack);
    Data b=pop(stack);
    Data* ret=(Data*)malloc(sizeof(Data*));
    if(a.tag==INT && b.tag==INT){
        ret->val.integer=a.val.integer|b.val.integer;
        ret->tag=INT;
        push(stack,*ret);
    }
}

void not(Node** stack){
    Data a=pop(stack);
    Data* ret=(Data*)malloc(sizeof(Data*));
    if(a.tag==INT){
        ret->val.integer=~a.val.integer;
        ret->tag=INT;
        push(stack,*ret);
    }
}

void greater(Node** stack){
    Data a=pop(stack);
    Data b=pop(stack);
    Data* ret=(Data*)malloc(sizeof(Data*));
    if(a.tag==INT && b.tag==INT){
        ret->val.integer=(b.val.integer>a.val.integer)?-1:0;
        ret->tag=INT;
        push(stack,*ret);
    }
}

void equal(Node** stack){
    Data a=pop(stack);
    Data b=pop(stack);
    Data* ret=(Data*)malloc(sizeof(Data*));
    if(a.tag==INT && b.tag==INT){
        ret->val.integer=(b.val.integer==a.val.integer)?-1:0;
        ret->tag=INT;
        push(stack,*ret);
    }
}

//Variables
void store(Node** stack){
    Data top=peek(stack);
    if(top.tag!=VAR){
        printf("ERROR: cannot store unless the top of the stack specifies a variable");
        exit(EXIT_FAILURE);
    }
    char c=top.val.character;
    pop(stack);
    Data value=pop(stack);     //Get data from the stack
    variables[c-'a']=value;    //Do the thing
}

void fetch(Node** stack){
    Data top=peek(stack);
    if(top.tag!=VAR){
        printf("ERROR: cannot fetch unless the top of the stack specifies a variable");
        exit(EXIT_FAILURE);
    }
    pop(stack);
    char c=top.val.character;
    push(stack,variables[c-'a']);
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

void conditional(Node** stack){
    // check if b is a valid input (i.e. an lambda function)
    Data a=pop(stack);
    if(a.tag!=FUN){
        printf("ERROR: cannot execute unless the top of the stack specifies a function");
        exit(EXIT_FAILURE);
    }
    // check if b is a valid input (i.e. an integer)
    Data b=pop(stack);
    if(b.tag!=INT){
        printf("ERROR: cannot execute unless the top of the stack specifies a function");
        exit(EXIT_FAILURE);
    }
    // if b holds a non-zero value then execute the code in the value of a
    if(b.val.integer!=0){
        execute(stack,a.val.string);
    }
}

//void loop(struct Node**);

/* I/O Controls */
//void read(Node** stack); // one character at a time or multiple?

void emit(Node** stack){
    Data top=pop(stack);
    switch(top.tag){
        case INT:
            printf("%c",top.val.integer); 
            break;
        case STR:
            printf("%s",top.val.string); 
            break;
        case FUN:
            printf("[%s]",top.val.string); 
            break;
        case VAR:
            printf("%c",top.val.character); 
            break;
        // case OP: // shouldn't be possible
        // default: // shouldn't be possible
    }
}

void write(Node** stack){
    Data top=pop(stack);
    switch(top.tag){
        case INT:
            printf("%d",top.val.integer); 
            break;
        // otherwise just give the pointer? (maybe just only allow this for integers)
        case STR:
            printf("@%p",top.val.string); 
            break;
        case FUN:
            printf("@%p",top.val.string); 
            break;
        case VAR:
            printf("%d",top.val.character); 
            break;
        // case OP: // shouldn't be possible
        // default: // shouldn't be possible
    }
}