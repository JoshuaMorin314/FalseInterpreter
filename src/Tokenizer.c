#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"

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

    // print dataret
    switch(dataret.tag){
        case TYPE_INT:\
          printf("INT: %d\n",dataret.val.integer); 
          break;
        case TYPE_STR:
          printf("STR: %s\n",dataret.val.string); 
          break;
        case TYPE_FUN:
          printf("FUN: %s\n",dataret.val.string); 
          break;
    }

    *progstring = start;                        //Move start location
    return dataret;                             //Return the token
}

