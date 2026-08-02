#include "input.h"

int getTokens(char *str, char **tokenArray){
    char* token = strtok(str, " ");
    int count = 0;
    
    for (int i = 0; token != NULL; i++) {
    	tokenArray[i] = token;
        token = strtok(NULL, " ");
        count++;
    }
	
    return count;
}

// Consume input until it reaches a newline or end of file
// use only when looping for flushing prev input

void clearInput(){
    char c = '0';
	while ( (c = getchar()) != '\n' && c != EOF );
}

// Get string as user input
int getInput(char *str){

    char c = '0';
    int i = 0;

    // get char input. skip newlines and blank spaces
    do{
        c = getchar();
        if (c != '\n'){    
            str[i++] = c;
        }

    }while( c != '\n' && i < MAX);

    // add string terminator
    str[i] = '\0';
    return i;
}