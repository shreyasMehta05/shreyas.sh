#include"alias.h"


Alias* aliasList = NULL;
// Function to add an alias to the alias list
void addAlias(char* aliasName,char* command){
    Alias* newAlias = (Alias*)malloc(sizeof(Alias));
    newAlias->aliasName = (char*)malloc(strlen(aliasName)+1);
    strcpy(newAlias->aliasName,aliasName);
    newAlias->command = (char*)malloc(strlen(command)+1);
    strcpy(newAlias->command,command);
    newAlias->next = NULL;
    newAlias->length = strlen(aliasName);
    if(aliasList == NULL){
        aliasList = newAlias;
    }
    else{
        Alias* temp = aliasList;
        while(temp->next!=NULL){
            temp = temp->next;
        }
        temp->next = newAlias;
    }

}
// Function to remove an alias from the alias list
void removeAlias(char* aliasName){
    if(aliasList == NULL){
        return;
    }
    Alias* temp = aliasList;
    if(strcmp(aliasList->aliasName,aliasName)==0){
        aliasList = aliasList->next;
        free(temp->aliasName);
        free(temp->command);
        free(temp);
        return;
    }
    while(temp->next!=NULL){
        if(strcmp(temp->next->aliasName,aliasName)==0){
            Alias* toDelete = temp->next;
            temp->next = temp->next->next;
            free(toDelete->aliasName);
            free(toDelete->command);
            free(toDelete);
            return;
        }
        temp = temp->next;
    }
}
// Function to list all the aliases
void listAliases(){
    if(aliasList == NULL){
        printf(CYAN"No aliases found\n"RESET);
        return;
    }
    printf(CYAN"List of aliases:\n"RESET);
    Alias* temp = aliasList;
    while(temp!=NULL){
        printf(GREEN"%s -> %s\n%s",temp->aliasName,temp->command,RESET);
        temp = temp->next;
    }
}
// Function to execute an alias
void executeAlias(char* aliasName,Prompt* prompt){
}
// Function to check if an alias exists
bool isAlias(char* aliasName){
    if(aliasList == NULL){
        return false;
    }
    Alias* temp = aliasList;
    while(temp!=NULL){
        if(strcmp(temp->aliasName,aliasName)==0){
            return true;
        }
        temp = temp->next;
    }
    return false;
}
// Function to get command for the aliasName
char* getCommand(char* aliasName){
    if(aliasList == NULL){
        return NULL;
    }
    Alias* temp = aliasList;
    while(temp!=NULL){
        if(strcmp(temp->aliasName,aliasName)==0){
            return temp->command;
        }
        temp = temp->next;
    }
    return NULL;
}
// Function to free the list
void freeAliasList(){
    Alias* temp = aliasList;
    while(temp!=NULL){
        Alias* toDelete = temp;
        temp = temp->next;
        free(toDelete->aliasName);
        free(toDelete->command);
        free(toDelete);
    }
    aliasList = NULL;
}


// Function to create and populate the alias list from .myshrc
void createAliasList() {

    FILE *file = fopen(".myshrc", "r");
    if (file == NULL) {
        return;
    }
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // my assumption is that the line will be in the format  aliasName='command'
        // so I will split the line by '='
        removeLeadingWhitespace(line);
        if(line[0] == '\0') {
            continue;
        }
        // now we need to remove the comments so we can split by '#'
        char* aliasPtr;
        char* token = strtok_r(line,"#",&aliasPtr); // this will remove the comments
        aliasPtr = NULL;
        if(strncmp(token,"function",8)==0){
            continue;
        }
        
        char* aliasName = strtok_r(token,"=",&aliasPtr);
        removeLeadingWhitespace(aliasName);
        char* command = strtok_r(NULL,"=",&aliasPtr);
        removeLeadingWhitespace(command);
        if(aliasName == NULL || command == NULL) {
            continue;
        }
        if(command[strlen(command)-1] == '\n') {
            command[strlen(command)-1] = '\0';
        }

        addAlias(aliasName, command);
    }
    fclose(file);
}

// Function to remove leading whitespace from a string
void removeLeadingWhitespace(char *str) {
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

// Function to replace aliases in a string with their corresponding commands
char *replaceAliasesInString(char *input) {
    if (input == NULL) {
        fprintf(stderr, "Error: input string is NULL.\n");
        return NULL;
    }

    // Start with a copy of the original input
    char *result = strdup(input);
    if (result == NULL) {
        // perror("Error duplicating input string");
        fprintf(stderr, "Error duplicating input string.\n");
        return NULL;
    }

    Alias* temp = aliasList;
    while (temp != NULL) {
        char *pos;
        // int len = strlen(temp->aliasName);
        while ( (pos = strstr(result, temp->aliasName)) != NULL ) {
            // pos now points to the first occurrence of the alias in the result string
            

            // Calculate lengths of the strings
            size_t lenBefore = pos - result;
            size_t lenKey = strlen(temp->aliasName);
            size_t lenValue = strlen(temp->command);
            size_t lenAfter = strlen(pos + lenKey);

            // Allocate a new string with enough space for replacement
            char *newResult = malloc(lenBefore + lenValue + lenAfter + 1);
            if (newResult == NULL) {
                // perror("Error allocating memory for replacement");
                fprintf(stderr, "Error allocating memory for replacement.\n");
                free(result);
                return NULL;
            }

            // Construct the new string
            strncpy(newResult, result, lenBefore);          // Copy the part before the alias
            strcpy(newResult + lenBefore, temp->command);   // Replace alias with the command
            strcpy(newResult + lenBefore + lenValue, pos + lenKey); // Copy the part after the alias

            free(result);
            result = newResult;
        }
        temp = temp->next;
    }
    
    input = strdup(result);
    free(result);
    return input;
}
