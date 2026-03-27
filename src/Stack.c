// Stack.c
#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"

// creates an empty stack
Node** create_stack(){
    Node** stack=(Node**)malloc(sizeof(Node**));
    *stack=NULL;
    return stack;
}

// creates a new Linked List node
Node* create_node(Data value){
    Node* node=(Node*)malloc(sizeof(Node*));
    node->value=value;
    node->next=NULL;
    return node;
}

// pushes value onto the stack
void push(Node** stack,Data value){
    Node* top=create_node(value);
    top->next=*stack;
    *stack=top;
    return;
}

// pops the top of the stack off
Data pop(Node** stack){
    if(*stack==NULL){
        fprintf(stderr, "ERROR: stack underflow\n");
        Data _;
        _.tag = TYPE_INT;
        _.val.integer = 0xFFFFFFFF;
        return _;
    }
    Node* top=*stack;
    Data output=top->value;
    *stack=top->next;
    free(top);
    return output;
}

// outputs the top stack value without popping it
Data peek(Node** stack){
    if(*stack==NULL){
        fprintf(stderr, "ERROR: stack underflow\n");
        Data _;
        _.tag = TYPE_INT;
        _.val.integer = 0xFFFFFFFF;
        return _;
    }
    return (*stack)->value;
}

// prints out the stack (runs into an issue if the stack is big but this funtion isn't used for anything but testing)
void print_stack(Node** stack){
    Node* current=*stack;
    char s[100]="[";
    int ind=(current!=NULL)?1:2;
    while (current!=NULL){
        char buffer[20];
        sprintf(buffer,"%d,",current->value);
        int i;
        for(i=0; buffer[i]!='\0'; i++){
            s[ind]=buffer[i];
            ind++;
        }
        current=current->next;
    }
    s[ind-1]=']';
    printf("Top -> %s\n",s);
    return;
}

int empty(Node** stack) {
    return *stack==NULL;
}