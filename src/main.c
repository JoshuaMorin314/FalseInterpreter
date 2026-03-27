#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "Tokenizer.h"

void teststack(){
    Node** stack=create_stack();
    int top;
    // test push
    printf("PUSH:\n");
    push(stack,0);
    push(stack,1);
    push(stack,-1);
    push(stack,0x7FFFFFFF);
    push(stack,0x80000000);
    print_stack(stack);
    // test pop
    top=pop(stack);
    printf("POP:\nvalue: %d\n",top);
    print_stack(stack);
    // test peek
    top=peek(stack);
    printf("PEEK:\nvalue: %d\n",top);
    print_stack(stack);
    // test underflow
    pop(stack);
    pop(stack);
    pop(stack);
    pop(stack);
    printf("EMPTY:\n");
    print_stack(stack);
    printf("UNDERFLOW:\n");
    peek(stack);
    pop(stack);
}

int main(){
    char* programstring = "0 0[ß^$$47>\\58\\>&][48-\\10*+]#%[$1>][$1-]#[\\$0=~][*]#%.";
    char** hahareference = &programstring;

    char* funny = (char*)malloc(10*sizeof(char));
    funny = gettoken(hahareference);
    while (funny != NULL) {
        printf("%s\n", funny);
        funny = gettoken(hahareference);
    }

    free(funny);
    return 0; 
}