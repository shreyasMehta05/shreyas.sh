#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#ifndef SIGNALS_H
#define SIGNALS_H 1
// Function to send a signal to a process
void sendSignal(pid_t pid, int signal_number);

// Function to handle Ctrl-C (SIGINT)
void handleSigint(int signum);

// Function to handle background processes
 void backgroundProcessHandler(int signum);

// Function to handle Ctrl-Z (SIGTSTP)
void handleSigtstp(int signum);
void setupSignal();
void setupSignalForForeground();
#endif