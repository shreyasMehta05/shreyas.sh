#include"hop.h"
#include<sys/stat.h>
#include<string.h>
bool hop(char* path, Prompt* prompt){
    if(path==NULL){
        fprintf(stderr,RED"Invalid path: No path provided\n"RESET);
        return false;
    }
    if(strcmp(path,"~")==0){
        path = prompt->directory->homeDirectory;
    }
    else if(strcmp(path,"-")==0){
        if(prompt->directory->lastWorkingDirectory==NULL){
            // printfColor(RED,"No last working directory found!\n",true);
            fprintf(stderr,RED"No last working directory found!\n"RESET);
            return false;
        }
        path = prompt->directory->lastWorkingDirectory;
    }
    else if(path==NULL){
        path = prompt->directory->directoryName;
    }
    char* freeStore=NULL;
    if(path[0]=='~'){
        char* home = prompt->directory->homeDirectory;
        char* temp = (char*)malloc(strlen(home)+strlen(path)+10);
        strcpy(temp,home);
        strcat(temp,path+1);
        path = temp;
        freeStore = temp;
    }
    if(chdir(path)==0){
        if(freeStore!=NULL){
            free(freeStore);
        }
        // how to get the current directory name using getcwd
        updatePrompt(prompt);
        if(prompt->directory->directoryName[0]=='~'){
            printf("%s",prompt->directory->homeDirectory);
            printf("%s\n",prompt->directory->directoryName+1);
        }
        else{
            printf("%s\n",prompt->directory->directoryName);
        }
    }
    else{
        if(freeStore!=NULL){
            free(freeStore);
        }
        fprintf(stderr,RED"Invalid path: No such dir!"RESET);
    }
    return true;
}
