#ifndef TOKENIZER_H
#define TOKENIZER_H

//Helper functions
extern int isalphabetic(char c);
extern int len(char* str);

//Retrieve token stream from a program and consume them
extern Data gettoken(char** progstring); 

#endif //TOKENIZER_H