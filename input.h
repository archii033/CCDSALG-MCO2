#ifndef INPUT_H	
#define INPUT_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX 515

void clearInput();
int getInput(char *str);
int getTokens(char *str, char **tokenArray);

#endif 