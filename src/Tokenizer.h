#ifndef TOKENIZER_H
#define TOKENIZER_H

//Helper functions (these don't need to be in the header file because no other file uses them) 
//extern void copyupto(char* dest, const char* src, int index);
//extern int isalphabetic(char c);
//extern int iswhitespace(char c);
//extern int isnumeric(char c);
//extern int len(char* str);

//Retrieve token stream from a program and consume them
extern Data gettoken(char** progstring);

// determines which False.c function to use based on the value of a OP type token (via the lex parameter)
extern void processlexeme(Node** stack, char lex);


#endif //TOKENIZER_H