#include"interface.h"


Prompt* InitialisePrompt(){
    // initialise the prompt
    Prompt* prompt=NULL;
    prompt = (Prompt*)malloc(sizeof(Prompt));
    if(prompt==NULL){
        // perror("Error Occoured in file: interface/interface.c --> InitialisePrompt()\n");
        fprintf(stderr,RED"Error Occoured in file: interface/interface.c --> InitialisePrompt()\n"RESET);
        exit(EXIT_FAILURE);
    }
    prompt->directory = (Directory*)malloc(sizeof(Directory));
    if(prompt->directory==NULL){
        // perror("Error Occoured in file: interface/interface.c --> InitialisePrompt()\n");
        fprintf(stderr,RED"Error Occoured in file: interface/interface.c --> InitialisePrompt()\n"RESET);
        exit(EXIT_FAILURE);
    }
    prompt->prompt = (char*)malloc(sizeof(char)*BUFFER_TERMINAL_DISPLAY_PROMPT);
    if(prompt->prompt==NULL){
        // perror("Error Occoured in file: interface/interface.c --> InitialisePrompt()\n");
        fprintf(stderr,RED"Error Occoured in file: interface/interface.c --> InitialisePrompt()\n"RESET);
        exit(EXIT_FAILURE);
    }
    prompt->directory->directoryName = getDirectoryName();
    prompt->directory->homeDirectory = getDirectoryName();
    prompt->directory->lastWorkingDirectory = NULL;
    generateTheDirectoryPath(prompt->directory->homeDirectory,prompt->directory->directoryName);
    prompt->prompt = returnUserAndSysStr(YELLOW);
    prompt->command2sec = NULL;
    prompt->processList = malloc(sizeof(ProcessList));
    initProcessList(&(prompt->processList));
    return prompt;
}

void printPrompt(Prompt* prompt){
    // print the prompt
    printf("%s",prompt->prompt);
    printfColor(BLUE,prompt->directory->directoryName,true);
    printfColor(GREEN,prompt->command2sec,false);
    printf("> ");
}

void updatePrompt(Prompt* prompt){
    // free the previous directory name
    if(prompt->directory->lastWorkingDirectory!=NULL)
        free(prompt->directory->lastWorkingDirectory);
    prompt->directory->lastWorkingDirectory = malloc(sizeof(char)*BUFFER_TERMINAL_DISPLAY_DIR);
    // printf("prompt->directory->directoryName :: %s\n",prompt->directory->directoryName);
    // printf("prompt->directory->homeDirectory :: %s\n",prompt->directory->homeDirectory);
    // printf("prompt->directory->lastWorkingDirectory :: %s\n",prompt->directory->lastWorkingDirectory);
    strcpy(prompt->directory->lastWorkingDirectory,prompt->directory->directoryName);
    // printf("prompt->directory->directoryName :: %s\n",prompt->directory->directoryName);
    // printf("prompt->directory->homeDirectory :: %s\n",prompt->directory->homeDirectory);
    // printf("prompt->directory->lastWorkingDirectory :: %s\n",prompt->directory->lastWorkingDirectory);
    if(prompt->directory->directoryName!=NULL)
        free(prompt->directory->directoryName);
    prompt->directory->directoryName = getDirectoryName();
    generateTheDirectoryPath(prompt->directory->homeDirectory,prompt->directory->directoryName);
    if(prompt->prompt!=NULL)
        free(prompt->prompt);
    prompt->prompt = returnUserAndSysStr(YELLOW);
    return;
}