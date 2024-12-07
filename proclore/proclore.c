#include"proclore.h"



pid_t getTerminalPGID(const char* ttyPath){ //terminal device file path
    int fd = open(ttyPath,O_RDWR);
    if(fd == -1){
        perror("open");
        return -1;
    }
    pid_t pgid = tcgetpgrp(fd);
    close(fd);
    return pgid;
}
pid_t getProcessId(pid_t pid){
    pid_t pgid = getpgid(pid);
    if(pgid == -1){
        perror("getpgid");
        return -1;
    }
    return pgid;
}
int isForegroundProcess(pid_t pid,const char* ttyPath){
    pid_t terminalPGID = getTerminalPGID(ttyPath);
    if(terminalPGID == -1){
        return -1;
    }
    pid_t processPGID = getProcessId(pid);
    if(processPGID == -1){
        return -1;
    }
    return processPGID == terminalPGID;
}


char* proclorePathConstructor(pid_t ID){
    char* proclorePath = (char*)malloc(100);
    if(proclorePath == NULL){
        // printfColor("Memory Allocation Error\n",RED,false);
        fprintf(stderr,RED"Memory Allocation Error\n"RESET);
        return NULL;
    }
    snprintf(proclorePath,100,"/proc/%d",ID);
    return proclorePath;
}
char* statusPathConstructor(pid_t ID){
    char* statusPath = (char*)malloc(100);
    if(statusPath == NULL){
        // printfColor("Memory Allocation Error\n",RED,false);
        fprintf(stderr,RED"Memory Allocation Error\n"RESET);
        return NULL;
    }
    if(snprintf(statusPath,100,"/proc/%d/stat",ID) >= 100){
        // printfColor("Long Path\n",RED,false);
        fprintf(stderr,RED"Long Path\n"RESET);
        return NULL;
    }
    return statusPath;
}
void printProclore1(char* bufferForProclore,pid_t ID){
    int processID, pgrp, session, tty_nr, tpgid;
    char comm[256], state;
    unsigned long vsize;
    sscanf(bufferForProclore,"%d %s %c %*d %d %d %d %d %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %lu",&processID,comm,&state,&pgrp,&session,&tty_nr,&tpgid,&vsize);

    
    printf("pid : %d\n",processID);
    char path[100];
    sprintf(path, "/proc/%d/status", processID);
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    char statusStr[100];
    while(fgets(statusStr,sizeof(statusStr),fp) != NULL){
        if(strncmp(statusStr,"State:",6) == 0){
            break;
        }
    }
    if(isForegroundProcess(ID,"/dev/tty") == 1){
        printf("State : %c+\n",statusStr[7]);
    }
    else{
        printf("State : %c\n",statusStr[7]);
    }
    fclose(fp);
    
    printf("Process Group : %d\n",pgrp);
    printf("Virtual memory : %lu\n",vsize);
}


char* relativePathGenerator(char* homeDirectory,char* path){
    char* relativePath = (char*)malloc(100);
    if(relativePath == NULL){
        // printfColor("Memory Allocation Error\n",RED,false);
        fprintf(stderr,RED"Memory Allocation Error\n"RESET);
        return NULL;
    }
    int homeDirectoryLength = strlen(homeDirectory); int directoryLength = strlen(path);
    if(homeDirectoryLength > directoryLength){
        strcpy(relativePath,path);
        return relativePath;
    }
    if(strncmp(homeDirectory,path,homeDirectoryLength) != 0){
        strcpy(relativePath,path);
        return relativePath;
    }
    snprintf(relativePath,100,"~%s",path+homeDirectoryLength);
    return relativePath;
}
void printExecutablePath(char* proclorePath,Prompt* prompt){
    char exePath[40];
    if(snprintf(exePath, sizeof(exePath), "%s/exe", proclorePath) >= sizeof(exePath)){
        printfColor("Long Path\n", RED, false);
        return;
    }

    char bufferForProclore[1024];
    ssize_t len = readlink(exePath, bufferForProclore, sizeof(bufferForProclore) - 1);
    if (len != -1) {
        bufferForProclore[len] = '\0';
        // printf("executable path : %s\n", bufferForProclore);
        printf("executable path : %s\n", relativePathGenerator(prompt->directory->homeDirectory, bufferForProclore));
        
    } else {
        // perror("readlink");
        fprintf(stderr,RED"readlink\n"RESET);
        printf("executable path : unknown\n");
    }
}

bool readProclore(char* path,pid_t ID,char* proclorePath,Prompt* prompt){
    FILE *file = fopen(path,"r");
    if(file == NULL){
        printfColor("fopen error\n",RED,false);
        return false;
    }
    char buffer[1000];
    if(fgets(buffer,sizeof(buffer),file) != NULL){
        printProclore1(buffer,ID);
        printExecutablePath(proclorePath,prompt);
    }
    else{
        fprintf(stderr,RED"Failed to read file\n"RESET);
        // printfColor("Failed to read file\n",RED,false);
        return false;
    }
    fclose(file);
    return true;
}
bool proclore(pid_t ID,Prompt* prompt){
    char* proclorePath = proclorePathConstructor(ID);
    if(proclorePath == NULL){
        return false;
    }
    char* statPath = statusPathConstructor(ID);
    if(statPath == NULL){
        free(proclorePath);
        return false;
    }
    FILE *statFile = fopen(statPath,"r");
    if(statFile == NULL){
        // printfColor("fopen error\n",RED,false);
        fprintf(stderr,RED"fopen error\n"RESET);
        return false;
    }
    if(readProclore(statPath,ID,proclorePath,prompt) == false){
        free(proclorePath);
        free(statPath);
        fclose(statFile);
        return false;
    }
    fclose(statFile);
    free(proclorePath);
    free(statPath);
    return true;
}