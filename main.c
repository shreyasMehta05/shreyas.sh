#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"interface/interface.h"
#include"display/systemDisplay.h"
#include<sys/types.h>
#include<pwd.h>
#include<signal.h>
#include<sys/wait.h>
#include"command/command.h"
#include"process/process.h"
#include"alias/alias.h"
#include"command/signals.h"
#include"command/globals.h"
#include"alias/functions.h"
extern Prompt* PROMPT;           // Definition
extern Function *functionList;

Prompt* globalPrompt;
void promptInit(Prompt* prompt){
    printPrompt(prompt);
}

int main(){
    loadFunctions();
    createAliasList();
    listAliases();
    Prompt* promptTerminal = InitialisePrompt();
    globalPrompt = promptTerminal;
    promptTerminal->command2sec="";
    PROMPT = promptTerminal;
    promptInit(promptTerminal);
    shellPid = getpid();
    setupSignal();

    // Handle SIGINT (Ctrl + C)

    while(1){
        char* command = inputCommand(promptTerminal);
        
        executeCommands(command,promptTerminal);
        promptInit(promptTerminal);
        promptTerminal->command2sec = "";
    }
    // freeFunctionList();
    freeAliasList();
    
    return 0;
}