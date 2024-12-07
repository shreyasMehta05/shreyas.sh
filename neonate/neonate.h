#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <termios.h>
#include<stdbool.h>
#include <time.h>

#ifndef NEONATE_H
#define NEONATE_H 1

extern bool keepRunning;
int getMostRecentId();
void neonate(int time);
#endif