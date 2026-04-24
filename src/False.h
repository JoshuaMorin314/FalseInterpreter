#ifndef FALSE_H
#define FALSE_H

/**** FALSE OPERATIONS ****/
//Stack
extern void drop(Node** stack);              // '%'  pops the top stack element off the stack (destroys)
extern void dup(Node** stack);               // '$'  pushes a copy of the top stack element onto the top of the stack (duplicates)
extern void swap(Node** stack);              // '\\' swaps the order of the top two stack elements (rearanges)
extern void rot(Node** stack);               // '@'  removes the third element from top element from the stack and pushes it back on the top of the stack (rearranges)
extern void pick(Node** stack);              // 'U'  makes a copy of the element as many elements deep on the stack as the value on the top stack element and pushes it on the top of the stack (preserves the copied value destroys the top value)

//Arithmatic
extern void add(Node** stack);               // '+'  adds the top two elements on the stack (destructive)
extern void subtract(Node** stack);          // '-'  subtracts the top stack element from the second to top element on the stack (destructive)
extern void multiply(Node** stack);          // '*'  multiplies the top two elements on the stack (destructive)
extern void divide(Node** stack);            // '/'  divides the second to top stack element by the top element on the stack (destructive)

//Logical
extern void negate(Node**);                  // '_'  flip the sign of top element on the stack (destructive)
extern void and(Node**);                     // '&'  bitwise and on the top two elements on the stack (destructive)
extern void or(Node**);                      // '|'  bitwise or on the top two elements on the stack (destructive)
extern void not(Node**);                     // '~'  bitwise not on the top two elements on the stack (destructive)
extern void greater(Node**);                 // '>'  pushes -1 on top the stack if the second from top stack element is greater than the top stack element otherwise pushes 0 (destructive)
extern void equal(Node**);                   // '='  pushes -1 on top the stack if the second from top stack element is equal to the top stack element otherwise pushes 0 (destructive)

//Variables
extern void store(Node** stack);             // ':'  stores the value of the variable specified by the top element on the stack
extern void fetch(Node** stack);             // ';'  stores the value of the second element from the top of the stack to the variable on the top of the stack

//Control flow
extern void execute(Node** stack,char* str); // '!'  executes the code contained in the parameter str (destructive)
extern void conditional(Node** stack);       // '?'  if the second from top stack element is non-zero execute the top stack element (destructive)
extern void loop(Node** stack);              // '#'  while the second from top stack element is non-zero execute the top stack element repeatedly (destructive)

// I/O controls
extern void read(Node** stack);              // '^' reads a character from user input (i.e. stdin) and pushes it onto the top of th stack 
extern void emit(Node** stack);              // ',' writes the top of the stack to the console as a character (destructive)
extern void write(Node** stack);             // '.' writes the top of the stack to the console as a decimal integer (destructive)

// Debug commands
extern void debugprint(Node** stack);        // 'S' simply prints out the current working stack.

#endif // FALSE_H