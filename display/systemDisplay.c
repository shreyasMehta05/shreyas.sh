#include"systemDisplay.h"

struct utsname* returnSystemInfo(){
    // get system information for node name
    struct utsname* systemInfo = (struct utsname* )malloc(sizeof(struct utsname));
    int returnValues = uname(systemInfo);
    if(returnValues==-1){
        fprintf(stderr,RED"Error Occoured in file: display/diplay.c --> returnSystemInfo()\n"RESET);
        free(systemInfo);
        exit(EXIT_FAILURE);
    }
    return systemInfo;
}

struct passwd* getUserDetails(){
    // get user details from passwd database(file)
    struct passwd* pw = NULL;
    uid_t effectiveUserID = getuid(); 
    pw = getpwuid(effectiveUserID);
    if(pw==NULL){
        fprintf(stderr,RED"Error Occoured in file: display/diplay.c --> getUserDetails()\n"RESET);
        exit(EXIT_FAILURE);
    }
    return pw;
}

char* returnUserAndSysStr(color* COLOR){
    // return user and system string
    char* str = malloc(sizeof(char)*BUFFER_TERMINAL_DISPLAY_PROMPT);
    struct passwd* pw = getUserDetails();
    struct utsname* systemInfo = returnSystemInfo();
    int writtenChar = snprintf(str,BUFFER_TERMINAL_DISPLAY_PROMPT,"<%s%s%s@%s%s:",BOLD,COLOR,pw->pw_name,systemInfo->nodename,RESET);
    free(systemInfo);
    if(writtenChar >= BUFFER_TERMINAL_DISPLAY_PROMPT){
        free(str);
        perror("Error Occoured in file: display/diplay.c --> returnUserAndSysStr()\n");
        exit(EXIT_FAILURE);
    }
    return str;
}

char* getDirectoryName(){
    // get the current directory name
    char* directoryName = (char *)malloc(sizeof(char)*BUFFER_TERMINAL_DISPLAY_DIR);
    if(getcwd(directoryName,BUFFER_TERMINAL_DISPLAY_DIR) == NULL){
        perror("Error Occoured in file: display/diplay.c --> getDirectoryName()\n");
        free(directoryName);
        exit(EXIT_FAILURE);
    }
    return directoryName; 
}

void generateTheDirectoryPath(char* homeDirectory,char* directoryName){
    // generate the path of the directory and update the directory name
    int homeDirectoryLength = strlen(homeDirectory); int directoryNameLength = strlen(directoryName);
    if(homeDirectoryLength>directoryNameLength){
        return;
    }
    if(strncmp(homeDirectory,directoryName,homeDirectoryLength)!=0){
        return;
    }
    if(homeDirectoryLength==directoryNameLength){
        free(directoryName);
        directoryName = (char *)malloc(sizeof(char)*BUFFER_TERMINAL_DISPLAY_DIR);
        snprintf(directoryName,BUFFER_TERMINAL_DISPLAY_DIR,"~");
        return;
    }
    char* str = (char *)malloc(sizeof(char)*BUFFER_TERMINAL_DISPLAY_DIR);
    snprintf(str,BUFFER_TERMINAL_DISPLAY_DIR,"~%s",directoryName+homeDirectoryLength);
    strcpy(directoryName,str);
    free(str);
    return;
}