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
#include"../hop/hop.h"

#ifndef SEEK_H
#define SEEK_H 1
void seek(char* searchPath,char* dirName,bool flagF,bool flagD,bool flagE,Prompt* prompt);
#endif