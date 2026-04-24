#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "Tokenizer.h"

Data variables[26];

/**** FALSE FUNCTIONS *****/
/* Stack */
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

/* Arithmatic */
void add(Node** stack) {
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

/* Logical */
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

/* Variables */
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
    while(!(token.tag==STR && token.val.string==NULL)){ // until the string has been completely consumed
        if(token.tag==OP){ // if token is an operation
            processlexeme(stack,token.val.character); // execute based on value
        }else if(token.tag==STR){ // if token is an string (not including functions)
            printf("%s",token.val.string); // print the string
        }else{ // if token is an integer, function string, or variable name
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
        printf("ERROR: Invalid conditional expression found");
        exit(EXIT_FAILURE);
    }
    // if b holds a non-zero value then execute the code in the value of a
    if(b.val.integer!=0){
        execute(stack,a.val.string);
    }
}

void loop(Node** stack) {
    //Grab the function to execute
    Data fun = pop(stack);
    if (fun.tag != FUN) {
        printf("ERROR: cannot execute unless the top of the stack specifies a function");
        exit(EXIT_FAILURE);
    }

    //Grab the conditional body function
    Data cond = pop(stack);
    if (cond.tag != FUN) {
        printf("ERROR: conditional body must be a function");
    }

    //Execute the conditional body
    execute(stack, cond.val.string);

    //Check for valid data
    Data ctn = pop(stack);
    if (ctn.tag != INT) {
        printf("ERROR: conditional body must return an integer.");
        exit(EXIT_FAILURE);
    }

    //Execute the main body while loop control is not zero
    while (ctn.val.integer != 0) {
        execute(stack, fun.val.string);

        //Update loop control
        execute(stack, cond.val.string);
        ctn = pop(stack);
        if (ctn.tag != INT) {
            printf("ERROR: conditional body must return an integer.");
            exit(EXIT_FAILURE);
        }
    }

}

/* I/O Controls */
void read(Node** stack){
    /* 
    NOTE: waits until enter is pressed to read any input
    then reads from the buffer until the whole input gets consumed 
    before looking for more input
    */
    char c='\0';
    scanf("%c",&c);
    Data* ret=(Data*)malloc(sizeof(Data));
    ret->val.integer=(int)(c);
    ret->tag=INT;
    push(stack,*ret);
}

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