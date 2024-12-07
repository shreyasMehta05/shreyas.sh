#include"process.h"
#include<signal.h>
#include"../command/globals.h"
extern int foregroundPid;
extern int shellPid;
Process* getProcessByPid(ProcessList* processList, int pid) {
    for (int i = 0; i < processList->count; i++) {
        if (processList->processes[i].pid == pid) {
            return &processList->processes[i];
        }
    }
    return NULL; // Process not found
}

void initProcessList(ProcessList** processList){
    (*processList)->count = 0;
}
void addProcess(ProcessList** processList, char* command, int pid){
     if (command == NULL) {
        fprintf(stderr, "Warning: command is NULL, setting to default value\n");
        command = "unknown";  // Set a default value to avoid crashing
    }
    if((*processList)->count >= MAX_PROCESSES){
        // Cannot add more processes so discard first 50% of the processes and terminate them
        for(int i=0; i<MAX_PROCESSES/2; i++){
            //kill the process
            kill((*processList)->processes[i].pid, SIGKILL);
            (*processList)->processes[i] = (*processList)->processes[i+MAX_PROCESSES/2];
        }
        (*processList)->count = MAX_PROCESSES/2;
    }
    // check if the process is already present
    for(int i=0; i<(*processList)->count; i++){
        if((*processList)->processes[i].pid == pid){
            return;
        }
    }
    Process* process = &(*processList)->processes[(*processList)->count];
    strcpy(process->command, command);
    process->pid = pid;
    process->status = RUNNING;
    (*processList)->count++;
}
void removeProcess(ProcessList** processList, int pid){
    for(int i=0; i<(*processList)->count; i++){
        if((*processList)->processes[i].pid == pid){
            for(int j=i; j<(*processList)->count-1; j++){
                (*processList)->processes[j] = (*processList)->processes[j+1];
            }
            (*processList)->count--;
            return;
        }
    }
}
void printProcesses(ProcessList** processList){
    for(int i=0; i<(*processList)->count; i++){
        Process* process = &(*processList)->processes[i];
        printf("%s",CYAN);
        printf("[%d]:[%s]-%s\n", process->pid, process->command, process->status == RUNNING ? "Running" : "Stopped");
        printf("%s",RESET); fflush(stdout);
    }
}
void updateProcesses(ProcessList** processList){
    for(int i=0; i<(*processList)->count; i++){
        Process* process = &(*processList)->processes[i];
        int status;
        int pid = waitpid(process->pid, &status, WNOHANG|WUNTRACED|WCONTINUED);
        if(pid >= 0){
            if(WIFSTOPPED(status)||WIFSIGNALED(status)|| WIFEXITED(status)){
                process->status = STOPPED;
            }
            else if(WIFCONTINUED(status)){
                process->status = RUNNING;
            }
            
        }
        else{
            process->status = STOPPED;
        }
        
    }
}

int compareProcesses(const void* a, const void* b){
    Process*processA = (Process*)a;
    Process*processB = (Process*)b;
    return strcmp(processA->command, processB->command);
}
void activities(ProcessList** processList){    
    // updateProcesses(processList);
    qsort((*processList)->processes, (*processList)->count, sizeof(Process), compareProcesses);
    printProcesses(processList);
}

void bg(pid_t pid, ProcessList** processList){
    Process* process = getProcessByPid(*processList, pid);
    if(process == NULL){
        // printf("%s[Process with pid %d not found]%s\n",RED, pid,RESET);
        fprintf(stderr, "%s[Process with pid %d not found]%s\n",RED, pid,RESET);
        return;
    }
    // if(pid != __getpgid(pid)){
        // foregroundPid Process comes to background
        signal(SIGSTOP, SIG_IGN);
        // signal(SIGINT, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        // printf("%s[Process with pid %d is not a background process]%s\n",RED,pid,RESET);
    // }

    kill(pid, SIGCONT);
    process->status = RUNNING;
    printf("%s[Process with pid %d is resumed in background!]%s\n", GREEN,pid,RESET);
}
int fg(pid_t pid, ProcessList** processList){
    Process* process = getProcessByPid(*processList, pid);
    if(process == NULL){
        // printf("[%sProcess with pid %d not found%s]\n",RED, pid,RESET);
        fprintf(stderr, "%s[Process with pid %d not found]%s\n",RED, pid,RESET);
        return -1;
    }
    if(process->status == STOPPED){
        return pid;
    }
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGSTOP, SIG_IGN);
    kill(pid, SIGSTOP);
    process->status = STOPPED;

    return pid;
}
void updateSingleProcess(ProcessList** processList, int pid){
    Process* process = getProcessByPid(*processList, pid);
    if(process == NULL){
        return;
    }
    int status;
    int result = waitpid(pid, &status, WNOHANG|WUNTRACED|WCONTINUED);
    if(result >= 0){
        if(WIFSTOPPED(status)||WIFSIGNALED(status)){
            process->status = STOPPED;
        }
        else if(WIFCONTINUED(status)){
            process->status = RUNNING;
        }
        if(WIFEXITED(status)){
            removeProcess(processList, pid);
        }
    }
    else{
        process->status = STOPPED;
    }
}