#include <stdlib.h>
#include <stdio.h>

void copyupto(char* dest, const char* src, int index) {
    for(int i = 0; i < index && src[i] && dest[i]; i++) {
        dest[i] = src[i];
    }
}

int isnumeric(char c) {
    return (c - '0' <= 9 && c - '0' >= 0);
}

int len(char* str) {
    int count;
    for(count = 0; str[count]; count++);
    return count;
}

void pause() {
    char _;
    scanf("%c", _);
}

/* GET TOKEN */
/*
Grab the first token from input stream, using whitespaces as delimiters
We then wipe the token from the input stream, starting the string at a new character.
*/

char* gettoken(char** progstring) {
    if (!len(*progstring)) return NULL;
    char* start = *progstring;
    char* retpreserve = (char*)malloc(10000*sizeof(char));
    char* ret = retpreserve;
    if (isnumeric(*start)) {
        while (isnumeric(*start)) {
            *ret = *start;
            ret++;
            start++;
        }
    } else if (*start == '\"') {
        start++;
        while (*start != '\"') {
            *ret = *start;
            ret++;
            start++;
        }
        start++;
    } else if (*start == '\'') {
        start++;
        itoa(*start, ret, 10);
    } else if (*start == '[') {
        start++;
        while (*start != ']') {
            *ret = *start;
            ret++;
            start++;
        }
        start++;
    } else {
        *ret = *start;
        start++;
        ret++;
    }
    *ret = 0;
    *progstring = start;
    return retpreserve;
}