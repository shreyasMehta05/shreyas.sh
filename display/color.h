#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>
#include<errno.h>

#ifndef COLOR_H 
#define COLOR_H 1

#define RED "\x1b[31m"
#define GREEN "\x1b[32m" 
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"
#define BOLD "\x1b[1m"
#define UNDERLINE "\x1b[4m"
#define WHITE "\x1b[37m"
#define BLACK "\x1b[30m"
#define color const char
    
#endif