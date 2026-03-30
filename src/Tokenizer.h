#ifndef TOKENIZER_H
#define TOKENIZER_H

//Helper functions
extern int isalphabetic(char c);
extern int len(char* str);

//Retrieve token stream from a program and consume them
extern Data gettoken(char** progstring); 

/**** FALSE OPERATIONS ****/
//Stack
extern void DROP(Node** stack);
extern void SWAP(Node** stack);
extern void ROT(Node** stack);
extern void PICK(Node** stack);
extern void DUP(Node** stack);

//Variables
extern void fetch(Node** stack, char ch);
extern void store(Node** stack, char ch);

//Arithmatic
extern void plus(Node** stack);

//Functions
extern char* getlambda(Node** stack);

#endif //TOKENIZER_H