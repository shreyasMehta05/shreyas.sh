#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <signal.h>
#include "../display/color.h"
#include<stdbool.h>



// Global variable to store original terminal attributes
struct termios originalTermios;

// Function to restore terminal attributes
void restoreTerminalMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &originalTermios) == -1) {
        fprintf(stderr, RED"Failed to restore terminal attributes\n"RESET);
    }
}

// Function to enable raw mode for terminal input
void setRawMode() {
    if (tcgetattr(STDIN_FILENO, &originalTermios) == -1) {
        fprintf(stderr, RED"Failed to get terminal attributes\n"RESET);
    }
    atexit(restoreTerminalMode);

    struct termios raw = originalTermios;
    raw.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        fprintf(stderr, RED"Failed to set terminal attributes\n"RESET);
    }
}

void initNeonate() {
    // printf("Neonate initialized\n");
    setbuf(stdout, NULL); // Disable buffering on stdout
    setRawMode(); // Enable raw mode for terminal
}
// Function to execute the 'neoexec' functionality
void neonateHelper(int time) {
    initNeonate();

    pid_t childPid = fork(); // Create a new process

    if (childPid == 0) {
        // Child process
        while (true) {
            // Read the most recent process ID
            FILE *file = fopen("/proc/sys/kernel/ns_last_pid", "r");
            if (file == NULL) {
                fprintf(stderr, RED"No Recent Process ID Found\n"RESET);
                exit(EXIT_FAILURE);
            }
            char mostRecentPid[50];
            if (fgets(mostRecentPid, sizeof(mostRecentPid), file) != NULL) {
                printf(CYAN"%s"RESET, mostRecentPid);
            }
            sleep(time);
        }
    } else if (childPid > 0) {
        // Parent process
        char interruptChar;
        while (read(STDIN_FILENO, &interruptChar, 1) == 1 && (interruptChar != 'x' && interruptChar != 'X')) {
            // Wait for the 'x' character to be pressed
            continue;
        }
        // Kill the child process
        kill(childPid, SIGKILL);
    } else {
        // Fork failed
        fprintf(stderr, RED"Failed to create child process\n"RESET);
    }
    restoreTerminalMode(); // Restore terminal attributes
}

// Function to parse and execute the 'neonate' command
void neonate(int time) {
    if(time <= 0){
        FILE *file = fopen("/proc/sys/kernel/ns_last_pid", "r");
        if (file == NULL) {
            fprintf(stderr, RED"No Recent Process ID Found\n"RESET);
            exit(EXIT_FAILURE);
        }
        char mostRecentPid[50];
        if (fgets(mostRecentPid, sizeof(mostRecentPid), file) != NULL) {
            printf("%s", mostRecentPid);
        }
        fclose(file);
        return;
    }
    neonateHelper(time);
}
