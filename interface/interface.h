#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"../display/systemDisplay.h"
#include<sys/types.h>
#include<pwd.h>
#include"../process/process.h"

#ifndef INTERFACE_H
#define INTERFACE_H 1

typedef struct Directory{
    char* directoryName;
    char* homeDirectory;
    char* lastWorkingDirectory;
}Directory;

typedef struct Prompt{
    Directory* directory;
    char* command2sec;
    char* prompt;
    ProcessList* processList;
}Prompt;
// Prompt* promptTerminal;

void printPrompt(Prompt* prompt); // print the prompt
Prompt* InitialisePrompt(); // initialise the prompt
void updatePrompt(Prompt* prompt); // update the prompt

#endif