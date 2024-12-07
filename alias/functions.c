#include "functions.h"



Function *functionList = NULL;

// Function to add a new function to the list
void addFunction(const char *functionName, const char *functionBody) {
    Function *newFunction = malloc(sizeof(Function));
    if (newFunction == NULL) {
        perror("Error allocating memory for function");
        exit(EXIT_FAILURE);
    }
    // printf("adding function %s\n",functionName);
    strncpy(newFunction->functionName, functionName, MAX_FUNCTION_NAME - 1); // Copy the function name
    newFunction->functionName[MAX_FUNCTION_NAME - 1] = '\0'; // Null-terminate the function name
    strncpy(newFunction->functionBody, functionBody, MAX_FUNCTION_BODY - 1); // Copy the function body
    newFunction->functionBody[MAX_FUNCTION_BODY - 1] = '\0'; // Null-terminate the function body
    newFunction->next = functionList; // Add the new function to the start of the list
    functionList = newFunction; // Update the list head
}

// Load functions from the .myshrc file
void loadFunctions() {
    char* myshrcFile = ".myshrc";
    FILE *file = fopen(myshrcFile, "r");
    if (file == NULL) {
        perror("Error opening .myshrc file");
        return;
    }

    char line[1024];
    char functionName[MAX_FUNCTION_NAME];
    char functionBody[MAX_FUNCTION_BODY];
    int inFunction = 0;
    printf(CYAN"Loading functions from %s\n"RESET, myshrcFile);
    while (fgets(line, sizeof(line), file)) {
        // printf("%s",line);
        // Strip comments (ignore anything after #)
        char *commentPos = strchr(line, '#');
        if (commentPos != NULL) {
            *commentPos = '\0';  // remove the comment
        }

        removeLeadingWhitespace(line); // Remove leading whitespace
        char* trimmedLine = line;
        // Check for function start
        if (strncmp(trimmedLine, "function ", 9) == 0) {
            inFunction = 1;
            sscanf(trimmedLine + 9, "%s", functionName);  // Get the function name

            // Remove parentheses if they exist
            char *parenPos = strchr(functionName, '(');
            if (parenPos) {
                *parenPos = '\0';  // Null-terminate to remove the parentheses
            }
            functionBody[0] = '\0';  // Reset function body
        } 
        else if (inFunction && strstr(trimmedLine, "{") != NULL) {
            // Ignore the opening curly brace '{'
            continue;
        }
        else if (inFunction && strncmp(trimmedLine, "}", 1) == 0) {
            // Function ends at closing curly brace
            inFunction = 0;
            printf(GREEN"%s\n"RESET, functionName);
            addFunction(functionName, functionBody);
        } 
        else if (inFunction && strlen(trimmedLine) > 0) {
            // Append lines to function body if it's not empty
            strncat(functionBody, trimmedLine, sizeof(functionBody) - strlen(functionBody) - 1);
            strncat(functionBody, "\n", sizeof(functionBody) - strlen(functionBody) - 1);  // Add newline
        }
    }

    fclose(file);
}
// Execute a custom function if it matches
int executeAliasFunction(const char *command,Prompt* prompt) {
    char functionName[MAX_FUNCTION_NAME];
    char functionArgs[MAX_FUNCTION_BODY] = {0};
    char *argStart;

    // Extract function name
    sscanf(command, "%s", functionName);

    // Extract arguments if present
    argStart = strchr(command, ' ');
    if (argStart) {
        argStart++;  // Move past the space
        strcpy(functionArgs, argStart);
    }

    // Search for the function in the function list
    Function *function = functionList;
    while (function != NULL) {
        if (strcmp(function->functionName, functionName) == 0) {
            // Duplicate function body
            char *bodyCopy = strdup(function->functionBody);
            if (!bodyCopy) {
                perror("Error duplicating function body");
                return 0;
            }

            // Replace both $1 and "$1" with functionArgs (without adding quotes)
            char *newBody = malloc(MAX_FUNCTION_BODY);
            if (!newBody) {
                perror("Error allocating memory for function body");
                free(bodyCopy);
                return 0;
            }
            newBody[0] = '\0';  // Start with an empty string

            char *currentPos = bodyCopy;
            while (*currentPos) {
                // Check for $1 and "$1"
                char *argPos = strstr(currentPos, "$1");
                char *quotedArgPos = strstr(currentPos, "\"$1\"");
                
                if (argPos && (!quotedArgPos || argPos < quotedArgPos)) {
                    // Handle $1 without quotes
                    strncat(newBody, currentPos, argPos - currentPos);  // Copy part before $1
                    strcat(newBody, functionArgs);  // Insert functionArgs
                    currentPos = argPos + 2;  // Move past $1
                } else if (quotedArgPos) {
                    // Handle "$1"
                    strncat(newBody, currentPos, quotedArgPos - currentPos);  // Copy part before "$1"
                    strcat(newBody, functionArgs);  // Insert functionArgs
                    currentPos = quotedArgPos + 4;  // Move past "$1"
                } else {
                    // No more $1 or "$1", copy the rest
                    strcat(newBody, currentPos);
                    break;
                }
            }

            // Execute commands in the modified function body
            char *cmd = strtok(newBody, "\n");  // Split by newlines
            while (cmd) {
                // Trim whitespace from the command
                removeLeadingWhitespace(cmd);
                if (strlen(cmd) > 0) {
                    // processCommand(cmd, home);  // Execute the command
                    // printf("executing command: %s\n",cmd);
                    executeCommands(cmd,prompt);
                }
                cmd = strtok(NULL, "\n");  // Process next command
            }
            free(bodyCopy);
            free(newBody);
            return 1;  // Exit after executing the matched function
        }
        function = function->next;
    }
    return 0;
}
