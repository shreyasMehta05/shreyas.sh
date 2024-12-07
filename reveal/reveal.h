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
#ifndef REVEAL_H
#define REVEAL_H 1
typedef struct filesList{
    char** list;
    int n;
}filesList;

void permission(mode_t mode);
void reveal(char* token,Prompt* prompt,bool flagA,bool flagL,bool prev,char* path);
void revealRetList(char* path,Prompt* prompt,bool flagA,bool flagL);
void colorACCtoFiles(struct dirent* entry,char* path,char* name);
void printDetails(char* name,char* path);
void printDetailsFile(char* path);
bool isFile(char* path, bool flagL, bool flagA);
int compare(const void* a, const void* b);
filesList* getFiles(char* path);
filesList* sort(filesList* list);

#endif