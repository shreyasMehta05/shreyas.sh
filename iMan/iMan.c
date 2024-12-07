#include "iMan.h"


// Function to remove everything before the first <html> tag in the response
void removeHeaderBeforeHtml(char *response) {
    char *htmlStart;

    // Find the first occurrence of the <html> tag
    htmlStart = strstr(response, "<html>");
    if (htmlStart != NULL) {
        // Print the content starting from the <html> tag
        removeHtmlTags(htmlStart);
        printf("%s", htmlStart);
    } else {
        // If <html> is not found, print an error message or handle it accordingly
        fprintf(stderr, RED"Failed to find <html> tag in the response.\n"RESET);
    }
}

void removeHtmlTags(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char* tagStart;
    char* tagEnd;
    const char *pattern = "<[^>]*>";

    // Compile the regular expression
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, RED"Could not compile regex\n"RESET);
        return;
    }

    // Process the input string
    while (regexec(&regex, str, 1, match, 0) == 0) {
        tagStart = str + match[0].rm_so;
        tagEnd = str + match[0].rm_eo;
        memmove(tagStart, tagEnd, strlen(tagEnd) + 1);
    }

    // Free the compiled regular expression
    regfree(&regex);
}
int isErrorResponse(const char *response) {
    return strstr(response, "No matches for") != NULL;
}
void fetchManPage(const char *command) {
    int sockfd;
    struct sockaddr_in server_addr; struct hostent *server;
    char buffer[BUFFER_SIZE]; char request[1024];
    int received;

    // Resolve hostname
    server = gethostbyname("man.he.net");
    if (server == NULL) {
        fprintf(stderr, RED"ERROR, no such host\n"RESET);
        // exit(0);
        return;
    }

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, RED"ERROR opening socket\n"RESET);
        // exit(1);
        return;
    }

    // Setup server address struct
    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);
    server_addr.sin_port = htons(80);

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, RED"ERROR connecting\n"RESET);
        // exit(1);
        return;
    }

    // Create GET request
    snprintf(request, sizeof(request),
             "GET /?topic=%s&section=all HTTP/1.0\r\n"
             "Host: man.he.net\r\n"
             "Connection: close\r\n\r\n", command);

    // Send request
    if (send(sockfd, request, strlen(request), 0) < 0) {
        fprintf(stderr, RED"ERROR sending request\n"RESET);
        // exit(1);
        return;
    }
    bool notFound=false;
    // Receive response
    received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (received < 0) {
        fprintf(stderr, RED"ERROR receiving response\n"RESET);
        // exit(1);
        return;
    }
    buffer[received] = '\0'; // Null-terminate the response
    removeHeaderBeforeHtml(buffer);
    if(isErrorResponse(buffer)) {
        notFound=true;
    }
    while ((received = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[received] = '\0'; // Null-terminate the response
        if(isErrorResponse(buffer)) {
            notFound=true;
        }
        // Remove HTML tags from the remaining body content
        removeHtmlTags(buffer);
        // Print remaining body content as it arrives
        printf("%s", buffer);
    }
    
    if (received < 0) {
        fprintf(stderr, RED"ERROR receiving response\n"RESET);
        // exit(1);
        return;
    }
    if(notFound){
        fprintf(stderr, RED"Error: No matches for '%s'\n"RESET, command);
    }

    // Close socket
    close(sockfd);

}
void iMan(char* command){
    fetchManPage(command);
}