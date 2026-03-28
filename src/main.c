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

void processvariable(Node** stack, char var, char fun);
void processlexeme(Node** stack, char lex);

int main(){
    Node** stack = create_stack();
    char* progstr = "123 44 a: 44 3 ;";
    char** progref = &progstr;

    Data token;
    token = gettoken(progref);
    while (token.tag == TYPE_STR && token.val.string != NULL || 
            token.tag == TYPE_INT || token.tag == TYPE_FUN) {
        switch(token.tag) {
            case TYPE_STR:
                if (len(token.val.string) > 2) {
                    printf("%s", token.val.string);
                } else if (len(token.val.string) == 2) {
                    processvariable(stack, token.val.string[0], token.val.string[1]);
                } else if (isalphabetic(*token.val.string)) {
                    push(stack, token);
                } else {
                    processlexeme(stack, *token.val.string);
                }
                break;
            case TYPE_FUN:
            case TYPE_INT:
                push(stack, token);
                break;
        }

        token = gettoken(progref);
    }

    print_stack(stack);

    return 0; 
}

void processvariable(Node** stack, char var, char fun) {
    switch (fun) {
        /* variable functions */
        case ':':           //Store top into a variable
            store(stack, var);
            break;
        case ';':           //Fetch from a variable
            fetch(stack, var);
            break;
    }
}

void processlexeme(Node** stack, char lex) {
    switch(lex) {
        /* stack functions */
        case '$':           //Duplicate top of stack (equivelant to pick(0))
            DUP(stack);
            break;
        case '%':           //Pop top item from stack
            DROP(stack);
            break;
        case '\\':          //Swap top and top->next
            SWAP(stack);
            break;
        case '@':           //Bring third item to top
            ROT(stack);
            break;
        case 'U':           //C doesn't like greek letters so I'm improvising
            PICK(stack);    //Pick the nth item from the stack (starting from 0)
            break;

        case ';':
        case ':':
            printf("Error: Fetch/store called with no associated variable");
            exit(EXIT_FAILURE);
    }
}