#ifndef TOKENIZER_H
#define TOKENIZER_H

//Retrieve token stream from a program and consume them
extern Data gettoken(char** progstring);

// determines which False.c function to use based on the value of a OP type token (via the lex parameter)
extern void processlexeme(Node** stack, char lex);

#endif //TOKENIZER_H