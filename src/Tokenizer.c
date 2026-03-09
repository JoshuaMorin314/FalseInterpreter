#include <stdlib.h>
#include <string.h>

int getfirstwhitespace(char* str) {
    int i;
    for(i = 0; str[i] != ' ' && str[i] != '\n' && str[i] != '\t' && str[i] != '\0'; i++);
    return i+1;
}

void copyupto(char* dest, const char* src, int index) {
    for(int i = 0; i < index && src[i] && dest[i]; i++) {
        dest[i] = src[i];
    }
}

/* GET TOKEN */
/*
Grab the first token from input stream, using whitespaces as delimiters
We then wipe the token from the input stream, starting the string at a new character.
*/

char* gettoken(char** progstring) {
    int size = strlen(*progstring);
    if (!size) return NULL;
    int tokensize = getfirstwhitespace(*progstring);
    char* token = (char*)malloc(tokensize*sizeof(char));
    copyupto(token, *progstring, tokensize);
    *progstring += (tokensize);
    return token;
}