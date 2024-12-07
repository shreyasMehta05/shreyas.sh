#include"../display/systemDisplay.h"
#include<stdbool.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<pwd.h>
#include<stdlib.h>
#include"../interface/interface.h"
#include"../display/systemDisplay.h"
#ifndef LOG_H 
#define LOG_H 1
#define BUFFER_MAX_PATH_TO_LOG_FILES 100
#define MAX_LINES 15
char* pathDynamicFunction(Prompt* prompt);
bool readLastLine(FILE* file,char* command);
char* pathDynamicFunctionFortempLog(Prompt* prompt);
bool copyFromTempToUser(Prompt* prompt,FILE* File);
bool appendAtFirst(FILE* file, char* command, Prompt* prompt);
bool logCommandUser(char* command,Prompt* prompt);
char* logExecute(int num,Prompt* prompt);
bool logPurge(Prompt* prompt);
bool logDisplay(Prompt* prompt);
int numberOflines(FILE* file);
#endif