#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "False.h"

int main(){
    Node** stack = create_stack();
    char* progstr = "8 2 3+\\$2U@%"; //"1[3+]\"Hello World\"a:6a;!";
    execute(stack,progstr);
    print_stack(stack);
    return 0; 
}



