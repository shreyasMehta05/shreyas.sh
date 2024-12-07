#include"ping.h"
#include"../process/process.h"
void ping(int pid, int signal_number,Prompt* prompt) {
    // Normalize signal number to be within the range of valid signals
    int sig = signal_number % 32;

    // Check if the PID is valid
    if (kill(pid, 0) != 0) {
        // PID does not exist or is not accessible
        fprintf(stderr, RED"No such process found\n"RESET);
        return;
    }
    Process* p = getProcessByPid((prompt->processList),pid);
    // Send the signal to the process
    if (kill(pid, sig) == 0) {
        if(p!=NULL){
            if(sig==SIGTSTP || sig==SIGSTOP || sig==SIGTTIN || sig==SIGTTOU){
                p->status = STOPPED;
            }
            else if(sig==SIGCONT){
                p->status = RUNNING;
            }
            // else if(sig==SIGKILL || sig==SIGINT|| sig==SIGQUIT|| sig==SIGTERM){
            //     // removeProcess(&(prompt->processList),pid);
            // }
            else{
                p->status = STOPPED;
            }
        }
        printf("%s[Sent signal %d to process with pid %d]%s\n",YELLOW, sig, pid,RESET);
    } 
    else {
        // perror("Failed to send signal");
        fprintf(stderr, RED"Error sending signal\n"RESET);
    }
}

