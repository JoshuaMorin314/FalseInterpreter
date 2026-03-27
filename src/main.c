#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "Tokenizer.h"

/*
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
*/

int main(){
    char* programstring = "1 67 333 09123721 839826 a:a;";
    char** hahareference = &programstring;

    Data funny;
    funny = gettoken(hahareference);
    while (funny.tag == TYPE_STR && funny.val.string != NULL || funny.tag == TYPE_INT) {
        switch(funny.tag) {
            case TYPE_STR:
                printf("%s\n", funny.val.string);
                break;
            case TYPE_INT:
                printf("%d\n", funny.val.integer);
                break;
        }

        funny = gettoken(hahareference);
    }

    return 0; 
}