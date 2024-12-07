#include"display.h"
#include<sys/utsname.h>
#include<stdlib.h>
#include<pwd.h>
#include<sys/types.h>
#include<unistd.h>

#ifndef SYSTEM_DISPLAY_H
#define SYSTEM_DISPLAY_H 1

#define BUFFER_TERMINAL_DISPLAY_PROMPT 100
#define BUFFER_TERMINAL_DISPLAY_DIR 1000

struct utsname* returnSystemInfo(); // return system information
struct passwd* getUserDetails(); // return user details
char* returnUserAndSysStr(color* COLOR); // return user and system string
char* getDirectoryName(); // return current directory name
void generateTheDirectoryPath(char* homeDirectory,char* directoryName); // generate the directory path and update the directory name

#endif