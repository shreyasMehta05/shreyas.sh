#include"seek.h"

char* generateAbsolutePath(char* dirname,Prompt* prompt){
    char* absolutePath = (char*)malloc(1000);
    if(absolutePath==NULL){
        // printfColor("Memory Allocation Error\n",RED,false);
        fprintf(stderr,RED"Memory Allocation Error\n"RESET);
        return NULL;
    }
    if(dirname==NULL){
        dirname = prompt->directory->directoryName;
    }
    if(dirname[0]=='/'){
        strcpy(absolutePath,dirname);
    }
    else if(dirname[0]=='~'||dirname[0]=='-'){
        strcpy(absolutePath,prompt->directory->homeDirectory);
        strcat(absolutePath,"/");
        if(strlen(dirname)==1){
            return absolutePath;
        }
        strcat(absolutePath,dirname+2);
    }
    else{
        strcpy(absolutePath,prompt->directory->directoryName);
        strcat(absolutePath,"/");
        strcat(absolutePath,dirname);
    }
    return absolutePath;
}
bool ifTrivialDirectory(char* name){
    if(strcmp(name,".")==0 || strcmp(name,"..")==0){
        return true;
    }
    
    return false;

}
void searchDir(char* baseDirectory,const char* searchName ,const char* targetDirectory,bool flagF,bool flagD,bool FlagE,int* dirCnt,char* foundDirectory,int* fileCnt,char* foundFiles){
    DIR* directory = opendir(baseDirectory);
    if(directory==NULL){
        // printfColor(RED,"Error opening directory\n",false);
        fprintf(stderr,RED"Error opening directory\n"RESET);
        return;
    }

    struct dirent* entry; struct stat pathStat;
    char path[1000];
    
    while((entry = readdir(directory))){
        if(ifTrivialDirectory(entry->d_name)){
            continue;
        }
        if(baseDirectory[strlen(baseDirectory)-1]=='/'){
            baseDirectory[strlen(baseDirectory)-1] = '\0';
        }
        snprintf(path,sizeof(path),"%s/%s",baseDirectory,entry->d_name);
        stat(path,&pathStat);
        const char* relativePath = path + strlen(targetDirectory) + 1;

        if(S_ISDIR(pathStat.st_mode)){

            if(strstr(entry->d_name,searchName) && (flagD)){
                (*dirCnt)++;
                strncpy(foundDirectory,path,sizeof(path));
                foundDirectory[strlen(foundDirectory)] = '\0';
                printfColor(BLUE,relativePath,false);
                printf("\n");
            }
            searchDir(path,searchName,targetDirectory,flagF,flagD,FlagE,dirCnt,foundDirectory,fileCnt,foundFiles);
        }
        else if(S_ISREG(pathStat.st_mode)){
            if(strstr(entry->d_name,searchName) && (flagF)){
                (*fileCnt)++;
                strncpy(foundFiles,path,sizeof(path));
                foundFiles[strlen(foundFiles)] = '\0';
                printfColor(GREEN,relativePath,false);
                printf("\n");
            }
        }
    }
    closedir(directory);
}

void seek(char* searchPath,char* dirName,bool flagF,bool flagD,bool flagE,Prompt* prompt){
    if(!flagD && !flagF){
        // printfColor(RED,"Invalid Flags\n",false);
        fprintf(stderr,RED"Invalid Flags\n"RESET);
        return;
    }
    
    int dirCnt = 0; int fileCnt = 0;
    char foundDirectory[1000]={0}; char foundFiles[1000]={0};
    char* absolutePath = generateAbsolutePath(dirName,prompt);
    printf("absolutePath: %s\n",absolutePath);
    searchDir(absolutePath,searchPath,absolutePath,flagF,flagD,flagE,&dirCnt,foundDirectory,&fileCnt,foundFiles);
    if(flagD && flagF){
        if(dirCnt==0 && fileCnt==0){
            // printfColor(RED,"No File or Directory Found\n",false);
            fprintf(stderr,RED"No File or Directory Found\n"RESET);
            return;
        }
    }
    else if(flagD){
        if(dirCnt==0){
            // printfColor(RED,"No Directory Found!\n",false);
            fprintf(stderr,RED"No Directory Found!\n"RESET);
            return;
        }
    }
    else if(flagF){
        if(fileCnt==0){
            // printfColor(RED,"No File Found!\n",false);
            fprintf(stderr,RED"No File Found!\n"RESET);
            return;
        }
    }
    if(flagE){
        if(dirCnt==1 && fileCnt==0){
            // change the directory
            hop(foundDirectory,prompt);
        }
        else if(fileCnt==1 && dirCnt==0){
            printf("%s\n",foundFiles);
            FILE* file = fopen(foundFiles,"r");
            if(file==NULL){
                // printfColor("Error opening file\n",RED,false);
                fprintf(stderr,RED"Error opening file\n"RESET);
                return;
            }
            // print the content of the file
            char buffer[1000];
            while(fgets(buffer,1000,file)!=NULL){
                printf("%s",buffer);
            }
            printf("\n");
            fclose(file);
        }
    }
    free(absolutePath);
}