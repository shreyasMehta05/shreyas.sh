#include"reveal.h"
#include <sys/stat.h>

int compare(const void* a, const void* b){
    return strcmp(*(const char**)a,*(const char**)b);
}

filesList* sort(filesList* list){
    qsort(list->list,list->n,sizeof(char*),compare);
    return list;
}

void permission(mode_t mode){
    if(S_ISDIR(mode)){
        // directory
        printfColor(BLUE,"d",false);
        printf("%s",BLUE);
    }
    else if((mode & S_IFMT) == S_IFREG && (mode & (S_IXUSR | S_IXGRP | S_IXOTH))){
        // executable
        printfColor(GREEN,"l",false);
        printf("%s",GREEN);
    }
    else if(S_ISREG(mode)){
        // file
        printfColor(WHITE,"-",false);
        printf("%s",WHITE);
    }
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

void printDetails(char* name,char* path){
    struct stat fileStat;
    char* temp = (char*)malloc(strlen(path)+strlen(name)+2); // 1 for / and 1 for \0
    strcpy(temp,path);
    strcat(temp,"/");
    strcat(temp,name);
    if(stat(temp,&fileStat)<0){
        // printfColor(RED,"Error getting file stats\n",true);
        fprintf(stderr,RED"Error getting file stats\n"RESET);
        free(temp);
        return;
    }
    
    permission(fileStat.st_mode);
    printf(" %ld",fileStat.st_nlink);
    struct passwd* pwd = getpwuid(fileStat.st_uid);
    struct group* grp = getgrgid(fileStat.st_gid);
    printf(" %s %s %ld ",pwd->pw_name,grp->gr_name,fileStat.st_size);
    char* time = ctime(&fileStat.st_mtime);
    time[strlen(time)-1]='\0';
    printf("%s ",time);
    printf(" %s\n",name);
    printf("%s",RESET);
    free(temp);
}
void colorACCtoFiles(struct dirent* entry,char* path,char* name){
    struct stat fileStat;
    char* temp = (char*)malloc(strlen(path)+strlen(name)+2);
    strcpy(temp,path);
    strcat(temp,"/");
    strcat(temp,name);
    if(stat(temp,&fileStat)<0){
        // printfColor(RED,"Error getting file stats\n",true);
        fprintf(stderr,RED"Error getting file stats\n"RESET);
        free(temp);
        return;
    }
    if(S_ISDIR(fileStat.st_mode)){
        // directory
        printf("%s",BLUE);
    }
    else if((fileStat.st_mode & S_IFMT) == S_IFREG && (fileStat.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))){
        // executable
        printf("%s",GREEN);
    }
    else if(S_ISREG(fileStat.st_mode)){
        // file
        printf("%s",WHITE);
    }
    free(temp);
}
void revealRetList(char* path,Prompt* prompt,bool flagA,bool flagL){
    // DIR* dir = opendir(path);
    // if(dir==NULL){
    //     printfColor(RED,"Error opening directory\n",true);
    //     return;
    // }
    // struct dirent* entry = readdir(dir);
    // while(entry){
    //     if(flagA==false && entry->d_name[0]=='.'){
    //         entry = readdir(dir);
    //         continue;
    //     }
    //     if(flagL){
    //         printDetails(entry->d_name,path);
    //     }
    //     else{
    //         colorACCtoFiles(entry,path,entry->d_name);
    //         printf("%s\n",entry->d_name);
    //         printf("%s",RESET);
    //     }
    //     entry = readdir(dir);
    // }
    // closedir(dir);
    filesList* list = getFiles(path);
    if(list==NULL){
        return;
    }
    list = sort(list);
    for(int i=0;i<list->n;i++){
        if(flagA==false && list->list[i][0]=='.'){
            continue;
        }
        if(flagL){
            printDetails(list->list[i],path);
        }
        else{
            colorACCtoFiles(NULL,path,list->list[i]);
            printf("%s\n",list->list[i]);
            printf("%s",RESET);
        }
    }
    for(int i=0;i<list->n;i++){
        free(list->list[i]);
    }
    free(list->list);
    free(list);
}
void printDetailsFile(char* path){
    struct stat fileStat;
    if(stat(path,&fileStat)<0){
        // printfColor(RED,"Error getting file stats\n",true);
        fprintf(stderr,RED"Error getting file stats\n"RESET);
        return;
    }
    permission(fileStat.st_mode);
    printf(" %ld",fileStat.st_nlink);
    struct passwd* pwd = getpwuid(fileStat.st_uid);
    struct group* grp = getgrgid(fileStat.st_gid);
    printf(" %s %s %ld ",pwd->pw_name,grp->gr_name,fileStat.st_size);
    char* time = ctime(&fileStat.st_mtime);
    time[strlen(time)-1]='\0';
    printf("%s ",time);
    printf(" %s\n",path);
    printf("%s",RESET);
}
bool isFile(char* path, bool flagL, bool flagA){
    // char* actualPath = malloc(sizeof(char)*1000);
    // actualPath = prompt->directory->directoryName;
    // if(actualPath[0]=='~'){
    //     char* home = prompt->directory->homeDirectory;
    //     char* temp = (char*)malloc(strlen(home)+strlen(actualPath));
    //     strcpy(temp,home);
    //     strcat(temp,actualPath+1);
    //     strcpy(actualPath,temp);
    //     free(temp);
    // }
    // if(actualPath[strlen(actualPath)-1]!='/'){
    //     strcat(actualPath,"/");
    // }
    // strcat(actualPath,path);
    

    struct stat fileStat;
    if(stat(path,&fileStat)<0){
        // printfColor(RED,"Error getting file stats\n",true);
        fprintf(stderr,RED"Error getting file stats\n"RESET);
        return false;
    }
    if(S_ISREG(fileStat.st_mode)){
        if(flagL){
            printDetailsFile(path);
        }
        else{
            printf("%s\n",path);
        }
        return true;
    }
    return false;

}
void reveal(char* token,Prompt* prompt,bool flagA,bool flagL,bool prev,char* path){
    if(path==NULL){
        path = prompt->directory->directoryName;
    }
    if(strcmp(path,"~")==0){
        path = prompt->directory->homeDirectory;
    }
    else if(strcmp(path,"-")==0){
        if(prompt->directory->lastWorkingDirectory==NULL){
            // printfColor(RED,"No last working directory found!\n",true);
            fprintf(stderr,RED"No last working directory found!\n"RESET);
            return;
        }
        path = prompt->directory->lastWorkingDirectory;
    }
    char* freeStore=NULL;
    if(path[0]=='~'){
        char* home = prompt->directory->homeDirectory;
        char* temp = (char*)malloc(strlen(home)+strlen(path));
        strcpy(temp,home);
        strcat(temp,path+1);
        path = temp;
        freeStore = temp;
    }
    // check if path is actually a file
    if(isFile(path,flagL,flagA)) return;
    revealRetList(path,prompt,flagA,flagL);
    printf("%s",RESET);
    if(freeStore!=NULL){
        free(freeStore);
    }

}

filesList* getFiles(char* path){
    DIR* dir = opendir(path);
    if(dir==NULL){
        // printfColor(RED,"Error opening directory\n",true);
        fprintf(stderr,RED"Error opening directory\n"RESET);
        return NULL;
    }
    struct dirent* entry = readdir(dir);
    filesList* list = (filesList*)malloc(sizeof(filesList));
    list->list = (char**)malloc(1000*sizeof(char*));
    list->n = 0;
    while(entry){
        list->list[list->n] = (char*)malloc(strlen(entry->d_name)+1);
        strcpy(list->list[list->n],entry->d_name);
        list->n++;
        entry = readdir(dir);
    }
    closedir(dir);
    return list;
}