#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "False.h"

int main(){
    Node** stack = create_stack();
    char* progstr = "10 5+10 5-10 5*10 5/5_42a:1U_1U_$@\\%a;@\"Hello\"b:@1 2=2 1>1_~0 1_&1_0|[1+]f:5f;!f;!0~[9_]?0[9]?b;"; // expects {Top -> "Hello",-9,7,-1,0,0,-1,0,-2,5,42,-5,2,50,5,15}
    // other test inputs: //"8 2 3+\\$2U@%"; //"1[3+]\"Hello World\"a:6a;!";
    execute(stack,progstr);
    print_stack(stack);
    return 0; 
}