#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"
#include "False.h"

void copyupto(char* dest, const char* src, int index) {
    for(int i = 0; i < index && src[i] && dest[i]; i++) {
        dest[i] = src[i];
    }
}

int isalphabetic(char c) {
    return (c - 'a' <= 26 && c - 'a' >= 0);
}

int iswhitespace(char c) {
    return (
        c == ' '  ||
        c == '\n' ||
        c == '\t'
    );
}

int isnumeric(char c) {
    return (c - '0' <= 9 && c - '0' >= 0);
}

int len(char* str) {
    int count;
    for(count = 0; str[count]; count++);
    return count;
}

/* GET TOKEN */
/*
Grab the first token from input stream, using whitespaces as delimiters
We then wipe the token from the input stream, starting the string at a new character.
*/
Data gettoken(char** progstring) {
    if (!len(*progstring)) {
        Data reterror;
        reterror.tag = STR; // doesn't really make sense?
        reterror.val.string = NULL;
        return reterror;         //Leave early if no program left
    }

    char* start = *progstring;                  //Begin the things
    char* stret = (char*)malloc(10000*sizeof(char));
    char* striter = stret;
    Data dataret;

    while (iswhitespace(*start)) start++;       //Skip past whitespacess

    if (isnumeric(*start)) {                    //Check for int literals
        dataret.tag = INT;
        dataret.val.integer = 0;
        while (isnumeric(*start)) {
            dataret.val.integer += *start - '0';
            dataret.val.integer *= 10;
            start++;
        }
        dataret.val.integer /= 10;
    } else if (*start == '\"') {                //Check for strings
        start++;
        while (*start != '\"') {
            *striter = *start;
            striter++;
            start++;
        }
        *striter = 0;
        start++;
        dataret.tag = STR;
        dataret.val.string = stret;
    } else if (*start == '\'') {                //Check for character codes
        start++;
        dataret.tag = INT;
        dataret.val.integer = (int)(*start);
    } else if (*start == '[') {                 //Check for lambdas
        int brackets = 1;
        start++;
        if (*start == '[') brackets++;
        if (*start == ']') brackets--;
        while (brackets) {
            *striter = *start;
            striter++;
            start++;
            if (*start == '[') brackets++;
            if (*start == ']') brackets--;
        }
        *striter = 0;
        start++;
        dataret.tag = FUN;
        dataret.val.string = stret;
    } else if (isalphabetic(*start)) {
        dataret.tag = VAR;
        dataret.val.character=*start;
        start++;
    } else if (*start == '{') {                 //Ignore comments
        for(; *start != '}'; start++);
        start++;
    } else {                                    //Save everything else as a character
        dataret.tag = OP;
        dataret.val.character=*start;
        start++;
    }

    // print dataret
    switch(dataret.tag){
        case INT:
            printf("INT: %d\n",dataret.val.integer); 
            break;
        case STR:
            printf("STR: %s\n",dataret.val.string); 
            break;
        case FUN:
            printf("FUN: %s\n",dataret.val.string); 
            break;
        case VAR:
            printf("VAR: %c\n",dataret.val.character); 
            break;
        case OP:
            printf("OP:  %c\n",dataret.val.character); 
            break;
        default:
            printf("%d: ",dataret.tag);
            break;
    }

    *progstring = start;                        //Move start location
    return dataret;                             //Return the token
}

// determines which function to call based on an a command character (the lex parameter)
void processlexeme(Node** stack, char lex) {
    Data top;
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
        case '+':           //Add top and top->next
            plus(stack);
            break;
        case '-':           //Subtract top and top->next
            subtract(stack);
            break;
        case '*':           //Multiply top and top->next
            multiply(stack);
            break;
        case '/':           //Divide top and top->next
            divide(stack);
            break;
        
        /* Logic */
        case '_':           //negete top (i.e. invert its sign)
            negate(stack);
            break;
        case '&':           //Bitwize And top and top->next
            and(stack);
            break;
        case '|':           //Bitwize Or top and top->next
            or(stack);
            break;
        case '~':           //Bitwize Not top and top->next
            not(stack);
            break;
        case '>':           //Are top and top->next equal (-1 if true, 0 if false)
            greater(stack);
            break;
        case '=':           //Are top and top->next equal (-1 if true, 0 if false)
            equal(stack);
            break;
        
        /* Control Flow */
        case '!':           //Execute Lambda
            top=peek(stack);
            if(top.tag!=FUN){
                printf("ERROR: cannot execute unless the top of the stack specifies a function");
                exit(EXIT_FAILURE);
            }else{
                pop(stack);
                execute(stack,top.val.string);
            }
            break;
        case '?':           //Conditional statement
            conditional(stack);
            break;

        /* Variable storage and retrieval */
        case ':':           //Store top into a variable
            store(stack);
            break;
        case ';':           //Fetch from a variable
            fetch(stack);
            break;
    }
}