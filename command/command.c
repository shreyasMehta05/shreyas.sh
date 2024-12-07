#include"command.h"
#include"signals.h"
#include"globals.h"
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include"../alias/functions.h"


extern ProcessList** globalProcessList;  // Definition
extern char* COMMAND;                    // Definition
extern int foregroundPid; 
// ProcessList** globalProcessList;

// trim whitespace from the string
void trimWhitespace(char *str) {
    if(str==NULL){
        return;
    }

    char *start = str;
    while (isspace((unsigned char)*start)) start++;

    char *end = start + strlen(start) - 1;
    while(end > start && isspace((unsigned char)*end)) end--;

    *(end+1) = '\0';

    memmove(str, start, strlen(start) + 1);
}

// remove leading whitespaces from the string
void removeLeadingWhitespaces(char *str) {
    trimWhitespace(str);
}
// 
// ctrl+d handler
void handleCtrlD(Prompt* prompt,bool print) {
    // Send SIGTERM to all background processes first
    printf("\nCleaning up..."); fflush(stdout);
    for (int i = 0; i < prompt->processList->count; i++) {
        pid_t pid = prompt->processList->processes[i].pid;
        kill(pid, SIGTERM);
        prompt->processList->processes[i].status = STOPPED;
        // Wait for the process to exit, using WNOHANG to avoid blocking
        if (waitpid(pid, NULL, WNOHANG) == 0) {
            // If the process is still running, wait briefly and then force kill
            usleep(100000); // 100ms
            // sleep(1); // Give the process some time to terminate
            kill(pid, SIGKILL);
            waitpid(pid, NULL, 0);  // Ensure the process is reaped
        }
        if(prompt->processList->count>0)
        printf("\rCleaning up... %d%%", (i + 1) * 100 / prompt->processList->count);
        fflush(stdout);
    }

    freeAliasList();

    // Print newline for clean terminal output
    if(print){
        printf("\n");
    }else
    printf("\n");

    // Exit the shell
    exit(EXIT_SUCCESS);
}
// take input from the user
char* inputCommand(Prompt* prompt){
    char* command=(char*)malloc(BUFFER_TERMINAL_COMMAND*sizeof(char));
    if(command==NULL){
        fprintf(stderr, RED"Error: Memory allocation failed\n"RESET);
        exit(EXIT_FAILURE);
    }
    if(fgets(command,BUFFER_TERMINAL_COMMAND,stdin)==NULL){
        handleCtrlD(prompt,true);
    } 
    return command;
}
// hop helper function
void hopHelper(char* token,char* commandPtr,Prompt* prompt){
    if(commandPtr==NULL || strlen(commandPtr)==0){
        hop("~",prompt);
        return;
    }
    token = strtok_r(NULL," ",&commandPtr);
    char* actualCommand = (char*)malloc(BUFFER_TERMINAL_COMMAND*sizeof(char));
    if(token==NULL){
        hop("~",prompt);
        return;
    }
    strcpy(actualCommand,token);
    while(token){
        removeLeadingWhitespaces(token);
        actualCommand = strcat(actualCommand," ");
        hop(token,prompt);
        token = strtok_r(NULL," ",&commandPtr);
    }
}
// reveal helper function
void revealHelper(char* token,char* commandPtr,Prompt* prompt){
    if(commandPtr==NULL || strlen(commandPtr)==0){
        reveal(token,prompt,false,false,false,".");
        return;
    }
    token = strtok_r(NULL," ",&commandPtr);
    bool flagA = false,flagL = false, prev = false;  char* path = NULL;
    while(token){
        removeLeadingWhitespaces(token);
        if(token[0]=='-' && strlen(token)==1){
            prev = true;
            path =token;
        }
        else if(token[0]=='-'){
            for(int i=1;i<strlen(token);i++){
                if(token[i]=='a'){
                    flagA = true;
                }
                else if(token[i]=='l'){
                    flagL = true;
                }
            }
        }
        else{
            path = token;
        }
        token = strtok_r(NULL," ",&commandPtr);
    }
    reveal(token,prompt,flagA,flagL,prev,path);
    char *actualCommand = (char*)malloc(BUFFER_TERMINAL_COMMAND*sizeof(char));
    strcpy(actualCommand,"reveal ");
    if(flagA){
        strcat(actualCommand,"-a ");
    }
    if(flagL){
        strcat(actualCommand,"-l ");
    }
    if(path==NULL || strlen(path)==0){
        strcat(actualCommand,".");
    }
    else{
        strcat(actualCommand,path);
    }
}
// log helper function
void logHelper(char* token,char* commandPtr,Prompt* prompt){
    trimWhitespace(token);
    token = strtok_r(NULL," ",&commandPtr);
    trimWhitespace(token);
    if(token==NULL){
        logDisplay(prompt);
        return;
    }
    if(strstr(token,"purge")){
        logPurge(prompt);
        return;
    }
    if(strcmp(token,"execute")==0){
        token = strtok_r(NULL," ",&commandPtr);
        trimWhitespace(token);
        // check if the token is a number
        if(token==NULL){
            fprintf(stderr,RED"Invalid Arguments\n"RESET);
            return;
        }
        for(int i=0;i<strlen(token);i++){
            if(!isdigit(token[i])){
                fprintf(stderr,RED"Invalid Arguments\n"RESET);
                return;
            }
        }
        int num = atoi(token);
        char* command = logExecute(num,prompt);
        if(command == NULL) return;
        executeCommands(command,prompt);
        return;
    }
}

void backgroundProcess(char* command,Prompt* prompt){
    if(command==NULL){
        return;
    }
    // shell commands run via exec
    globalProcessList = &(prompt->processList);
    trimWhitespace(command);
    
    tcsetpgrp(STDIN_FILENO, getpid());
    int pid = fork();
    
    if(pid==0){


        int childPid = getpid();
        setpgid(childPid,childPid);
        
        addProcess(&(prompt->processList),command,childPid);
        char* commandPtr;

        char* token = strtok_r(command," ",&commandPtr);
        removeLeadingWhitespaces(token);
        char* args[100];
        int i=0;
        printf(GREEN"[%d %s]%s\n",childPid,token,RESET);
        while (token && i < 100) {
            removeLeadingWhitespaces(token);
            if (token[0] == '"' || token[0] == '\'') {
                char quoteType = token[0];
                token++;
                char quotedString[1000] = {0};
                strcat(quotedString, token);
                char *endQuote = strchr(quotedString, quoteType);
                while (endQuote == NULL) {
                    char *nextToken = strtok_r(NULL, " ", &commandPtr);
                    if (nextToken == NULL) {
                        fprintf(stderr, "Error: unmatched quote\n");
                        return;
                    }
                    strcat(quotedString, " ");
                    strcat(quotedString, nextToken);
                    endQuote = strchr(quotedString, quoteType);
                }

                *endQuote = '\0';
                args[i++] = strdup(quotedString);
            } 
            else {
                args[i++] = token;
            }
            token = strtok_r(NULL, " ", &commandPtr);
        }

        args[i] = NULL;
        // signal(SIGTSTP,SIG_IGN);
        // signal(SIGINT,SIG_IGN);
        execvp(args[0],args);
        token = strtok(command," ");
        trimWhitespace(token);
        exit(EXIT_FAILURE);
    }
    else if(pid<0){
        fprintf(stderr,RED"Error: Failed to create child process\n"RESET);
        exit(EXIT_FAILURE);
    }
    else{
        // tokenise the 1st argument
        signal(SIGCHLD,backgroundProcessHandler);
        setpgid(pid,pid);
        addProcess(&(prompt->processList),command,pid);
        return;
    }

}
// proclore helper function
void procloreHelper(char* token,char* commandPtr,Prompt* prompt){
    if(commandPtr==NULL || strlen(commandPtr)==0){
        proclore(getpid(),prompt);
        return;
    }
    token = strtok_r(NULL," ",&commandPtr);
    removeLeadingWhitespaces(token);
    if(token==NULL){
        fprintf(stderr,RED"Invalid Arguments\n"RESET);
        return;
    }
    for(int i=0;i<strlen(token);i++){
        if(!isdigit(token[i])){
            fprintf(stderr,RED"Invalid Arguments\n"RESET);
            return;
        }
    }
    int ID = atoi(token);
    proclore(ID,prompt);
}
void seekHelper(char* token,char* commandPtr,Prompt* Prompt){
    // check for flags
    bool flagF = true,flagD = true,flagE = false;
    if(commandPtr==NULL || strlen(commandPtr)==0){
        fprintf(stderr,RED"Invalid Arguments\n"RESET);
        return;
    }
    token = strtok_r(NULL," ",&commandPtr);
    removeLeadingWhitespaces(token);
    int cnt = 0;
    while(token[0]=='-' && cnt<3){
        for(int i=1;i<strlen(token);i++){
            if(token[i]=='f'){
                flagD = false;
            }
            else if(token[i]=='d'){
                flagF = false;
            }
            else if(token[i]=='e'){
                flagE = true;
            }
        }
        token = strtok_r(NULL," ",&commandPtr);
        removeLeadingWhitespaces(token);
        cnt++;
    }
    char* searchPath = token;
    token = strtok_r(NULL," ",&commandPtr);
    
    char* dirName = token;
    printf("dirName: %s\n",dirName);
    seek(searchPath,dirName,flagF,flagD,flagE,Prompt);

}

void foregroundProcess(char* command,Prompt* prompt){

    if(command==NULL){
        return;
    }
    if(executeAliasFunction(command,prompt)==1){
        return;
    }
    // if any of the process contains more than 2 seconds to run we store that command
    int originalStdin = -1;  // Initialize as -1 to check later if redirection occurred
    int originalStdout = -1;  // Initialize as -1 to check later if redirection occurred
    globalProcessList = &(prompt->processList);
    // check for redirection
    bool redirValid = handleRedirection(command,prompt, &originalStdin, &originalStdout);
    if(!redirValid){
        return;
    }
    // we need to remove the > and < corresponding input and output arguments
    char* originalCommand = strdup(command);
    removeRedirectionSymbols(command);
    char* ptr=strdup(command);
    char* commandPtr;
    char* token = strtok_r(command," ",&commandPtr);
    removeLeadingWhitespaces(token);
    if(strcmp(token,"hop")==0){
        if(originalStdin!=-1){
            // this means input redirection and we have to extract the args
            char* args[100];
            command = getArgs(ptr,args,true);
            commandPtr = NULL;
            token = strtok_r(command," ",&commandPtr);
            removeLeadingWhitespace(token);
        }
        hopHelper(token,commandPtr,prompt);
        if(originalStdout!=-1||originalStdin!=-1){
            restoreRedirection(originalStdin, originalStdout);
        }
    }
    else if(strcmp(token,"reveal")==0){
        if(originalStdin!=-1){
            // this means input redirection and we have to extract the args
            char* args[100];
            printf("command: %s\n",ptr);
            command = getArgs(ptr,args,true);
            commandPtr=NULL;
            token = strtok_r(command," ",&commandPtr);
            removeLeadingWhitespace(token);
        }
        revealHelper(token,commandPtr,prompt);
        if (originalStdout != -1 || originalStdin != -1) {
            restoreRedirection(originalStdin, originalStdout);
        }

        
    }
    else if(strstr(token,"log")){
        
        logHelper(token,commandPtr,prompt);
        if(originalStdin!=-1||originalStdout!=-1){
            restoreRedirection(originalStdin, originalStdout);
        }
    }
    else if(strcmp(token,"proclore")==0){
        if(originalStdin!=-1){
            // this means input redirection and we have to extract the args
            char* args[100];
            command = getArgs(command,args,true);
            commandPtr=NULL;
            token = strtok_r(command," ",&commandPtr);
            removeLeadingWhitespace(token);
        }
        procloreHelper(token,commandPtr,prompt);
        if(originalStdin!=-1||originalStdout!=-1){
            restoreRedirection(originalStdin, originalStdout);
        }
    }
    else if(strcmp(token,"seek")==0){
        if(originalStdin!=-1){
            // this means input redirection and we have to extract the args
            char* args[100];
            printf("command: %s\n",ptr);
            command = getArgs(ptr,args,true);
            commandPtr=NULL;
            token = strtok_r(command," ",&commandPtr);
            removeLeadingWhitespace(token);
        }
        seekHelper(token,commandPtr,prompt);
        if(originalStdin!=-1||originalStdout!=-1){
            restoreRedirection(originalStdin, originalStdout);
        }
    }else if(strcmp(token,"q")==0){
        handleCtrlD(prompt,false);
        exit(EXIT_SUCCESS);
    }
    else if(strcmp(token,"activities")==0){
        activities(&(prompt->processList));
        if (originalStdout != -1 || originalStdin != -1) {
            restoreRedirection(originalStdin, originalStdout);
        }     
    }
    else if(strcmp(token,"ping")==0){
        if(originalStdin!=-1){
            // this means input redirection and we have to extract the args
            char* args[100];
            command = getArgs(ptr,args,true);
            commandPtr=NULL;
            token = strtok_r(command," ",&commandPtr);
            removeLeadingWhitespace(token);
        }
        token = strtok_r(NULL," ",&commandPtr);
        removeLeadingWhitespaces(token);
        if(token==NULL){
            fprintf(stderr,RED"Invalid Arguments\n"RESET);
            restoreRedirection(originalStdin, originalStdout);
            return;
        }
        for(int i=0;i<strlen(token);i++){
            if(!isdigit(token[i])){
                fprintf(stderr,RED"Invalid Arguments\n"RESET);
                restoreRedirection(originalStdin, originalStdout);
                return;
            }
        }
        int pid = atoi(token);
        token = strtok_r(NULL," ",&commandPtr);
        removeLeadingWhitespaces(token);
        if(token==NULL){
            fprintf(stderr,RED"Invalid Arguments\n"RESET);
            restoreRedirection(originalStdin, originalStdout);
            return;
        }
        for(int i=0;i<strlen(token);i++){
            if(!isdigit(token[i])){
                fprintf(stderr,RED"Invalid Arguments\n"RESET);
                restoreRedirection(originalStdin, originalStdout);
                return;
            }
        }
        int signal = atoi(token);
        ping(pid,signal,prompt);
        if(originalStdin!=-1||originalStdout!=-1){
            restoreRedirection(originalStdin, originalStdout);
        }
    }
    else if (strcmp(token, "fg") == 0) {
        if(originalStdin != -1) {
            // this means input redirection and we have to extract the args
            char* args[100];
            command = getArgs(ptr, args, true);
            commandPtr = NULL;
            token = strtok_r(command, " ", &commandPtr);
            removeLeadingWhitespace(token);
        }
        token = strtok_r(NULL, " ", &commandPtr);
        removeLeadingWhitespaces(token);
        if (token == NULL) {
            fprintf(stderr, RED"Invalid Arguments\n"RESET);
            restoreRedirection(originalStdin, originalStdout);
            return;
        }
        for (int i = 0; i < strlen(token); i++) {
            if (!isdigit(token[i])) {
                fprintf(stderr, RED"Invalid Arguments\n"RESET);
                restoreRedirection(originalStdin, originalStdout);
                return;
            }
        }
        int pid = atoi(token);
        COMMAND = strdup(command);
        int bgPID = fg(pid, &(prompt->processList));  // Retrieve the process from background
        if (bgPID == -1) {
            restoreRedirection(originalStdin, originalStdout);
            return;
        }
        foregroundPid = bgPID;

        if(tcsetpgrp(STDIN_FILENO, getpgid(pid)) == -1) {
            // perror(RED"Failed to set terminal control to the foreground process"RESET);
            fprintf(stderr, RED"Failed to set terminal control to the foreground process[Maybe terminated!]\n"RESET);
            removeProcess(globalProcessList,foregroundPid);
        }
        struct timeval start, end;
        gettimeofday(&start, NULL);
        signal(SIGTTOU, SIG_IGN);    
        kill(bgPID, SIGCONT);
        Process* p = getProcessByPid(prompt->processList, bgPID);
        if (p == NULL) {
            restoreRedirection(originalStdin, originalStdout);
            return;
        }
        p->status = RUNNING;
        // handleForegroundProcess(bgPID);
        // process is stopped
        signal(SIGTSTP, handleSigtstp);
        signal(SIGINT, handleSigint);
        int status;
        // waitpid(bgPID, NULL, WUNTRACED);
        waitpid(bgPID, &status, WUNTRACED);
        if(WIFEXITED(status)){
            removeProcess(globalProcessList, bgPID);
        }
        else if(WIFSIGNALED(status)){
            // only remove the process if it is terminated
            removeProcess(globalProcessList, bgPID);
        }
        // else if(WIFSTOPPED(status)){
        //     // this means the process is stopped
        //     addProcess(&(prompt->processList), COMMAND, bgPID);
        //     Process* p = getProcessByPid(prompt->processList, bgPID);
        //     if (p == NULL) {
        //         restoreRedirection(originalStdin, originalStdout);
        //         return;
        //     }
        //     p->status = STOPPED;
        // }
        
        gettimeofday(&end, NULL);
        long seconds = end.tv_sec - start.tv_sec;
        // printf("Seconds: %ld\n", seconds);
        p->status = STOPPED;
        
        if (tcsetpgrp(STDIN_FILENO, getpid()) == -1) {
            fprintf(stderr, RED"Failed to set terminal control to the shell\n"RESET);
            removeProcess(globalProcessList,foregroundPid);
        }
        foregroundPid = -1;  // Reset the foreground process ID
        if(originalStdin!=-1||originalStdout!=-1){
            ptr = strdup(originalCommand);
            restoreRedirection(originalStdin, originalStdout);
        }
        if (seconds > 2) {
            prompt->command2sec = strdup(ptr);
        }
        restoreRedirection(originalStdin, originalStdout);
    }
    else if(strcmp(token,"bg")==0){
        if(originalStdin!=-1){
            // this means input redirection and we have to extract the args
            char* args[100];
            command = getArgs(ptr,args,true);
            commandPtr=NULL;
            token = strtok_r(command," ",&commandPtr);
            removeLeadingWhitespace(token);
        }
        token = strtok_r(NULL," ",&commandPtr);
        removeLeadingWhitespaces(token);
        if(token==NULL){
            fprintf(stderr,RED"Invalid Arguments\n"RESET);
            restoreRedirection(originalStdin, originalStdout);
            return;
        }
        for(int i=0;i<strlen(token);i++){
            if(!isdigit(token[i])){
                fprintf(stderr,RED"Invalid Arguments\n"RESET);
                restoreRedirection(originalStdin, originalStdout);
                return;
            }
        }
        int pid = atoi(token);
        bg(pid,&(prompt->processList));
        restoreRedirection(originalStdin, originalStdout);
    }
    else if(strcmp(token,"neonate")==0){
        if(originalStdin!=-1){
            // this means input redirection and we have to extract the args
            char* args[100];
            command = getArgs(ptr,args,true);
            commandPtr=NULL;
            token = strtok_r(command," ",&commandPtr);
            removeLeadingWhitespaces(token);
        }
        // check for -n flag
        // if -n flag is not present then we will take the default value of 10
        token = strtok_r(NULL," ",&commandPtr);
        removeLeadingWhitespaces(token);
        struct timeval start,end;
        gettimeofday(&start, NULL);
        
        if(token==NULL){
            neonate(10);
        }
        else if(token[0]=='-' && token[1]=='n'){
            token = strtok_r(NULL," ",&commandPtr);
            removeLeadingWhitespaces(token);
            if(token==NULL){
                fprintf(stderr,RED"Invalid Arguments\n"RESET);
                restoreRedirection(originalStdin, originalStdout);
                return;
            }
            for(int i=0;i<strlen(token);i++){
                if(!isdigit(token[i])){
                    fprintf(stderr,RED"Invalid Arguments\n"RESET);
                    restoreRedirection(originalStdin, originalStdout);
                    return;
                }
            }
            int time = atoi(token);
            neonate(time);
        }
        else{
            if(token==NULL){
                fprintf(stderr,RED"Invalid Arguments\n"RESET);
                restoreRedirection(originalStdin, originalStdout);
                return;
            }
            for(int i=0;i<strlen(token);i++){
                if(!isdigit(token[i])){
                    fprintf(stderr,RED"Invalid Arguments\n"RESET);
                    restoreRedirection(originalStdin, originalStdout);
                    return;
                }
            }
            int time = atoi(token);
            removeLeadingWhitespace(token);
            neonate(time);
        }
        gettimeofday(&end, NULL);
        long seconds = end.tv_sec - start.tv_sec;
        if(originalStdin!=-1||originalStdout!=-1){
            ptr = strdup(originalCommand);
        }
        restoreRedirection(originalStdin, originalStdout);
        if(seconds>2){
            char temp[1000];
            sprintf(temp,"%s: %ldsec",ptr,seconds);
            prompt->command2sec = strdup(temp);
        }
        
    }
    else if(strcmp("iMan",token)==0){
        if(originalStdin!=-1){
            // this means input redirection and we have to extract the args
            char* args[100];
            command = getArgs(ptr,args,true);
            commandPtr=NULL;
            token = strtok_r(command," ",&commandPtr);
            removeLeadingWhitespace(token);
        }
        token = strtok_r(NULL," ",&commandPtr);
        removeLeadingWhitespaces(token);
        if(token==NULL){
            fprintf(stderr,RED"Invalid Arguments\n"RESET);
            restoreRedirection(originalStdin, originalStdout);
            return;
        }
        struct timeval start,end;
        gettimeofday(&start, NULL);
        removeLeadingWhitespaces(token);
        iMan(token);
        gettimeofday(&end, NULL);
        if(originalStdin!=-1||originalStdout!=-1){
            // restoreRedirection(originalStdin, originalStdout);
            ptr = strdup(originalCommand);
        }
        restoreRedirection(originalStdin, originalStdout);
        long seconds = end.tv_sec - start.tv_sec;
        if(seconds>2){
            char temp[1000];
            sprintf(temp,"%s: %ldsec",ptr,seconds);
            prompt->command2sec = strdup(temp);
        }
    }
    else{
        // set up signal handlers
        // setupSignalHandlers();
        // signal(SIGTTOU, SIG_IGN);  // Ignore SIGTTOU for background processes
        int pid = fork();
        // setpgid(pid,pid);
        foregroundPid = pid;
        COMMAND = strdup(command);// get full command
        
        struct timeval start,end;
        gettimeofday(&start, NULL);
        if(pid==0){
            // use execvp to run shell commands
            // printf(GREEN"[%s]%s\n",token,RESET);
            setupSignalForForeground();
            // tcsetpgrp(STDIN_FILENO, getpid());
            char* commandPtr;
            char* token = strtok_r(ptr," ",&commandPtr);
            removeLeadingWhitespace(token);
            char* args[100];
            
            if(originalStdin==-1){
                // this means no input redirection
                int i=0;
                while(token && i<100){
                    removeLeadingWhitespace(token);
                    if(token[0]=='"' || token[0]=='\''){
                        char quoteType = token[0];
                        token++;
                        char quotedString[1000] = {0};
                        strcat(quotedString,token);
                        char* endQuote = strchr(quotedString,quoteType);
                        while(endQuote==NULL){
                            char* nextToken = strtok_r(NULL," ",&commandPtr);
                            if(nextToken==NULL){
                                fprintf(stderr,"Error: unmatched quote\n");
                                return;
                            }
                            strcat(quotedString," ");
                            strcat(quotedString,nextToken);
                            endQuote = strchr(quotedString,quoteType);
                        }
                        *endQuote = '\0';
                        args[i++] = strdup(quotedString);
                    }
                    else{
                        args[i++] = token;
                    }
                    token = strtok_r(NULL," ",&commandPtr);
                }
                args[i] = NULL;
                execvp(args[0],args);
            }
            else{
                // this means input redirection
                char* args[100];
                // getArgs(command,args);
                args[0]=strdup(token);
                args[1]=NULL;
                execvp(args[0],args);
            }
            // this means the command is invalid
            token = strtok(command," ");
            trimWhitespace(token);
            restoreRedirection(originalStdin, originalStdout);
            fprintf(stderr,RED"Error: Invalid command %s\n"RESET,token);
            exit(EXIT_FAILURE);
        }
        else if(pid<0){
            restoreRedirection(originalStdin, originalStdout);
            fprintf(stderr,RED"Error: Failed to create child process\n"RESET);
            exit(EXIT_FAILURE);
        }
        else{
            // waitpid(pid,NULL,0);
            int status;
            // tcsetpgrp(STDIN_FILENO, pid);
            waitpid(pid, &status, WUNTRACED);  // Wait for process to finish or be stopped
            if(WIFSTOPPED(status)){
                // this means the process is stopped
                addProcess(&(prompt->processList),command,pid);
                // printf("%s[Process with pid %d is stopped]%s\n", YELLOW, pid, RESET);
                Process* p = getProcessByPid(*globalProcessList, pid);
                if (p == NULL) {
                    restoreRedirection(originalStdin, originalStdout);
                    return;
                }
                p->status = STOPPED;
            }
            else if(WIFEXITED(status)){
                Process* p = getProcessByPid(*globalProcessList, pid);
                if(p!=NULL) removeProcess(&(prompt->processList),pid);
            }
            
            if(originalStdin!=-1||originalStdout!=-1){
                ptr = strdup(originalCommand);
            }
            restoreRedirection(originalStdin, originalStdout);
            gettimeofday(&end, NULL);
            long seconds = end.tv_sec - start.tv_sec;
            if(seconds>2){
                // store in the form of command:seconds
                char temp[1000];
                sprintf(temp,"%s: %ldsec",ptr,seconds);
                prompt->command2sec = strdup(temp);
                
            }
            // tcsetpgrp(STDIN_FILENO, getpid());
            foregroundPid = -1;
            free(COMMAND);
            COMMAND = NULL;
            // signal(SIGTTOU, SIG_DFL);  // Restore default SIGTTOU behavior
            
            return;
        }
    }
}
void executeCommand(char* command,Prompt* prompt){
    
    command=replaceAliasesInString(command);
    
    
    trimWhitespace(command); 
    if(strstr(command,"&")==NULL){
        if(strstr(command,"|")!=NULL){
            executePipedCommands(command,prompt);
            return;
        }
        foregroundProcess(command,prompt);
        return;
    }
    if(strstr(command,"|")!=NULL){
        executePipedCommands(command,prompt);
        return;
    }
    char* processPtr;
    char* process = strtok_r(command,"&",&processPtr);
    backgroundProcess(process,prompt);
    while (process){
        trimWhitespace(process);
        if(strlen(process)==0){
            break;
        }
        if(strstr(processPtr, "&") == NULL) {
            process = strtok_r(NULL, "&", &processPtr);
            foregroundProcess(process, prompt);
            return;
        } else {
            process = strtok_r(NULL, "&", &processPtr);
            backgroundProcess(process, prompt);
        }
    }

}
void tokenise(char* command,Prompt* prompt){
    if(command==NULL || strlen(command)==0){
        return;
    }
    if(strstr(command,"log")==NULL){
        logCommandUser(command,prompt);
    }
    char* singleCommandPtr;
    char* singleCommand = strtok_r(command,";",&singleCommandPtr);
    while(singleCommand){
        removeLeadingWhitespaces(singleCommand);
        executeCommand(singleCommand,prompt);
        singleCommand = strtok_r(NULL,";",&singleCommandPtr);
    }

}
bool executeCommands(char* command,Prompt* prompt){
    if(command[strlen(command)-1]=='\n'){
        command[strlen(command)-1] = '\0';
    }
    tokenise(command,prompt);
    return true;
}

// code for piping
#include <unistd.h>
#include <fcntl.h>

void executePipedCommands(char* command, Prompt* prompt) {
    char* commands[100]; // Array to hold individual commands separated by pipes
    char* commandPtr;
    int numCommands = 0;
    bool isInvalid = false;
    int cntPipes = 0;
    for(int i=0;i<strlen(command);i++){
        if(command[i]=='|'){
            cntPipes++;
        }
    }
    // Tokenize the input by pipe symbols
    char* token = strtok_r(command, "|", &commandPtr);
    while (token != NULL) {
        // Trim whitespace from the token to check for empty commands
        char* trimmedCommand = strdup(token);
        trimWhitespace(trimmedCommand); // Assuming this trims leading/trailing spaces
        
        // Check if the command is empty
        if (strlen(trimmedCommand) == 0) {
            isInvalid = true;
            fprintf(stderr, RED"Error: Invalid use of pipe\n"RESET);
            free(trimmedCommand);
            return;
        }


        commands[numCommands++] = trimmedCommand;
        token = strtok_r(NULL, "|", &commandPtr);
    }
    commands[numCommands] = NULL;
    if(isInvalid || numCommands == 0 || cntPipes!=numCommands-1) {
        
        fprintf(stderr, RED"Error: Invalid use of pipe\n"RESET);
        return;
    }
    // If there's only one command, no need for pipes
    if (numCommands == 1) {
        executeSingleCommand(commands[0], prompt);
        return;
    }

    int pipefds[2 * (numCommands - 1)]; // Create pipes for communication between commands

    for (int i = 0; i < numCommands - 1; i++) {
        if (pipe(pipefds + i * 2) == -1) {
            perror("Pipe failed");
            exit(EXIT_FAILURE);
        }
    }

    int pid;
    for (int i = 0; i < numCommands; i++) {
        pid = fork();

        if (pid == 0) {
            // Redirect output to the next pipe's write end (if not last command)
            if (i < numCommands - 1) {
                if (dup2(pipefds[i * 2 + 1], STDOUT_FILENO) == -1) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            // Redirect input from the previous pipe's read end (if not first command)
            if (i > 0) {
                if (dup2(pipefds[(i - 1) * 2], STDIN_FILENO) == -1) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            // Close all pipe file descriptors
            for (int j = 0; j < 2 * (numCommands - 1); j++) {
                close(pipefds[j]);
            }

            // Execute the command
            executeSingleCommand(commands[i], prompt);
            exit(EXIT_FAILURE); // If exec fails
            
        }
    }

    // Parent process closes all pipe file descriptors
    for (int i = 0; i < 2 * (numCommands - 1); i++) {
        close(pipefds[i]);
    }

    // Wait for all child processes to finish
    for (int i = 0; i < numCommands; i++) {
        wait(NULL);
    }
}

void executeSingleCommand(char* command, Prompt* prompt) {
    trimWhitespace(command); 

    if(strstr(command, "&") == NULL) {
        foregroundProcess(command, prompt);

        return;
    }
    command = strtok(command, "&");
    backgroundProcess(command, prompt);
}

