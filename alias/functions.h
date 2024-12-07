#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../command/command.h"
#ifndef FUNCTIONS_H
#define FUNCTIONS_H 1

#define MAX_FUNCTION_NAME 256
#define MAX_FUNCTION_BODY 1024

// Structure to store a function
typedef struct Function {
    char functionName[MAX_FUNCTION_NAME];
    char functionBody[MAX_FUNCTION_BODY];
    struct Function *next;
} Function;

// global variable to store the function list
extern Function *functionList;
// Loads the function definitions from the .myshrc file
void loadFunctions();
// Executes the command if it matches a function defined in the .myshrc file
int executeAliasFunction(const char *command,Prompt* prompt);
#endif