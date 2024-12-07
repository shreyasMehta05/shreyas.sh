#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include"../display/display.h"
#include"../process/process.h"
#include"../interface/interface.h"
#ifndef PING_H
#define PING_H 1

void ping(pid_t pid, int signal,Prompt* prompt);

#endif