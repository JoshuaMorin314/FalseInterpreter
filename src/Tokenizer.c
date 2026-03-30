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
        dataret.tag = TYPE_STR;
        dataret.val.string = stret;
    } else if (*start == '\'') {                //Check for character codes
        start++;
        dataret.tag = TYPE_INT;
        dataret.val.integer = *start;
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
        dataret.tag = TYPE_FUN;
        dataret.val.string = stret;
    } else if (isalphabetic(*start)) {
        dataret.tag = TYPE_STR;
        *striter = *start; start++; striter++;
        if (*start == ':' || *start == ';') {
            *striter = *start; start++; striter++;
        } else {
            printf("Syntax Error: Variables must be followed by a fetch/store command.");
            exit(EXIT_FAILURE);
        }    
        *striter = 0;
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
//Stack
void DROP(Node** stack) {
    pop(stack);
}

void SWAP(Node** stack) {
    Data v1 = pop(stack);
    Data v2 = pop(stack);
    push(stack, v1);
    push(stack, v2);
}

void ROT(Node** stack) {
    Data v1 = pop(stack);
    Data v2 = pop(stack);
    Data v3 = pop(stack);
    push(stack, v2);
    push(stack, v1);
    push(stack, v3);
}

void PICK(Node** stack) {
    Data idx = pop(stack);
    if (idx.tag != TYPE_INT) {
        printf("Type Error: Pick index must be int");
        exit(EXIT_FAILURE);
    }
    
    Node* traverse = *stack;
    for(int i = idx.val.integer; i != 0; i--) {
        traverse = traverse->next;
    }
    push(stack, traverse->value);
}

void DUP(Node** stack) {
    push(stack, peek(stack));
}


//Variables
void store(Node** stack, char ch) {
    Data val = pop(stack);        //Get data from the stack
    variables[ch - 'a'] = val;    //Do the thing
}

void fetch(Node** stack, char ch) {
    push(stack, variables[ch - 'a']);
}


//Control Flow
char* getlambda(Node** stack) {
    Data lmb = pop(stack);
    if (lmb.tag == TYPE_FUN) {
        return lmb.val.string;
    } else {
        return "ERROR";
    }
}


//Arithmatic
void plus(Node** stack) {
    Data a = pop(stack);
    Data b = pop(stack);
    Data* ret = (Data*)malloc(sizeof(Data*));
    if (a.tag == TYPE_INT && b.tag == TYPE_INT) {
        ret->val.integer = a.val.integer + b.val.integer;
        ret->tag = TYPE_INT;
        push(stack, *ret);
    }
}