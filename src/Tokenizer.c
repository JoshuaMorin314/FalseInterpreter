#include <stdlib.h>
#include <stdio.h>

void copyupto(char* dest, const char* src, int index) {
    for(int i = 0; i < index && src[i] && dest[i]; i++) {
        dest[i] = src[i];
    }
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
char* gettoken(char** progstring) {
    if (!len(*progstring)) return NULL;         //Leave early if no program left

    char* start = *progstring;                  //Begin the things
    char* retpreserve = (char*)malloc(10000*sizeof(char));
    char* ret = retpreserve;

    while (iswhitespace(*start)) start++;       //Skip past whitespacess

    if (isnumeric(*start)) {                    //Check for int literals
        while (isnumeric(*start)) {
            *ret = *start;
            ret++;
            start++;
        }

    } else if (*start == '\"') {                //Check for strings
        start++;
        while (*start != '\"') {
            *ret = *start;
            ret++;
            start++;
        }
        start++;

    } else if (*start == '\'') {                //Check for character codes
        start++;
        itoa(*start, ret, 10);

    } else if (*start == '[') {                 //Check for lambdas
        start++;
        while (*start != ']') {
            *ret = *start;
            ret++;
            start++;
        }
        start++;

    } else {                                    //Save everything else as a character
        *ret = *start;
        start++;
        ret++;

    }

    *ret = 0;                                   //Denote end of retstring
    *progstring = start;                        //Move start location
    return retpreserve;                         //Return the token
}