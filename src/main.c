#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "False.h"

int main(){
    Node** stack = create_stack();
    char* progstr = "10 5+10 5-10 5*10 5/5_54a:1U_1U_$@\\%a;@\"Hello\"b:@1 2=2 1>1_~0 1_&1_0|[1+]f:5f;!f;!0~[9_]?0[9]?b;a;,b;,a;."; // expects 6Hello54{Top -> "Hello",-9,7,-1,0,0,-1,0,-2,5,54,-5,2,50,5,15}
    // other test inputs: //"8 2 3+\\$2U@%"; //"1[3+]\"Hello World\"a:6a;!";
    execute(stack,progstr);
    print_stack(stack);
    return 0; 
}

/*
TO DO:
1. while functionality < see False.c line 216 and False.h line 33
  >>Haven't tried yet; might not be that bad; not super sure I know how exactly it is supposed to work 
2. read functionality  < see False.c line 219 and False.h line 36
    have to figure out how to differentiate input and code in stdin
    have to figure out a plan for the front end in general
  >>Probably need to meet  to discuss this
3. Strings (i.e. the " command) is implemented incorrectly; decide wwhether to make this a feature or relimit it to what is allowed by the original language
  >>Probably need to meet to discuss this
4. comments for False.h lines 33-38
5. make the interpreter look to stdin or a file for input instead of hard coding it into the source code 
  >>I can do this
6. maybe move where stack is assigned for the sake of organization?
  >>Not really 100% necessary
7. figure out what takes it so long to run lol
  >>If theres time
*/