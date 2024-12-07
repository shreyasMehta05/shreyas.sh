// Function to send a signal to a process
#include "signals.h"
#include "../process/process.h"
#include <errno.h>
#include "globals.h"
#include "../ping/ping.h"

extern Prompt* PROMPT;           // Definition
extern ProcessList** globalProcessList;  // Definition
extern char* COMMAND;                    // Definition
extern int foregroundPid; 

// used to send signal to a process
void sendSignal(pid_t pid, int signal_number) {
    signal_number = signal_number % 32;
    if (kill(pid, 0) == -1) {
        if (errno == ESRCH) {
            fprintf(stderr, RED"No such process found\n"RESET);
        } else {
            fprintf(stderr, RED"Error sending signal\n"RESET);
        }
        return;
    }
    // Send the signal
    if (kill(pid, signal_number) == -1) {
        fprintf(stderr, RED"Error sending signal\n"RESET);
    } else {
        printf(GREEN"[Sent signal %d to process with pid %d]\n"RESET, signal_number, pid);
    }
}
// Function to handle Ctrl-C (SIGINT)
void handleSigint(int signum){
    
    if (foregroundPid != -1) {
        if (kill(foregroundPid, SIGINT) == -1) {
            fprintf(stderr, RED"Error sending SIGINT to foreground process\n"RESET);
        } else {
            // printf(YELLOW"[Sent SIGINT to process PID: %d]\n"RESET, foregroundPid);
            removeProcess(globalProcessList, foregroundPid);
            foregroundPid = -1;
        }
    } else {
        // fprintf(stderr, "No foreground process to interrupt\n");
        printf("\n");
        printPrompt(PROMPT);
        fflush(stdout);
    }
}


// Function to handle background processes
void backgroundProcessHandler(int signum){
    int status;
    pid_t pid;

    // Wait for all child processes (including the specific one we just stopped)
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        Process* process = getProcessByPid(*globalProcessList, pid);
        if (process == NULL) {
            continue;
        }
        if (WIFEXITED(status)) {
            printf(GREEN"[Background process %d ended normally]\n"RESET, pid);
            removeProcess(globalProcessList, pid); // Remove the process from the list
        } else if (WIFSIGNALED(status)) {
            // printf(GREEN"[Background process %d with signal %d]\n", pid, WTERMSIG(status));
            printf(GREEN"[Background process %d ended]\n"RESET, pid);
            removeProcess(globalProcessList, pid); // Remove the process from the list optionally
        }
    }
}


// Function to handle Ctrl-Z (SIGTSTP)
void handleSigtstp(int signum) {
    if (foregroundPid != -1) {
        // check if this foreground process is now a background process
        for(int i=0; i<(*globalProcessList)->count; i++){
            if((*globalProcessList)->processes[i].pid == foregroundPid){
                foregroundPid = -1;
                return;
            }
        }
        if (kill(foregroundPid, SIGTSTP) == -1){
            // perror("Error sending SIGTSTP to foreground process");
            fprintf(stderr, RED"Failed to signal the foreground process\n"RESET);
        } 
        else{
            printf(YELLOW"[Stopped Process PID: %d]\n"RESET, foregroundPid);
            // Store the stopped process as a background process
            addProcess(globalProcessList,COMMAND, foregroundPid);
            Process* p = getProcessByPid(*globalProcessList, foregroundPid);
            if (p == NULL) {
                return;
            }
            p->status = STOPPED;

            // Call the background process handler directly for this specific PID
            backgroundProcessHandler(SIGCHLD);
        }
    } else {
        printf("\n");
        printPrompt(PROMPT);
        fflush(stdout);
    }
}


// Function to set up signal handlers
void bgForegroundHandler(int signum){
    if(foregroundPid != -1){
        if (kill(foregroundPid, SIGTSTP) == -1) {
            fprintf(stderr, RED"Failed to signal the foreground process\n"RESET);
        } 
        else{
            printf(YELLOW"[Stopped foreground process PID: %d]\n"RESET, foregroundPid);
            // Store the stopped process as a background process
            addProcess(globalProcessList,COMMAND, foregroundPid);
            Process* p = getProcessByPid(*globalProcessList, foregroundPid);
            if (p == NULL) {
                return;
            }
            p->status = STOPPED;

            // Call the background process handler directly for this specific PID
            backgroundProcessHandler(SIGCHLD);
        }
    } 
    else {
        printf("\n");
        printPrompt(PROMPT);
        fflush(stdout);
    }
}

void setupSignalForForeground(){
    struct sigaction sa;
    sa.sa_handler = &bgForegroundHandler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGTSTP, &sa, NULL);
}


void setupSignal() {
    struct sigaction sa;

    // Handle SIGCHLD for background process management
    sa.sa_handler = backgroundProcessHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        fprintf(stderr, RED"Error setting up SIGCHLD handler\n"RESET);
        exit(1);
    }


    // Handle Ctrl-Z
    sa.sa_handler = handleSigtstp;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGTSTP, &sa, NULL) == -1) {
        fprintf(stderr, RED"Error setting up SIGTSTP handler\n"RESET);
        exit(1);
    }
    // Handle Ctrl-C
    sa.sa_handler = handleSigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        fprintf(stderr, RED"Error setting up SIGINT handler\n"RESET);
        exit(1);
    }
}


