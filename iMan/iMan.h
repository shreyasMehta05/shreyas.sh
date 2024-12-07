#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <regex.h>
#include <stdbool.h>
#include"../display/color.h"

#ifndef IMAN_H
#define IMAN_H 1



#define BUFFER_SIZE 4096

// Function to remove HTML tags from a string
void removeHtmlTags(char *str);

// Function to check if the response contains an error message
int isErrorResponse(const char *response);

void fetchManPage(const char *command);

void iMan(char* command);

#endif
