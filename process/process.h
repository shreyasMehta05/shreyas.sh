#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include"../display/color.h"
#ifndef PROCESS_H
#define PROCESS_H 1

#define MAX_PROCESSES 100
#define STOPPED 1
#define RUNNING 0

typedef struct Process {
    char command[4096];
    int pid;
    int status;
} Process;

typedef struct ProcessList {
    Process processes[MAX_PROCESSES];
    int count;
} ProcessList;

void initProcessList(ProcessList** processList);
void addProcess(ProcessList** processList, char* command, int pid);
void removeProcess(ProcessList** processList, int pid);
void printProcesses(ProcessList** processList);
void updateProcesses(ProcessList** processList);
int compareProcesses(const void* a, const void* b);
void activities(ProcessList** processList);
Process* getProcessByPid(ProcessList* processList, int pid);
void bg(pid_t pid, ProcessList** processList);
int fg(pid_t pid, ProcessList** processList);
void updateSingleProcess(ProcessList** processList, int pid);
int getStatusUsingPid(pid_t pid);
#endif