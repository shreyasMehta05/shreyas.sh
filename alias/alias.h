#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"../display/display.h"
#include"../display/color.h"
#include"../interface/interface.h"
#include<stdbool.h>
#include<ctype.h>

#ifndef ALIAS_H
#define ALIAS_H 1

// Structure to store an alias
typedef struct Alias{
    char* aliasName;
    char* command;
    struct Alias* next;
    int length;
    
} Alias;
// global variable to store the alias list
extern Alias* aliasList;

void addAlias(char* aliasName,char* command);
void removeAlias(char* aliasName);
void listAliases();
void executeAlias(char* aliasName,Prompt* prompt);
bool isAlias(char* aliasName);
char* getCommand(char* aliasName);
void freeAliasList();
void createAliasList();
char *replaceAliasesInString(char *input);
void removeLeadingWhitespace(char *str);


#endif
