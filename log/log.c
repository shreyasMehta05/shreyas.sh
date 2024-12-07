#include"log.h"
char* pathDynamicFunction(Prompt* prompt){
    char* path = (char*)malloc(BUFFER_MAX_PATH_TO_LOG_FILES*sizeof(char));
    if(path==NULL){
        // perror("Error Occoured in file: log/log.c --> pathDynamicFunction()\n");
        fprintf(stderr,RED"Error Occoured in file: log/log.c --> pathDynamicFunction()\n"RESET);
        exit(EXIT_FAILURE);
    }
    strcpy(path,prompt->directory->homeDirectory);
    strcat(path,"/log/user.log");
    return path;
}
bool readLastLine(FILE* file,char* command) {
    if (file == NULL) {
        // printfColor(RED, "Error opening file\n", true);
        fprintf(stderr,RED"Error opening file\n"RESET);
        return NULL;
    }
    fseek(file, 0, SEEK_SET);
    int numberLine = numberOflines(file);
    if(numberLine==0){
        return false;
    }
    fseek(file, 0, SEEK_SET);
    char* lastCommand = (char*)malloc(100*sizeof(char));
    if (lastCommand == NULL) {
        // printfColor(RED, "Error allocating memory\n", true);
        fprintf(stderr,RED"Error allocating memory\n"RESET);
        return NULL;
    }
    while (fgets(lastCommand, 100, file) != NULL) {
        if (numberLine == 1) {
            break;
        }
        numberLine--;
    }
    lastCommand[strlen(lastCommand) - 1] = '\0';
    if(strcmp(lastCommand,command) == 0) {
        return true;
    }
    return false;
}
char* pathDynamicFunctionFortempLog(Prompt* prompt){
    char* path = (char*)malloc(BUFFER_MAX_PATH_TO_LOG_FILES*sizeof(char));
    if(path==NULL){
        fprintf(stderr,RED"Error Occoured in file: log/log.c --> pathDynamicFunctionForSysLog()\n"RESET);
        // perror("Error Occoured in file: log/log.c --> pathDynamicFunctionForSysLog()\n");
        exit(EXIT_FAILURE);
    }
    strcpy(path,prompt->directory->homeDirectory);
    strcat(path,"/log/temp.log");
    return path;
}
bool copyFromTempToUser(Prompt* prompt,FILE* file) {
    char* bufferArray[MAX_LINES];
    for(int i=0;i<MAX_LINES;i++){
        bufferArray[i] = (char*)malloc(1000*sizeof(char));
        if(bufferArray[i]==NULL){
            // printfColor(RED,"Error allocating memory\n",true);
            fprintf(stderr,RED"Error allocating memory\n"RESET);
            return false;
        }
    }
    for(int i=0;i<MAX_LINES;i++){
        if(fgets(bufferArray[i],1000,file)==NULL){
            break;
        }
    }
    fclose(file);
    char* path = pathDynamicFunction(prompt);
    file = fopen(path,"w+");
    if(file==NULL){
        // printfColor(RED,"Error opening user.log\n",true);
        fprintf(stderr,RED"Error opening user.log\n"RESET);
        return false;
    }
    for(int i=0;i<MAX_LINES;i++){
        fprintf(file,"%s",bufferArray[i]);
    }
    for(int i=0;i<MAX_LINES;i++){
        free(bufferArray[i]);
    }
    free(path);
    return true;
}
bool readLast15Lines(Prompt* prompt,FILE* file) {
    if (file == NULL) {
        // printfColor(RED, "Error opening file\n", true);
        fprintf(stderr,RED"Error opening file\n"RESET);
        return false;
    }
    fseek(file, 0, SEEK_SET);
    int numberLine = numberOflines(file);
    if(numberLine<=MAX_LINES){
        // printfColor(RED,"No need to purge\n",true);
        fseek(file, 0, SEEK_SET);
        return true;
    }
    fseek(file, 0, SEEK_SET);
    char* buffer = (char*)malloc(1000*sizeof(char));
    if(buffer==NULL){
        // printfColor(RED,"Error allocating memory\n",true);
        fprintf(stderr,RED"Error allocating memory\n"RESET);
        return false;
    }
    int count = 0;
    while(fgets(buffer,1000,file)!=NULL){
        if(++count==numberLine-MAX_LINES){
            break;
        }
    }
    copyFromTempToUser(prompt,file);
    free(buffer);
    return true;
}
bool appendAtFirst(FILE* file, char* command, Prompt* prompt) {
    if (file == NULL) {
        // printfColor(RED, "Error opening file\n", true);
        fprintf(stderr,RED"Error opening file\n"RESET);
        return false;
    }
    if(readLastLine(file,command)) {
        return true;
    }
    fseek(file, 0, SEEK_SET);
    fprintf(file, "%s\n", command);
    readLast15Lines(prompt,file);
    return true;
}
bool logCommandUser(char* command,Prompt* prompt){
    char* pathTouserLog = pathDynamicFunction(prompt);
    FILE* file = fopen(pathTouserLog,"a+");  
    free(pathTouserLog);   
    if(file==NULL){
        // printfColor(RED,"Error opening user.log\n",true);
        fprintf(stderr,RED"Error opening user.log\n"RESET);
        return false;
    }
    appendAtFirst(file,command,prompt);
    fclose(file);
    return true;
}
int numberOflines(FILE* file){
    if(file==NULL){
        // printfColor(RED,"Error opening file\n",true);
        fprintf(stderr,RED"Error opening file\n"RESET);
        return -1;
    }
    fseek(file,0,SEEK_SET);
    int count = 0;
    char ch;
    while((ch=fgetc(file))!=EOF){
        if(ch=='\n'){
            count++;
        }
    }
    fseek(file,0,SEEK_SET);
    return count;
}
char* logExecute(int num,Prompt* prompt){
    if(num<=0 && num>MAX_LINES){
        fprintf(stderr,RED"Invalid number of commands\n"RESET);
        // printfColor(RED,"Invalid number of commands\n",true);
        return false;
    }
    char* pathToUserLog = pathDynamicFunction(prompt);
    FILE* file = fopen(pathToUserLog,"r");
    free(pathToUserLog);
    int numberLine = numberOflines(file);
    num = numberLine - num + 1;
    if(num<=0){
        // printfColor(RED,"Invalid number of commands\n",true);
        fprintf(stderr,RED"Invalid number of commands\n"RESET);
        return false;
    }
    if(file==NULL){
        // printfColor(RED,"Error opening user.log\n",true);
        fprintf(stderr,RED"Error opening user.log\n"RESET);
        return false;
    }
    char* buffer = (char*)malloc(1000*sizeof(char));
    if(buffer==NULL){
        // printfColor(RED,"Error allocating memory\n",true);
        fprintf(stderr,RED"Error allocating memory\n"RESET);
        return false;
    }
    int count = 0;
    while(fgets(buffer,1000,file)!=NULL){
        if(++count==num){
            break;
        }
    }
    fclose(file);
    return buffer;
}
bool logPurge(Prompt* prompt){
    char* pathToUserLog = pathDynamicFunction(prompt);
    FILE* file = fopen(pathToUserLog,"w+");
    free(pathToUserLog);
    if(file==NULL){
        // printfColor(RED,"Error opening user.log\n",true);
        fprintf(stderr,RED"Error opening user.log\n"RESET);
        return false;
    }
    fclose(file);
    return true;
}
bool logDisplay(Prompt* prompt){
    char* pathToUserLog = pathDynamicFunction(prompt);
    FILE* file = fopen(pathToUserLog,"r");
    free(pathToUserLog);
    if(file==NULL){
        // printfColor(RED,"Error opening user.log\n",true);
        fprintf(stderr,RED"Error opening user.log\n"RESET);
        return false;
    }
    char buffer[1000];
    while(fgets(buffer,1000,file)!=NULL){
        printf("%s",buffer);
    }
    fclose(file);
    return true;
}