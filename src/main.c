#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "False.h"

// opens the file and sets it to a variable
char* fileText(char* filename){
    FILE* F=fopen(filename,"rb"); // open file for reading ("rb"=read binary - so we get an accurate bytecounts)
    if(F==NULL){ // if file didn't exist
        printf("ERROR: file %s not found\n",filename);
        exit(EXIT_FAILURE);
    }
    // Move the cursor to the very end of the file
    fseek(F,0,SEEK_END);
    // Get the current position of the cursor (Since we are at the end this is the total size in bytes)
    long fileSize=ftell(F);
    // allocate exactly enough memory to hold the entire contents of the text document
    char *buffer=malloc(fileSize+1); // +1 for the null terminator '\0'
    // set the cursor back to the begining of the file so it can start reading
    rewind(F);
    // fill the buffer with the contents of the file
    size_t bytesRead=fread(buffer,1,fileSize,F);
    // check for 
    if(bytesRead<fileSize){
        printf("\nERROR: could not finish reading file %s (%zu of %lu bytes read)\n",filename,bytesRead,fileSize);
        exit(EXIT_FAILURE);
    }
    // null-terminate the string
    buffer[bytesRead]='\0';
    // close the file (we have the text saved in buffer)
    fclose(F);
    return buffer;
}

int main(int argc,char** argv){
    
    char* filename=argv[argc-1]; //"program.txt"; // put the code in here
    char* prgm=fileText(filename);
    Node** stack=create_stack();
    execute(stack,prgm);
    printf("\n"); // to separate program output from stack state
    //print_stack(stack);
    return 0; 
}