#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<sys/types.h>
#include<pwd.h>
#include<sys/wait.h>
#include"../hop/hop.h"
#include"../reveal/reveal.h"
#include<ctype.h>
#include"../interface/interface.h"
#include"../log/log.h"
#include"../proclore/proclore.h"
#include"../seek/seek.h"
#include<sys/time.h>
#include"fcntl.h"
#ifndef REDIRECTION_H
#define REDIRECTION_H 1

// Function to check and return input redirection file
char* getInputRedirectionFile(char *command, Prompt* prompt);
// Function to check and return output redirection file, supports both > and >>
char* getOutputRedirectionFile(char *command, int *appendMode, Prompt* prompt);
// Function to handle input redirection
void handleInputRedirection(char *inputFile, int *originalStdin);
// Function to handle output redirection with support for append or overwrite
void handleOutputRedirection(char *outputFile, int appendMode, int *originalStdout);
// Function to restore original stdin and stdout
void restoreRedirection(int originalStdin, int originalStdout);
// Main function to handle redirection
bool handleRedirection(char* command, Prompt* prompt,int *originalStdin, int *originalStdout);
void removeRedirectionSymbols(char* command);
char* getArgs(char*command,char* args[],bool includeCommand);
void handlePipes(char* command, Prompt* prompt);
#endif