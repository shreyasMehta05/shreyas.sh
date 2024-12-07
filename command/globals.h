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
#include "../process/process.h"
#include <string.h>
#include "../interface/interface.h"
#ifndef GLOBALS_H
#define GLOBALS_H 1 

extern ProcessList** globalProcessList;  // Definition
extern char* COMMAND;                    // Definition
extern int foregroundPid;                // Definition
extern Prompt* PROMPT;           // Definition
extern int shellPid;
#endif