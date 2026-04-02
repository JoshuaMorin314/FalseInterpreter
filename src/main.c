#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "Tokenizer.h"
#include "False.h"

void processvariable(Node** stack, char var, char fun);
void processlexeme(Node** stack, char lex);
void lambda(char* subprog, Node** stack);

int main(){
    Node** stack = create_stack();
    char* progstr = "1[3+]a:6a;!";
    char** progref = &progstr;

    Data token = gettoken(progref);
    while (token.tag == TYPE_STR && token.val.string != NULL || 
            token.tag == TYPE_INT || token.tag == TYPE_FUN) {
        switch(token.tag) {
            case TYPE_STR:
                if (len(token.val.string) > 2) {
                    printf("%s", token.val.string);
                } else if (len(token.val.string) == 2) {
                    processvariable(stack, token.val.string[0], token.val.string[1]);
                } else {
                    processlexeme(stack, *token.val.string);
                }
                break;

            default:
                push(stack, token);
                break;
        }
        token = gettoken(progref);
    }
    //*/
    print_stack(stack);
    

    return 0; 
}

void processvariable(Node** stack, char var, char fun) { //
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
            dup(stack);
            break;
        case '%':           //Pop top item from stack
            drop(stack);
            break;
        case '\\':          //Swap top and top->next
            swap(stack);
            break;
        case '@':           //Bring third item to top
            rot(stack);
            break;
        case 'U':           //C doesn't like greek letters so I'm improvising
            pick(stack);    //Pick the nth item from the stack (starting from 0)
            break;

        /* Arithmatic */
        case '+':
            plus(stack);
            break;

        /* Control Flow */
        case '!':           //Execute Lambda
            char* func1 = getlambda(stack);
            if (func1 == "ERROR") {
                printf("Error: Function call made to non-function");
                exit(EXIT_FAILURE);
            } else {
                lambda(func1, stack);
            }
            break;
        
        /* Error handling for fetch/store. These should not get here without a variable name */
        case ';':
        case ':':
            printf("Error: Fetch/store called with no associated variable");
            exit(EXIT_FAILURE);
    }
}

void lambda(char* subprog, Node** stack) {
    char** lmbref = &subprog;
    Data token = gettoken(lmbref);
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
            default:
                push(stack, token);
                break;
        }
        token = gettoken(lmbref);
    }
}