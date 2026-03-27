#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"

Data variables[26];

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
        reterror.tag = TYPE_STR;
        reterror.val.string = NULL;
        return reterror;         //Leave early if no program left
    }

    char* start = *progstring;                  //Begin the things
    char* stret = (char*)malloc(10000*sizeof(char));
    char* striter = stret;
    Data dataret;

    while (iswhitespace(*start)) start++;       //Skip past whitespacess

    if (isnumeric(*start)) {                    //Check for int literals
        dataret.tag = TYPE_INT;
        dataret.val.integer = 0;
        while (isnumeric(*start)) {
            dataret.val.integer += *start - '0';
            dataret.val.integer *= 10;
            start++;
        }
    } else if (*start == '\"') {                //Check for strings
        start++;
        while (*start != '\"') {
            *striter = *start;
            striter++;
            start++;
        }
        *striter = 0;
        start++;
        dataret.tag = TYPE_STR;
        dataret.val.string = stret;
    } else if (*start == '\'') {                //Check for character codes
        start++;
        dataret.tag = TYPE_INT;
        dataret.val.integer = *start;
    } else if (*start == '[') {                 //Check for lambdas
        start++;
        while (*start != ']') {
            *striter = *start;
            striter++;
            start++;
        }
        *striter = 0;
        start++;
        dataret.tag = TYPE_STR;
        dataret.val.string = stret;
    } else if (*start == '{') {                 //Ignore comments
        for(; *start != '}'; start++);
        start++;
    } else {                                    //Save everything else as a character
        *striter = *start;
        *(striter+1) = 0;

        dataret.tag = TYPE_STR;
        dataret.val.string = striter;

        start++;
    }

    *progstring = start;                        //Move start location
    return dataret;                             //Return the token
}

/**** FALSE FUNCTIONS *****/
void DROP(Node** stack) {
    pop(stack);
}

void SWAP(Node** stack) {
    Data v1, v2;
    v1 = pop(stack);
    v2 = pop(stack);
    push(stack, v1);
    push(stack, v2);
}

void ROT(Node** stack) {
    Data v1, v2, v3;
    v1 = pop(stack);
    v2 = pop(stack);
    v3 = pop(stack);
    push(stack, v2);
    push(stack, v1);
    push(stack, v3);
}

void PICK(Node** stack, int i) {
    Node* traverse = *stack;
    for(i; i != 0; i--) {
        traverse = traverse->next;
    }
    push(stack, traverse->value);
}

void DUP(Node** stack) {
    PICK(stack, 0);
}

void store(Node** stack) {
    Data ch = pop(stack);
    Data val = pop(stack);          //Get data from the stack
    if (ch.tag == TYPE_STR && len(ch.val.string) == 1 && isalphabetic(ch.val.string[0]))
        variables[*(ch.val.string) - 'a'] = val;    //Do the thing
    else {
        printf("Type Error: Variable must be an alphabetical character");
        exit(EXIT_FAILURE);
    }
}

void fetch(Node** stack) {
    Data ch = pop(stack);
    if (ch.tag == TYPE_STR && len(ch.val.string) == 1 && isalphabetic(ch.val.string[0]))
        push(stack, variables[*(ch.val.string) - 'a']);
    else {
        printf("Type Error: Variable must be an alphabetical character");
        exit(EXIT_FAILURE);
    } 
}