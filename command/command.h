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
#include"../redirection/redirection.h"
#include"../process/process.h"
#include"../ping/ping.h"
#include"../neonate/neonate.h"
#include"../alias/alias.h"
#include"../iMan/iMan.h"

#ifndef COMMAND_H
#define COMMAND_H 1

#define BUFFER_TERMINAL_COMMAND 1000
#define BUFFER_TERMINAL_MAX_ARGS 100

// remove whitespaces
void removeLeadingWhitespaces(char* str);
// take input from the user
char* inputCommand(Prompt* prompt);
bool isSpace(char c);
// tokenise the command
void tokenise(char* command,Prompt* prompt);
// execute the commands
bool executeCommands(char* command,Prompt* prompt);
// execute the command single
void executeCommand(char* command,Prompt* prompt);
// execute the command in the foreground
void foregroundProcess(char* command,Prompt* prompt);
// execute the command in the background
void backgroundProcess(char* command,Prompt* prompt);

// void handleSignalChild(int Signal);
// pipe the commands
void executePipedCommands(char* command, Prompt* prompt);
// execute the pipe command
void executeSingleCommand(char* command, Prompt* prompt);

#endif