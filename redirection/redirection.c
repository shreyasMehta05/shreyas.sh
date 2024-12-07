#include "redirection.h"
void trimWhitespaces(char *str) {
    if(str==NULL){
        return;
    }

    char *start = str;
    while (isspace((unsigned char)*start)) start++;

    char *end = start + strlen(start) - 1;
    while(end > start && isspace((unsigned char)*end)) end--;

    *(end+1) = '\0';

    memmove(str, start, strlen(start) + 1);
}

char* makeAbsolutePath(char* path, Prompt* prompt) {
    if (path == NULL) return NULL;
    if (path[0] == '/') return path; // Already an absolute path

    char* absolutePath = (char*)malloc(4096*sizeof(char));
    if (absolutePath == NULL) {
        fprintf(stderr, RED"Error: Memory allocation failed\n"RESET);
        // perror("Error Occoured in file: redirection/redirection.c --> makeAbsolutePath()\n");
        return NULL;
    }

    if (path[0] == '~') {
        strcpy(absolutePath, prompt->directory->homeDirectory); // it is the absolute path of home directory
        if(absolutePath[strlen(absolutePath)-1]!='/'){
            strcat(absolutePath, "/");
        }
        strcat(absolutePath, path+1);
    }
    // Relative path
    else {
        strcpy(absolutePath, "./");
        strcat(absolutePath, path);
    }
    return absolutePath;
   
}
// Function to check and return input redirection file
char* getInputRedirectionFile(char *command, Prompt* prompt) {
    char *commandCopy = strdup(command);
    char *commandPtr = NULL;
    char *inputFile = NULL;

    if (strstr(commandCopy, "<")) {
        strtok_r(commandCopy, "<", &commandPtr); // Split command at '<'
        inputFile = strtok_r(NULL, " ", &commandPtr); // Get input file
        if (inputFile) {
            trimWhitespaces(inputFile); // Clean up the file name
            inputFile = strdup(inputFile); // Duplicate to avoid freeing commandCopy
        }
    }

    free(commandCopy); // Free the copy after use
    return inputFile;
}

// Function to check and return output redirection file, supports both > and >>
char* getOutputRedirectionFile(char *command, int *appendMode, Prompt* prompt) {
    char *commandCopy = strdup(command);
    char *commandPtr = NULL;
    char *outputFile = NULL;

    if (strstr(commandCopy, ">>")) {  // Check for append redirection
        *appendMode = 1;  // Enable append mode
        strtok_r(commandCopy, ">>", &commandPtr); // Split command at '>>'
        strtok_r(NULL, " ", &commandPtr); // Skip spaces after '>>'
        // printf("commandCopy: %s\n",commandPtr);
    } else if (strstr(commandCopy, ">")) {  // Check for overwrite redirection
        *appendMode = 0;  // Overwrite mode
        strtok_r(commandCopy, ">", &commandPtr); // Split command at '>'
    }
    else{
        free(commandCopy);
        return NULL;
    }

    outputFile = strtok_r(NULL, " ", &commandPtr); // Get output file
    if (outputFile) {
        trimWhitespaces(outputFile); // Clean up the file name
        outputFile = strdup(outputFile); // Duplicate to avoid freeing commandCopy
    }

    free(commandCopy); // Free the copy after use
    return outputFile;
}

// Function to handle input redirection
void handleInputRedirection(char *inputFile, int *originalStdin) {
    if (inputFile) {
        int fdInput = open(inputFile, O_RDONLY);
        if (fdInput < 0) {
            // perror(RED"Error opening input file"RESET);
            return;
        }
        *originalStdin = dup(STDIN_FILENO); // Save original stdin
        dup2(fdInput, STDIN_FILENO); // Redirect stdin to the input file
        close(fdInput);              // Close file descriptor after duplication
    }
}

// Function to handle output redirection with support for append or overwrite
void handleOutputRedirection(char *outputFile, int appendMode, int *originalStdout) {
    if (outputFile) {
        int fdOutput;
        if (appendMode) {
            fdOutput = open(outputFile, O_WRONLY | O_CREAT | O_APPEND, 0644); // Open file in append mode
        } else {
            fdOutput = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);  // Open file in overwrite mode
        }

        if (fdOutput < 0) {
            // perror("Error opening output file");
            return;
        }
        *originalStdout = dup(STDOUT_FILENO); // Save original stdout
        dup2(fdOutput, STDOUT_FILENO); // Redirect stdout to the output file
        close(fdOutput);               // Close file descriptor after duplication
    }
}

// Function to restore original stdin and stdout
void restoreRedirection(int originalStdin, int originalStdout) {
    if (originalStdin != -1) {
        dup2(originalStdin, STDIN_FILENO); // Restore original stdin
        close(originalStdin);              // Close saved descriptor
    }
    if (originalStdout != -1) {
        dup2(originalStdout, STDOUT_FILENO); // Restore original stdout
        close(originalStdout);               // Close saved descriptor
    }
}

// Main function to handle redirection
bool handleRedirection(char* command, Prompt* prompt, int *originalStdin, int *originalStdout) {
    //  originalStdin = -1;  // Initialize as -1 to check later if redirection occurred
    //  originalStdout = -1; // Initialize as -1 to check later if redirection occurred
    int appendMode = 0;      // Default is overwrite mode

    char *inputFile = getInputRedirectionFile(command, prompt);   // Get input file if exists
    char *outputFile = getOutputRedirectionFile(command, &appendMode, prompt); // Get output file if exists
    // printf("inputFile: %s\n",inputFile);
    // printf("outputFile: %s\n",outputFile);
    handleInputRedirection(inputFile, originalStdin);    // Handle input redirection
    handleOutputRedirection(outputFile, appendMode, originalStdout); // Handle output redirection

    // return false if input file  name is not valid
    if (inputFile && access(inputFile, F_OK) == -1) {
        fprintf(stderr, RED"Error: Input file '%s' does not exist\n"RESET, inputFile);
        return false;
    }
    // return false if output file name is not valid
    if (outputFile && access(outputFile, F_OK) == -1) {
        fprintf(stderr, RED"Error: Output file '%s' does not exist\n"RESET, outputFile);
        return false;
    }
    
    // Execute your command logic here (e.g., calling execvp)

    // Restore original stdin and stdout
    // restoreRedirection(originalStdin, originalStdout);

    // Free the allocated file names after use
    if (inputFile) free(inputFile);
    if (outputFile) free(outputFile);
    return true;
}

// Function to remove redirection symbols and their corresponding file arguments from the command
void removeRedirectionSymbols(char* command) {
    int i = 0;
    while (i < strlen(command)) {
        if (command[i] == '<' || command[i] == '>') {
            char redirection = command[i];
            command[i] = ' '; // Remove '<' or '>'
            i++;

            // Handle '>>' (append mode)
            if (redirection == '>' && command[i] == '>') {
                command[i] = ' '; // Remove second '>'
                i++;
            }

            // Skip spaces after redirection symbol
            while (i < strlen(command) && isspace(command[i])) {
                i++;
            }

            // Remove the next argument (the file name)
            while (i < strlen(command) && !isspace(command[i])) {
                command[i] = ' ';
                i++;
            }
        } else {
            i++;
        }
    }
    command[strlen(command)] = '\0';
    // printf("final command: %s\n",command);
}

char* getArgs(char*command,char* args[],bool includeCommand){
    char* arguments = malloc(1000*sizeof(char));
    // for the case of input redirection
    // scanf the input and add it to the arguments return this string to the calling function and use it for tokenisation
    char buffer[1000];
    arguments[0]='\0';
    if(includeCommand){

        strcat(arguments,command);
        strcat(arguments," ");
    }
    while(scanf("%s",buffer)!=EOF){
        strcat(arguments,buffer);
        strcat(arguments," ");
    }
    rewind(stdin);
    // printf("arguments: %s\n",arguments);
    return arguments;
}

void handlePipes(char* command, Prompt* prompt){
    int pipeFD[2];
    char* commandPtr;
    char* command1 = strtok_r(command,"|",&commandPtr);
    char* command2 = strtok_r(NULL,"|",&commandPtr);
    if(pipe(pipeFD)==-1){
        fprintf(stderr, RED"Error: Pipe creation failed\n"RESET);
        // perror("Error Occoured in file: command/command.c --> handlePipes()\n");
        exit(EXIT_FAILURE);
    }
    int pid = fork();
    if(pid<0){
        fprintf(stderr, RED"Error: Fork failed\n"RESET);
        // perror("Error Occoured in file: command/command.c --> handlePipes()\n");
        return;
    }
    else if(pid == 0){
        close(pipeFD[0]);
        dup2(pipeFD[1],STDOUT_FILENO);
        close(pipeFD[1]);
        handleRedirection(command1,prompt,NULL,NULL);
        exit(EXIT_SUCCESS);
    }
    else{
        wait(NULL);
        pid = fork();
        if(pid<0){
            fprintf(stderr, RED"Error: Fork failed\n"RESET);
            // perror("Error Occoured in file: command/command.c --> handlePipes()\n");
            return;
        }
        else if(pid == 0){
            close(pipeFD[1]);
            dup2(pipeFD[0],STDIN_FILENO);
            close(pipeFD[0]);
            handleRedirection(command2,prompt,NULL,NULL);
            exit(EXIT_SUCCESS);
        }
        else{
            close(pipeFD[0]);
            close(pipeFD[1]);
            wait(NULL);
        }
    }
}

