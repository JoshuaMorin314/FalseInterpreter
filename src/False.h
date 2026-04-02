#ifndef FALSE_H
#define FALSE_H

/**** FALSE OPERATIONS ****/
//Stack
extern void drop(Node** stack);
extern void swap(Node** stack);
extern void rot(Node** stack);
extern void pick(Node** stack);
extern void dup(Node** stack);

//Variables
extern void fetch(Node** stack, char ch);
extern void store(Node** stack, char ch);

//Arithmatic
extern void plus(Node** stack);

//Functions
extern void execute(Node** stack,char* subprog);



#endif // FALSE_H