#include <stdio.h>
#include "Stack.h"

int main(){
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

    return 0; 
}