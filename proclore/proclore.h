#include"../display/systemDisplay.h"
#include<stdbool.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<pwd.h>
#include"../interface/interface.h"
#include"../display/systemDisplay.h"
#include<grp.h>
#include<time.h>
#include<sys/stat.h>
#include<dirent.h>
#include"../display/systemDisplay.h"
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

#ifndef PROCLORE_H
#define PROCLORE_H 1

bool proclore(pid_t ID,Prompt* prompt);
char* proclorePathConstructor(pid_t ID);
char* statusPathConstructor(pid_t ID);
void printProclore1(char* bufferForProclore,pid_t ID);
void printExecutablePath(char* proclorePath,Prompt* prompt);
bool readProclore(char* path,pid_t ID,char* proclorePath,Prompt* prompt);

#endif