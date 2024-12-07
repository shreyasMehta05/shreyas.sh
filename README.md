# **shreyas.sh** `💻`

![Waketime](https://img.shields.io/badge/Waketime-105%20hrs%2042%20mins-blueviolet?style=flat&labelColor=black&logo=clock&logoColor=white)


## *Project Title:*  ***A shell for Unix-based OSs, written in C*** `🐚`


### Description:
- *This project is a simple shell implementation for Unix-based operating systems, written in C. It was developed as part of the Operating Systems and Networks course at IIIT Hyderabad.*



### *Author: Shreyas Mehta (2023101059) IIIT-H*
### INDEX: `📚`
1. [Project Description](#project-description)
2. [File Structure](#file-structure)
3. [Build Instructions](#build-instructions)
4. [File Description](#file-description)
5. [Execution Flow](#execution-flow)
6. [Commands Supported](#commands-supported)
7. [Assumptions](#assumptions)
7. [References](#references)



#### FILE STRUCTURE: `📁`
*The project is organized as follows:*
```
.
├── Makefile 
├── README.md 
├── alias
│   ├── alias.c
│   ├── alias.h
│   ├── functions.c
│   └── functions.h
├── command 
│   ├── command.c 
│   ├── command.h 
│   ├── globals.c 
|   ├── globals.h
|   ├── signals.c
│   └── signals.h
├── display 
│   ├── color.h 
│   ├── display.c 
│   ├── display.h 
│   ├── systemDisplay.c 
│   └── systemDisplay.h 
├── hop 
│   ├── hop.c 
│   └── hop.h 
├── iMan
│   ├── iMan.c
│   └── iMan.h
├── interface 
│   ├── interface.c 
│   └── interface.h 
├── log 
│   ├── user.log 
│   ├── log.c 
│   └── log.h 
├── main.c
├── neonate
│   ├── neonate.c
│   └── neonate.h
├── ping
│   ├── ping.c
│   └── ping.h
├── process
│   ├── process.c
│   └── process.h
├── proclore 
│   ├── proclore.c 
│   └── proclore.h 
├── redirection
│   ├── redirection.c
│   └── redirection.h
├── reveal
│   ├── reveal.c
│   └── reveal.h
|── image
|   ├── Subfolders containing images (prompts)
├── seek
|   ├── seek.c 
|   └── seek.h 
├── .myshrc
|── Makefile
└── README.md
```

- **main.c**: The main entry point for the program.
- **command**: Contains the logic for command execution.
  - `command.c`: Implementation file for command execution.
  - `command.h`: Header file abstracting command execution.
- **display**: Handles display-related functions.
  - `display.c`: Implementation file for display functions.
  - `display.h`: Header file for display functions.
  - `color.h`: Header file defining color codes for terminal output.
  - `systemDisplay.c`: System display-related functionalities (prompt related).
  - `systemDisplay.h`: Header file for system display functions.
- **Interface**: Manages the user interface.
  - `Interface.c`: Implementation file for the user interface (user prompt queries).
  - `Interface.h`: Header file for the user interface (user prompt queries).
- **hop**: Handles directory navigation.
  - `hop.c`: Implementation file for directory hopping (to a directory).
  - `hop.h`: Header file for directory hopping.
- **log**: Manages logging functionalities.
  - `log.c`: Implementation file for logging.
  - `log.h`: Header file for logging.
  - `actual.log`: Log file storing runtime information.
- **proclore**: Processes and system lore.
  - `proclore.c`: Implementation file for process handling.
  - `proclore.h`: Header file for process handling.
- **redirection**: Handles redirection functionalities.
  - `redirection.c`: Implementation file for redirection functionalities.
  - `redirection.h`: Header file for redirection functionalities.
- **reveal**: Functions related to revealing information.
  - `reveal.c`: Implementation file for reveal functionalities.
  - `reveal.h`: Header file for reveal functionalities.
- **seek**: Search functionalities within the application.
  - `seek.c`: Implementation file for search functions.
  - `seek.h`: Header file for search functions.
- **alias**: Handles alias functionalities.
    - `alias.c`: Implementation file for alias functionalities.
    - `alias.h`: Header file for alias functionalities.
    - `functions.c`: Implementation file for alias functions.
    - `functions.h`: Header file for alias functions.
- **iMan**: Handles manual functionalities.
    - `iMan.c`: Implementation file for manual functionalities.
    - `iMan.h`: Header file for manual functionalities.
- **neonate**: Handles neonate functionalities.
    - `neonate.c`: Implementation file for neonate functionalities.
    - `neonate.h`: Header file for neonate functionalities.
- **ping**: Handles ping functionalities.
    - `ping.c`: Implementation file for ping functionalities.
    - `ping.h`: Header file for ping functionalities.
- **process**: Handles process functionalities.
    - `process.c`: Implementation file for process management.
    - `process.h`: Header file for process management.
- **.myshrc**: Contains the shell configuration settings.
- **globals**: Contains global variables and functions.
    - `globals.c`: Implementation file for global variables and functions.
    - `globals.h`: Header file for global variables and functions.
- **signals**: Handles signal-related functionalities.
    - `signals.c`: Implementation file for signal-related functionalities.
    - `signals.h`: Header file for signal-related functionalities.
- **`.myshrc`**: Contains the shell configuration settings.
- **`Makefile`**: Used to build the project.
- **`README.md`**: Documentation file for the project.

### Build Instructions:
- *To build the project, run the following command:*
  ```bash
  make
  ```
- *To run the project, execute the following command:*
  ```bash
  ./a.out
  ```
- *To clean the project, run the following command:*
  ```bash
    make clean
    ```



### File Description: `📝`

- **main.c**: The main entry point for the program.
    - **Contains the `main()` function that initializes the shell and runs the shell loop.**
    - The shell loop reads the user input, processes the input, and executes the commands.
    - The loop continues until the user exits the shell.
    - **Functions Used:**
      | **Function Name**                    | **Description**                                                                 |
      |--------------------------------------|---------------------------------------------------------------------------------|
      | `int main();`                        | The main function that initializes the shell and runs the shell loop.            |
      | `void promptInit(Prompt* prompt);`   | Helps print the prompt in each iteration of the shell loop.                      |
      | `char* inputCommand(Prompt* prompt);`| Reads the command input from the user.                                           |
      | `void executeCommands(char* cmd, Prompt* prompt);`| Processes and executes the given command.                              |
      | `Prompt* InitialisePrompt();`        | Initializes and sets up the prompt with necessary configurations.                |
      | `void setupSignal();`                | Sets up signal handlers to handle interruptions like Ctrl+C (SIGINT).            |
      | `void loadFunctions();`              | Loads available custom functions into memory.                                    |
      | `void createAliasList();`            | Initializes the alias system for command shortcuts.                              |
      | `void listAliases();`                | Displays the list of all defined aliases in the shell.                           |
      | `void freeAliasList();`              | Cleans up and frees memory allocated for aliases at the end of the shell's run.  |

    - **Main Flow:**
        ```c
        int main() {
            // Load custom shell functions and aliases
            loadFunctions();
            createAliasList();
            listAliases();

            // Initialize shell prompt
            Prompt* promptTerminal = InitialisePrompt();
            globalPrompt = promptTerminal;
            promptTerminal->command2sec = "";
            PROMPT = promptTerminal;

            // Store current shell's PID
            shellPid = getpid();
            setupSignal();  // Setup signal handling

            // Shell loop
            while (1) {
                // Read user input and process commands
                char* command = inputCommand(promptTerminal);
                executeCommands(command, promptTerminal);

                // Reprint the prompt for the next command
                promptInit(promptTerminal);
                promptTerminal->command2sec = "";
            }

            // Clean up
            freeAliasList();
            return 0;
        }
        ```


- **Makefile**: Used to build the project.
    - *Contains the build instructions for the project.*
    - *The Makefile compiles the project and generates the executable file `main`.*
    - *The Makefile also contains the clean instructions to remove the generated files.*
- **README.md**: Documentation file for the project.
    - *Contains the project description, file structure, build instructions, and file descriptions.*
- **command**: Contains the logic for command execution.
    - `command.c`: Implementation file for command execution.
        - *Contains the implementation of the command execution logic.*
        - *functions Used:*
            ### File: `command.c`
        ### Functions Table

        | **Function Name**               | **Description**                                                                                              | **Error Handling**                                                                                       | **Memory Management**                                                                                                               |
        |---------------------------------|--------------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------|
        | `trimWhitespace(char *str)`      | Removes leading and trailing whitespace from the string `str`.                                              | No explicit error handling.                                                                            | Allocates memory only for the input string `str`. Does not allocate new memory but modifies the input string.                      |
        | `removeLeadingWhitespaces(char *str)` | Calls `trimWhitespace` to remove leading whitespace from `str`.                                              | No explicit error handling.                                                                            | No additional memory allocation. Uses `trimWhitespace` which operates on the input string `str`.                                  |
        | `handleCtrlD(Prompt* prompt, bool print)` | Handles Ctrl+D input by cleaning up background processes and exiting the shell.                              | Prints progress and error messages if cleaning up processes or freeing aliases fails.                  | Frees aliases list using `freeAliasList`. Calls `exit` to terminate the program, handling no dynamic memory allocation within.    |
        | `inputCommand(Prompt* prompt)`        | Reads a command from the user input.                                                                         | Prints error message and exits if memory allocation fails.                                             | Allocates memory for the command using `malloc`, should be freed by the caller.                                                   |
        | `hopHelper(char* token, char* commandPtr, Prompt* prompt)` | Processes tokens for the `hop` command and handles them appropriately.                                        | No explicit error handling.                                                                            | Allocates memory for `actualCommand`, should be freed by the caller. Modifies the input string `token`.                           |
        | `revealHelper(char* token, char* commandPtr, Prompt* prompt)` | Processes tokens for the `reveal` command and handles options and paths.                                       | Prints error messages for invalid arguments.                                                            | Allocates memory for `actualCommand`, should be freed by the caller.                                                               |
        | `logHelper(char* token, char* commandPtr, Prompt* prompt)`    | Processes tokens for the `log` command and handles arguments like `purge` or `execute`.                        | Prints error messages for invalid arguments.                                                            | No additional memory allocation. Uses `strdup` for string manipulation and ensures that `command` from `logExecute` is freed.    |
        | `backgroundProcess(char* command, Prompt* prompt)`  | Executes a command in the background and handles process creation and management.                            | Prints error messages for process creation failures.                                                    | Allocates memory for `args` and `commandPtr`. Ensures that memory for `args[i]` is freed in the child process.                     |
        | `procloreHelper(char* token, char* commandPtr, Prompt* prompt)` | Processes tokens for the `proclore` command and handles process IDs.                                           | Prints error messages for invalid arguments.                                                            | Allocates memory for process ID handling and uses `atoi` for conversion.                                                            |
        | `seekHelper(char* token, char* commandPtr, Prompt* prompt)` | Processes tokens for the `seek` command and handles search paths and flags.                                   | Prints error messages for invalid arguments.                                                            | No explicit memory management. Uses `strtok_r` to parse tokens from the command string.                                           |
        | `foregroundProcess(char* command, Prompt* prompt)` | Executes a command in the foreground, handling process control, redirection, and command execution.           | Prints error messages for invalid commands, failed process creation, and signal handling issues.       | Allocates memory for command manipulation (e.g., `strdup` for `originalCommand`). Frees allocated memory and restores redirection. |
        | `executeCommand(char* command, Prompt* prompt)` | Parses and executes commands based on their type (foreground, background, or piped). Handles command separation and execution in the foreground or background. | No explicit error handling for command type determination. Prints error messages if `backgroundProcess` or `foregroundProcess` fails. | Allocates memory for temporary command manipulation. Frees memory for tokenized commands and handles command processing.         |
        | `tokenise(char* command, Prompt* prompt)` | Splits the input command string into individual commands based on semicolons and executes each command.       | No explicit error handling for command tokenization.                                                   | No additional memory allocation beyond command tokenization. Uses `strtok_r` for splitting commands.                               |
        | `executePipedCommands(char* command, Prompt* prompt)` | Handles commands separated by pipes, setting up inter-process communication via pipes and executing the commands in sequence. | Prints error messages for invalid pipe usage or pipe creation failures.                                | Allocates memory for command tokens and pipe file descriptors. Frees allocated memory and closes pipe file descriptors.           |

    - `command.h`: Header file abstracting command execution.
        - *Contains the function declarations for command execution.*
        - *functions Abstracted:*
            | **Function Name**                                         | **Description**  
            |----------------------------------                         |---------------------------------------------------------------------------------|
            | `void removeLeadingWhitespaces(char* str);`               | Removes leading and trailing whitespace from the given string.                      |
            | `char* inputCommand();`                                   | Takes the input command from the user.                                              |
            | `bool isSpace(char c);`                                   | Checks if the given character is a space.                                            |
            | `void tokenise(char* command, Prompt* prompt);`           | Tokenizes multiple commands and differentiates between background and foreground commands. |
            | `bool executeCommands(char* command, Prompt* prompt);`    | Directs the command to either the foreground or background for execution.             |
            | `void executeCommand(char* command, Prompt* prompt);`     | Executes a single command.                                                           |
            | `void foregroundProcess(char* command, Prompt* prompt);`  | Executes the command in the foreground.                                              |
            | `void backgroundProcess(char* command, Prompt* prompt);`  | Executes the command in the background.                                              |

        - *Macro Definitions:*
            | **Macro Definition**         | **Description**                           |
            |-----------------------------  |-------------------------------------------|
            | `COMMAND_H`                   | Header guard for the header file.         |
            | `BUFFER_TERMINAL_COMMAND`      | Maximum size of the command.              |
            | `BUFFER_TERMINAL_MAX_ARGS`     | Maximum number of arguments in the command.|

- **display**: Handles display-related functions.
    - `color.h`: Header file defining color codes for terminal output.
        - *Contains the color codes for terminal output.*
        - *Macro Definations:*
            | **Macro Definition** | **Description** |
            |----------------------|-----------------|
            | `COLOR_H`            | Header guard for the header file. |
            | `RED`               | Red color code. "x1b[31m"                   |
            | `GREEN`             | Green color code. "x1b[32m"                 |
            | `YELLOW`            | Yellow color code. "x1b[33m"                |
            | `BLUE`              | Blue color code. "x1b[34m"                  |
            | `MAGENTA`           | Magenta color code. "x1b[35m"               |
            | `CYAN`              | Cyan color code. "x1b[36m"                  |
            | `WHITE`             | White color code. "x1b[37m"                 |
            | `RESET`             | Reset color code. "x1b[0m"                  |
            | `BOLD`              | Bold color code. "x1b[1m"                   |
            | `color`             | const char            |
    - `display.c`: Implementation file for display functions.
    
        | **Function Name** | **Description** |
        |-------------------|-----------------|
        | `void printfColor(color *COLOR,const char* str,bool bold)` | Prints the given string with the specified color and boldness. |
    - `diplay.h`
        - *Contains the function declarations for display functions.*
        - *functions Abstracted:*
            ### File: `display.h`
            | **Function Name** | **Description** |
            |-------------------|-----------------|
            | `void printfColor(color *COLOR,const char* str,bool bold)` | Prints the given string with the specified color and boldness. |
        - *Macro Definations:*
            | **Macro Definition** | **Description** |
            |----------------------|-----------------|
            | `DISPLAY_H`          | Header guard for the header file. |
            
    - `systemDisplay.c`: System display-related functionalities (prompt related).
        - *Contains the implementation of system display-related functionalities.*
        - *functions Used:*
            ### File: `systemDisplay.c`
            | **Function Name**                                   | **Description**                                                                                  | **Error Handling**                                           | **Memory Management**                                          |
            |-----------------------------------------------------|--------------------------------------------------------------------------------------------------|--------------------------------------------------------------|---------------------------------------------------------------|
            | `struct utsname* returnSystemInfo();`               | Retrieves system information using `uname()` and returns a pointer to the `utsname` structure.   | Exits the program if `uname()` fails.                       | Allocates memory for `utsname`. Caller must free it after use.|
            | `struct passwd* getUserDetails();`                  | Fetches the current user's information from the system's password database using `getpwuid()`.   | Exits the program if `getpwuid()` fails.                    | Allocates a pointer to `passwd` structure.                   |
            | `char* returnUserAndSysStr(color* COLOR);`          | Constructs a formatted string containing the username and system name, colored as per the input color. | Exits the program if `snprintf()` fails due to buffer overflow. | Allocates memory for the output string. Caller must free it after use. |
            | `char* getDirectoryName();`                         | Retrieves the current working directory name using `getcwd()` and returns it as a string.         | Exits the program if `getcwd()` fails.                      | Allocates memory for the directory name. Caller must free it after use.|
            | `void generateTheDirectoryPath(char* homeDirectory, char* directoryName);` | Modifies the directory name string to replace the home directory path with `~` if applicable. | None; function does not exit the program.                   | Allocates new memory if needed for the directory name. Caller must manage it. |
    - `systemDisplay.h`: Header file for system display functions.
        - *Contains the function declarations for system display functions.*
        - *functions Abstracted:*
            ### File: `systemDisplay.h`
            | **Function Name**                                   | **Description**                                                                                  |
            |-----------------------------------------------------|--------------------------------------------------------------------------------------------------|
            | `struct utsname* returnSystemInfo();`               | Retrieves system information using `uname()` and returns a pointer to the `utsname` structure.   |
            | `struct passwd* getUserDetails();`                  | Fetches the current user's information from the system's password database using `getpwuid()`.   |
            | `char* returnUserAndSysStr(color* COLOR);`          | Constructs a formatted string containing the username and system name, colored as per the input color. |
            | `char* getDirectoryName();`                         | Retrieves the current working directory name using `getcwd()` and returns it as a string.         |
            | `void generateTheDirectoryPath(char* homeDirectory, char* directoryName);` | Modifies the directory name string to replace the home directory path with `~` if applicable. |
        - *Macro Definations:*
            ### File: `systemDisplay.h`
            | **Macro Name**                          | **Definition** | **Description**                                               |
            |-----------------------------------------|----------------|---------------------------------------------------------------|
            | `BUFFER_TERMINAL_DISPLAY_PROMPT`        | `100`          | Buffer size for terminal display prompt.                     |
            | `BUFFER_TERMINAL_DISPLAY_DIR`           | `1000`         | Buffer size for storing the current directory name.          |
            | `SYSTEM_DISPLAY_H`                      || Header guard for the header file.                            |
- **Interface**: Manages the user interface.
    - `Interface.c`: Implementation file for the user interface (user prompt queries).
        - *Contains the implementation of the user interface functions.*
        - *functions Used:*
            ### File: `Interface.c`
            | **Function Name**    | **Description**                                                                                                    | **Parameters**                                          | **Returns**   |
            |----------------------|--------------------------------------------------------------------------------------------------------------------|---------------------------------------------------------|---------------|
            | `InitialisePrompt`   | Initializes a `Prompt` structure by allocating memory and setting its fields.                                      | None                                                    | `Prompt*`     |
            | `printPrompt`        | Prints the prompt to the terminal, including user and system information, current directory, and additional details. | `Prompt* prompt`                                       | `void`        |
            | `updatePrompt`       | Updates the `Prompt` structure with new directory information and refreshes the prompt string.                      | `Prompt* prompt`                                       | `void`        |

    - `Interface.h`: Header file for the user interface (user prompt queries).
        ### File: `interface.h`
        | **Macro Name**     | **Definition** | **Description**  |
        |--------------------|-----------------|------------------|
        | `INTERFACE_H`      | `1`             | Prevents multiple inclusions of the header file (`interface.h`). |
        ### File: `interface.h`
        | **Structure** | **Field**               | **Type**   | **Description**                                              | **Memory Management**                                               |
        |---------------|-------------------------|------------|--------------------------------------------------------------|---------------------------------------------------------------------|
        | `Directory`   | `directoryName`         | `char*`    | Pointer to the name of the directory.                       | Should be allocated and freed by the code managing the `Directory` structure. |
        |               | `homeDirectory`         | `char*`    | Pointer to the home directory path.                         | Should be allocated and freed by the code managing the `Directory` structure. |
        |               | `lastWorkingDirectory`  | `char*`    | Pointer to the last working directory path.                 | Should be allocated and freed by the code managing the `Directory` structure. |
        | `Prompt`      | `directory`             | `Directory*` | Pointer to a `Directory` structure.                         | `Directory` structure should be allocated and freed by the code managing the `Prompt` structure. |
        |               | `command2sec`           | `char*`    | Pointer to a command string.                                | Should be allocated and freed by the code managing the `Prompt` structure. |
        |               | `prompt`                | `char*`    | Pointer to the prompt string.                               | Should be allocated and freed by the code managing the `Prompt` structure. |

- **hop**: Handles directory navigation.
    - `hop.c`: Implementation file for directory hopping (to a directory).
        - *Contains the implementation of directory hopping functions.*
        - *functions Used:*
            ### File: `hop.c`
            | **Function Name** | **Description** | **Error Handling** | **Memory Management** |
            |--------------------|-----------------|---------------------|------------------------|
            | `hop`              | Changes the current working directory based on the given path. If the path is `"~"`, it changes to the home directory. If the path is `"-"`, it changes to the last working directory. | - Checks if the `path` is `NULL` or invalid and prints an error message. <br> - If `chdir(path)` fails, prints an error message. | - Allocates memory for `temp` to store the concatenated path if the path starts with `"~"`. <br> - Frees `temp` after use to avoid memory leaks. |
    - `hop.h`: Header file for directory hopping.
        - *Contains the function declarations for directory hopping.*
        - *functions Abstracted:*
            | **Function Name** | **Description**                                                                                                    | **Parameters**                                          | **Returns**   |
            |-------------------|--------------------------------------------------------------------------------------------------------------------|---------------------------------------------------------|---------------|
            | `void hop(char* directory, Prompt* prompt);` | Changes the current working directory to the specified directory and updates the prompt. | `char* directory`, `Prompt* prompt` | `void`        |
           
        - *Macro Definations:*
            ### File: `hop.h`
            | **Macro Name** | **Definition** | **Description**  |
            |----------------|-----------------|------------------|
            | `HOP_H`        | `1`             | Prevents multiple inclusions of the header file (`hop.h`). |
- **log**: Manages logging functionalities.
    - `log.c`: Implementation file for logging.
        - *Contains the implementation of logging functions.*
        - *functions Used:*
            ### File: `log.c`
            | **Function Name**                 | **Description**                                                                                                             | **Error Handling**                                                                                                         | **Memory Management**                                                                                                      |
            |-----------------------------------|-----------------------------------------------------------------------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------|
            | `pathDynamicFunction`             | Constructs and returns the path to `user.log` based on the prompt's home directory.                                          | - Checks for allocation failure and exits with an error message if `malloc` fails.                                         | - Allocates memory for `path`. <br> - Caller is responsible for freeing `path`.                                              |
            | `readLastLine`                    | Reads the last line of a file and compares it with the given command.                                                       | - Checks if the file is `NULL` and prints an error message. <br> - Handles memory allocation failure and prints an error message. | - Allocates memory for `lastCommand`. <br> - Frees `lastCommand` after use.                                                 |
            | `pathDynamicFunctionFortempLog`   | Constructs and returns the path to `temp.log` based on the prompt's home directory.                                           | - Checks for allocation failure and exits with an error message if `malloc` fails.                                         | - Allocates memory for `path`. <br> - Caller is responsible for freeing `path`.                                              |
            | `copyFromTempToUser`              | Copies contents from `temp.log` to `user.log`.                                                                            | - Checks if file allocation fails and prints an error message. <br> - Handles memory allocation failure for `bufferArray`. | - Allocates memory for `bufferArray`. <br> - Frees `bufferArray` and `path` after use.                                       |
            | `readLast15Lines`                 | Reads the last 15 lines of a file and updates `user.log` with those lines.                                                   | - Checks if the file is `NULL` and prints an error message. <br> - Handles memory allocation failure and prints an error message. | - Allocates memory for `buffer`. <br> - Frees `buffer` after use.                                                             |
            | `appendAtFirst`                   | Appends a command at the beginning of `user.log` if it does not already exist and updates `user.log`.                        | - Checks if the file is `NULL` and prints an error message. <br> - Calls `readLastLine` and `readLast15Lines` which handle their own errors. | - No direct memory allocation in this function, but it relies on functions that allocate memory.                           |
            | `logCommandUser`                  | Logs a command into `user.log` by appending it.                                                                            | - Checks if the file is `NULL` and prints an error message. <br> - Calls `appendAtFirst` which handles its own errors. | - Calls `pathDynamicFunction` which allocates memory; frees `pathTouserLog` after use.                                      |
            | `numberOflines`                   | Counts the number of lines in a file.                                                                                       | - Checks if the file is `NULL` and prints an error message.                                                                 | - No direct memory allocation in this function.                                                                             |
            | `logExecute`                      | Reads and returns a specific number of lines from `user.log` based on the given number.                                    | - Checks if the number of lines is invalid and prints an error message. <br> - Checks if the file is `NULL` and prints an error message. <br> - Handles memory allocation failure and prints an error message. | - Allocates memory for `buffer`. <br> - Frees `buffer` after use.                                                             |
            | `logPurge`                        | Clears the contents of `user.log`.                                                                                           | - Checks if the file is `NULL` and prints an error message.                                                                 | - No direct memory allocation in this function.                                                                             |
            | `logDisplay`                      | Displays the contents of `user.log` to the standard output.                                                                  | - Checks if the file is `NULL` and prints an error message.                                                                 | - No direct memory allocation in this function.                                                                             |
    - `log.h`: Header file for logging.
        ### Table for Macros
        | **Macro Name**                        | **Description**                                       | **Value** |
        |---------------------------------------|-------------------------------------------------------|-----------|
        | `LOG_H`                               | Header file guard to prevent multiple inclusions.    | `1`       |
        | `BUFFER_MAX_PATH_TO_LOG_FILES`        | Maximum buffer size for paths to log files.          | `100`     |
        | `MAX_LINES`                           | Maximum number of lines to consider (e.g., for display or processing). | `15`      |
    - 'actual.log': Log file storing runtime information.

- **proclore**: Processes and system lore.
    - `proclore.c`: Implementation file for process handling.
        - *Contains the implementation of process handling functions.*
        - *functions Used:*
            ### Functions Table

        | **Function Name**              | **Description**                                                                                          | **Error Handling**                                                                                           | **Memory Management**                                                                                                                                                                     |
        |--------------------------------|----------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
        | `getTerminalPGID(const char* ttyPath)` | Retrieves the process group ID of the terminal associated with `ttyPath`.                               | Prints error message using `perror` if `open` fails. Returns `-1` on failure.                               | No dynamic memory allocation.                                                                                                                                                             |
        | `getProcessId(pid_t pid)`              | Gets the process group ID of the specified process ID `pid`.                                               | Prints error message using `perror` if `getpgid` fails. Returns `-1` on failure.                            | No dynamic memory allocation.                                                                                                                                                             |
        | `isForegroundProcess(pid_t pid, const char* ttyPath)` | Determines if the process with ID `pid` is in the foreground by comparing its PGID to the terminal's PGID. | Returns `-1` and prints error messages if getting terminal PGID or process PGID fails.                       | No dynamic memory allocation.                                                                                                                                                             |
        | `proclorePathConstructor(pid_t ID)`     | Constructs and returns a path to the `/proc` directory for the given process ID `ID`.                    | Prints error message if `malloc` fails. Returns `NULL` on failure.                                          | Allocates memory for the path string, should be freed by the caller.                                                                                                                      |
        | `statusPathConstructor(pid_t ID)`       | Constructs and returns a path to the `/proc/stat` file for the given process ID `ID`.                    | Prints error message if `malloc` fails or if `snprintf` exceeds buffer size. Returns `NULL` on failure.     | Allocates memory for the path string, should be freed by the caller.                                                                                                                      |
        | `printProclore1(char* bufferForProclore, pid_t ID)` | Parses and prints process information from `bufferForProclore` and `/proc/%d/status`.                      | Prints error message if `fopen` fails. Prints error message if `sscanf` or file reading fails.               | No dynamic memory allocation.                                                                                                                                                             |
        | `relativePathGenerator(char* homeDirectory, char* path)` | Generates a relative path starting with `~` for a path if it starts with `homeDirectory`.                  | Prints error message if `malloc` fails. Returns `NULL` on failure.                                          | Allocates memory for the relative path, should be freed by the caller.                                                                                                                     |
        | `printExecutablePath(char* proclorePath, Prompt* prompt)` | Prints the executable path of the process based on `proclorePath`.                                         | Prints error message if `readlink` fails.                                                                 | No dynamic memory allocation. Uses `relativePathGenerator` which allocates memory, should be freed by the caller.                                                                          |
        | `readProclore(char* path, pid_t ID, char* proclorePath, Prompt* prompt)` | Reads and processes the content of the `/proc` file, prints process information and executable path.         | Prints error message if `fopen` or `fgets` fails.                                                            | No dynamic memory allocation. Calls `printProclore1` and `printExecutablePath`, which handle memory management for their own allocations.                                                |
        | `proclore(pid_t ID, Prompt* prompt)`    | Main function to construct paths and read process information for the given process ID `ID`.                | Prints error message if any path construction or file operations fail. Cleans up allocated memory.           | Allocates memory for paths using `proclorePathConstructor` and `statusPathConstructor`, should be freed by the caller. Ensures all allocated memory is freed upon function completion. |

            **Note:**
            - Functions that dynamically allocate memory (`malloc`) must ensure that the allocated memory is properly freed by the caller to avoid memory leaks.
            - Error handling typically involves checking return values and printing appropriate error messages.
            - Functions that allocate memory must return the allocated memory to the caller, which is responsible for freeing it.
    - `proclore.h` : 
        - *Contains the function declarations for process handling.*
        | **Macro Name** | **Definition** | **Description** |
        |----------------|-----------------|-----------------|
        | `PROCLORE_H`   | `1`             | Prevents multiple inclusions of the header file (`proclore.h`). |
- **redirection**: Handles redirection functionalities.
    - `redirection.c`: Implementation file for redirection functionalities.
        - *Contains the implementation of redirection functions.*
        - *functions Used:*
            ### File: `redirection.c`       
        | **Function Name**           | **Description**                                                                                                               | **Error Handling**                                                                                                                 | **Memory Management**                                                                            |
        |-----------------------------|-------------------------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------|
        | `trimWhitespaces`          | Removes leading and trailing whitespace from a string.                                                                        | None                                                                                                                              | Modifies the input string in place; no new memory is allocated.                              |
        | `makeAbsolutePath`         | Converts a relative path or a home directory path to an absolute path.                                                        | Prints an error message if memory allocation fails.                                                                              | Allocates memory for `absolutePath`, which must be freed by the caller.                       |
        | `getInputRedirectionFile`  | Extracts and returns the input redirection file from a command string.                                                          | None                                                                                                                              | Allocates memory for the input file name, which must be freed by the caller.                 |
        | `getOutputRedirectionFile` | Extracts and returns the output redirection file from a command string, supporting both `>` and `>>` operators.                 | Prints an error message if memory allocation fails.                                                                              | Allocates memory for the output file name, which must be freed by the caller.                |
        | `handleInputRedirection`   | Redirects standard input to the specified file.                                                                               | Prints an error message if opening the input file fails.                                                                          | Frees no memory; manages file descriptors for input redirection.                             |
        | `handleOutputRedirection`  | Redirects standard output to the specified file, supporting append and overwrite modes.                                      | Prints an error message if opening the output file fails.                                                                         | Frees no memory; manages file descriptors for output redirection.                            |
        | `restoreRedirection`       | Restores standard input and output to their original file descriptors.                                                          | None                                                                                                                              | Frees no memory; restores file descriptors.                                                   |
        | `handleRedirection`        | Manages both input and output redirection for a command, including redirection cleanup and restoring original file descriptors. | None                                                                                                                              | Calls other functions that handle memory; ensures allocated memory for file names is freed. |
        | `removeRedirectionSymbols` | Removes redirection symbols and their corresponding file arguments from the command string.                                   | None                                                                                                                              | Modifies the input string in place; no new memory is allocated.                              |
        | `getArgs`                  | Tokenizes a command string into arguments using `scanf`, handling end-of-file (EOF) conditions.                                | None                                                                                                                              | Allocates memory for arguments using `strdup`; caller is responsible for freeing.            |

    - `redirection.h`: Header file for redirection functionalities.
        - *Contains the function declarations for redirection functionalities.*
        - *functions Abstracted:*
            | **Function Name** | **Description** | **Error Handling** | **Memory Management** |
            |-------------------|-----------------|---------------------|------------------------|
            | `handleRedirection`     | Redirects the standard input or output based on the given file path and mode. | None; function does not exit the program. | No dynamic memory allocation. |
        - *Macro Definations:*
            ### File: `redirection.h`
            | **Macro Name** | **Definition** | **Description** |
            |----------------|-----------------|-----------------|
            | `REDIRECTION_H` | `1`             | Prevents multiple inclusions of the header file (`redirection.h`). |

- **reveal**: Functions related to revealing information.
    - `reveal.c`: Implementation file for reveal functionalities.
        - *Contains the implementation of reveal functions.*
        - *functions Used:*
            ### File: `reveal.c`
            | **Function Name** | **Description** | **Error Handling** | **Memory Management** |
            |-------------------|-----------------|---------------------|------------------------|
            | `reveal`          | Reveals information about the system, user, and current directory. | None; function does not exit the program. | Allocates memory for `homeDirectory` and `directoryName`. Caller must free them after use. |
    - `reveal.h`: Header file for reveal functionalities.
        - *Contains the function declarations for reveal functionalities.*
        - *functions Abstracted:*
            | **Function Name**                                 | **Description**                                             | **Error Handling**                                            | **Memory Management**                                  |
            |---------------------------------------------------|-------------------------------------------------------------|---------------------------------------------------------------|--------------------------------------------------------|
            | `permission(mode_t mode)`                         | Prints the permissions of a file in symbolic format.       | None specified.                                              | None (uses standard I/O functions).                   |
            | `printDetails(char* name, char* path)`            | Prints detailed information about a file.                  | Prints an error message if `stat` fails.                     | Allocates and frees `temp`.                           |
            | `colorACCtoFiles(struct dirent* entry, char* path, char* name)` | Prints color-coded file information based on file type. | Prints an error message if `stat` fails.                     | Allocates and frees `temp`.                           |
            | `revealRetList(char* path, Prompt* prompt, bool flagA, bool flagL)` | Reveals files in a directory with optional flags. | Prints an error message if `getFiles` returns NULL.          | Allocates and frees `list` and its elements.          |
            | `printDetailsFile(char* path)`                    | Prints detailed information about a single file.           | Prints an error message if `stat` fails.                     | None (uses standard I/O functions).                   |
            | `isFile(char* path, bool flagL, bool flagA)`      | Checks if a path is a regular file and optionally prints its details. | Prints an error message if `stat` fails.                     | None (uses standard I/O functions).                   |
            | `reveal(char* token, Prompt* prompt, bool flagA, bool flagL, bool prev, char* path)` | Reveals files or directories based on flags and input. | Prints an error message if `isFile` or `revealRetList` fails. | Allocates and frees `freeStore`.                      |
            | `getFiles(char* path)`                            | Retrieves a list of files from a directory.                | Prints an error message if `opendir` fails.                  | Allocates and frees `list` and its elements.          |

        - *Macro Definations:*
            ### File: `reveal.h`
            | **Macro Name** | **Definition** | **Description** |
            |----------------|-----------------|-----------------|
            | `REVEAL_H`     | `1`             | Prevents multiple inclusions of the header file (`reveal.h`). |
        - *Structure Definations:*
            ### File: `reveal.h`
            | **Structure Name** | **Description**                | **Fields**                |
            |--------------------|--------------------------------|---------------------------|
            | `filesList`        | Represents a list of file names.| `char** list;` (Array of file names) <br> `int n;` (Number of files) |
- **seek**: Search functionalities within the application.
    - `seek.c`: Implementation file for search functions.
        - *Contains the implementation of search functions.*
        - *functions Used:*
            ### File: `seek.c`
            | **Function Name**         | **Description**                                                                                           | **Error Handling**                                                                                 | **Memory Management**                                       |
            |---------------------------|-----------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------|------------------------------------------------------------|
            | `generateAbsolutePath`    | Generates an absolute path from the given directory name and the current directory from the prompt.     | Checks for `NULL` and allocation failures.                                                         | Allocates memory for `absolutePath`. Freeing is handled in `seek()`. |
            | `ifTrivialDirectory`      | Checks if a directory name is trivial (`.` or `..`).                                                     | None                                                                                             | No dynamic memory allocation.                              |
            | `searchDir`               | Searches for directories and files recursively based on the provided flags and search name.              | Checks for directory opening failure.                                                            | No dynamic memory allocation.                              |
            | `seek`                    | Orchestrates the search process and handles the results based on the provided flags.                     | Checks for invalid flags and issues during file operations.                                     | Allocates memory for `absolutePath`. Freeing handled within the function. |

    - `seek.h`: Header file for search functions.
        - *Contains the function declarations for search functions.*
        - *functions Abstracted:*
            | **Function Name** | **Description** | **Error Handling** | **Memory Management** |
            |-------------------|-----------------|---------------------|------------------------|
            | `seek`            | Searches for files in the current directory based on the given query. | None; function does not exit the program. | Allocates memory for `list` and its elements. Caller must free them after use. |
        - *Macro Definations:*
            ### File: `seek.h`
            | **Macro Name** | **Definition** | **Description** |
            |----------------|-----------------|-----------------|
            | `SEEK_H`       | `1`             | Prevents multiple inclusions of the header file (`seek.h`). |

- **alias** : Handles alias functionalities.
    - `alias.c`: Implementation file for alias functionalities.
        - *Contains the implementation of alias functions.*
        - *functions Used:*
            ### File: `alias.c`
            | **Function Name**                  | **Description**                                                                                                                                 | **Error Handling**                                                                                                               | **Memory Management**                                                                                                      |
            |------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------|
            | `addAlias(char* aliasName, char* command)` | Adds a new alias to the alias list. Allocates memory for the alias and the command, then appends it to the alias linked list.                        | No error handling for memory allocation errors. Input parameters are assumed valid.                                               | Allocates memory for the alias structure, the alias name, and the command. Frees memory when alias is removed.             |
            | `removeAlias(char* aliasName)`     | Removes an alias from the alias list by matching the alias name, then frees its allocated memory.                                                  | No error messages or return values if the alias is not found or the list is empty.                                                | Frees memory for the alias structure, the alias name, and the command when an alias is removed.                            |
            | `listAliases()`                    | Prints all aliases in the alias list.                                                                                                             | No error handling for an empty alias list; instead, prints "No aliases found".                                                    | Does not manage memory directly, but iterates over the alias list.                                                         |
            | `executeAlias(char* aliasName, Prompt* prompt)` | Stub function for executing an alias by name, passing it to the shell prompt.                                                                  | No error handling implemented yet.                                                                                                | Memory management depends on future alias execution implementation.                                                       |
            | `isAlias(char* aliasName)`         | Checks if a given alias name exists in the alias list.                                                                                            | No error messages or return values if alias is not found; simply returns `false`.                                                 | No memory management involved.                                                                                             |
            | `getCommand(char* aliasName)`      | Retrieves the command associated with an alias name from the alias list.                                                                          | Returns `NULL` if the alias does not exist. No error handling for invalid inputs.                                                 | No memory management involved.                                                                                             |
            | `freeAliasList()`                  | Frees all allocated memory for the entire alias list, including alias names and commands.                                                          | No error messages are returned, but all memory for the alias list is freed.                                                       | Frees memory for the alias list, the alias name, and the command in each node.                                             |
            | `createAliasList()`                | Populates the alias list from `.myshrc`, reading aliases from the file and adding them to the list.                                                | Returns immediately if the file cannot be opened. Skips malformed or incomplete alias entries.                                    | Dynamically allocates memory for each alias added from the file. Frees memory in case of alias removal.                    |
            | `removeLeadingWhitespace(char* str)` | Removes leading and trailing whitespace from a string in-place.                                                                                   | Returns immediately if the string is `NULL`.                                                                                      | Does not allocate or free any memory, operates on the input string.                                                        |
            | `replaceAliasesInString(char* input)` | Replaces all alias names in the input string with their associated commands.                                                                     | Handles `NULL` input with error messages. Reports memory allocation failures.                                                     | Allocates new memory for each alias replacement. Frees old strings and uses `strdup` for reassigning the input string.     |

    - `alias.h`: Header file for alias functionalities.
        - *Contains the function declarations for alias functionalities.*


        ### **Macros**

        | **Macro Name**  | **Description**                                          |
        |-----------------|----------------------------------------------------------|
        | `ALIAS_H`       | A header guard macro to prevent multiple inclusions of the `alias.h` header file. It ensures that the file is only included once in a compilation unit. |

        ---
        ### **Structures**

        | **Structure Name** | **Field Name**   | **Field Type** | **Description**                                                                                 |
        |--------------------|------------------|----------------|-------------------------------------------------------------------------------------------------|
        | `Alias`            | `aliasName`      | `char*`        | Stores the name of the alias (a string). Allocated dynamically.                                  |
        |                    | `command`        | `char*`        | Stores the command associated with the alias (a string). Allocated dynamically.                  |
        |                    | `next`           | `Alias*`       | A pointer to the next alias in the linked list.                                                  |
        |                    | `length`         | `int`          | Stores the length of the alias name.                                                             |
    - `functions.c`: Implementation file for the shell functions.
        - *Contains the implementation of the shell functions.*
        - *functions Used:*
            ### File: `functions.c`
        ---

        ### **Functions**

        | **Function Name**         | **Description**                                                                                                                                         | **Error Handling**                                                                                                                                      | **Memory Management**                                                                                         |
        |---------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------|
        | `addFunction`             | Adds a new function to the linked list of custom functions.                                                                                             | If memory allocation fails for the `Function` structure, the program exits with an error message.                                                       | Allocates memory for a new `Function` and updates the linked list.                                            |
        | `loadFunctions`           | Reads functions from the `.myshrc` file and adds them to the linked list. Handles parsing of function definitions.                                      | Prints an error message if opening the `.myshrc` file fails.                                                                                            | Allocates memory for each `Function` and copies the function name and body to it. Memory is freed elsewhere.  |
        | `executeAliasFunction`    | Searches for a custom function matching the provided command, replaces any arguments (`$1`) in the function body, and executes the commands.             | Handles memory allocation errors for the function body duplication and replacement. If memory allocation fails, an error message is printed.            | Allocates memory for copying and modifying the function body. Frees the duplicated and modified function body after execution.                       |
        | `removeLeadingWhitespace` | Trims leading whitespace from a string.                                                                                                                 | None.                                                                                                                                                   | No dynamic memory management involved.                                                                        |

        ---

        ### **Macros**

        | **Macro Name**             | **Description**                                                                 |
        |----------------------------|---------------------------------------------------------------------------------|
        | `MAX_FUNCTION_NAME`        | Defines the maximum length for the function name (usually defined in `functions.h`). |
        | `MAX_FUNCTION_BODY`        | Defines the maximum length for the function body (usually defined in `functions.h`). |

        ---

        ### **Notes on Function Flow and Usage**

        - **Function Addition and Loading**
        - The `addFunction()` function is responsible for dynamically adding new functions to a global linked list. Each function is allocated memory and linked as part of a list.
        - `loadFunctions()` reads from a configuration file (`.myshrc`) to populate the list of custom functions. It parses the file for function definitions and their bodies.

        - **Executing Functions**
        - `executeAliasFunction()` searches for a function by its name, processes its body by replacing occurrences of `$1` with provided arguments, and executes the modified body as shell commands.

    - `functions.h`: Header file for the shell functions.
        - *Contains the function declarations for the shell functions.*
        - *Macro Definations:*
        ---

        ### **Structures**

        | **Structure Name** | **Field Name**   | **Field Type**  | **Description**                                                   |
        |--------------------|------------------|-----------------|-------------------------------------------------------------------|
        | `Function`         | `functionName`   | `char[MAX_FUNCTION_NAME]` | Stores the name of the custom function.                         |
        |                    | `functionBody`   | `char[MAX_FUNCTION_BODY]` | Contains the body of the custom function as a string.             |
        |                    | `next`           | `Function*`     | Pointer to the next `Function` in the linked list.               |

        ### **Macros**

        | **Macro Name**             | **Description**                                                                 |
        |----------------------------|---------------------------------------------------------------------------------|
        | `MAX_FUNCTION_NAME`        | Defines the maximum length for a function name (256 characters).               |
        | `MAX_FUNCTION_BODY`        | Defines the maximum length for a function body (1024 characters).              |

        ### **Function Prototypes**

        | **Function Name**           | **Description**                                                                                           | **Error Handling**                                                                              | **Memory Management**                                                                          |
        |-----------------------------|-----------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------|
        | `loadFunctions`             | Loads function definitions from the `.myshrc` file and adds them to the global function list.             | Prints an error message if opening the `.myshrc` file fails.                                 | Allocates memory for each `Function` structure. Memory is managed by freeing the list later. |
        | `executeAliasFunction`      | Executes a function if its name matches the command. Replaces function arguments (`$1`) in the function body. | Handles errors in memory allocation for duplicating and modifying function bodies.           | Allocates memory for copying and modifying the function body. Frees this memory after use.  |
        ---
- **iMan**: Manages the interactive manual.
    - `iMan.c`: Implementation file for interactive manual functionalities.
        ---

        ### **Function Table**

        | **Function Name**          | **Description**                                                                                             | **Error Handling**                                                                                   | **Memory Management**                                                      |
        |----------------------------|-------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------|
        | `removeHeaderBeforeHtml`   | Removes everything before the first `<html>` tag in the response and prints the HTML content.              | Prints an error message if the `<html>` tag is not found.                                           | No dynamic memory allocation; operates on input buffer directly.             |
        | `removeHtmlTags`           | Removes all HTML tags from the given string using regular expressions.                                    | Prints an error message if regex compilation fails.                                                | No dynamic memory allocation; modifies the input buffer in-place.           |
        | `isErrorResponse`          | Checks if the response contains the error message "No matches for".                                        | Returns a boolean indicating presence of the error message.                                        | No dynamic memory allocation.                                                |
        | `fetchManPage`             | Fetches the manual page for a given command from the `man.he.net` server and prints the content.            | Handles errors in DNS resolution, socket creation, connection, request sending, and response receiving. Prints error messages accordingly. | No dynamic memory allocation for the response; uses fixed-size buffers.     |
        | `iMan`                     | Wrapper function that calls `fetchManPage` with the provided command.                                      | Relies on `fetchManPage` for error handling.                                                        | No additional memory management; uses `fetchManPage` functionality.         |

        ---

        ### **Notes**

        - **`removeHeaderBeforeHtml(char *response)`**
        - Strips out everything before the `<html>` tag and processes the HTML content. If `<html>` is not found, an error message is printed.
        
        - **`removeHtmlTags(char *str)`**
        - Uses regular expressions to remove HTML tags from the input string. Handles regex compilation errors and modifies the input buffer in place.

        - **`isErrorResponse(const char *response)`**
        - Detects if the response contains the error message "No matches for" and returns a boolean indicating the presence of the error.

        - **`fetchManPage(const char *command)`**
        - Handles the entire process of fetching and displaying a manual page from a remote server. Includes error handling for various stages like DNS resolution, socket operations, and response processing. It uses fixed-size buffers for network communication and error handling.

        - **`iMan(char* command)`**
        - Simplifies calling the `fetchManPage` function with a given command.

    - `iMan.h`: Header file for interactive manual functionalities.

        ---

        ### **Macros Table**

        | **Macro Name**    | **Definition** | **Description**                                            |
        |-------------------|-----------------|------------------------------------------------------------|
        | `BUFFER_SIZE`     | `4096`          | Defines the size of the buffer used for receiving data from the server. This buffer size is used for both sending requests and receiving responses, ensuring enough space for the HTTP data. |
        | `IMAN_H`          | `1`             | Header guard macro to prevent multiple inclusions of the `iMan.h` header file. |
        ---
- **neonate**: Handles neonate functionalities.
    - `neonate.c`: Implementation file for neonate functionalities.
        - *Contains the implementation of neonate functions.*
        - *functions Used:*
            ---

            ### **Function Table**

            | **Function Name**      | **Description**                                                                                 | **Error Handling**                                                                                        | **Memory Management**                                    |
            |------------------------|-------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------|----------------------------------------------------------|
            | `restoreTerminalMode`  | Restores the terminal attributes to their original state.                                        | Prints an error message if restoring terminal attributes fails.                                           | None                                                     |
            | `setRawMode`           | Enables raw mode for terminal input by disabling canonical mode and echo.                       | Prints an error message if getting or setting terminal attributes fails.                                  | None                                                     |
            | `initNeonate`          | Initializes the `neonate` command by disabling buffering on stdout and enabling raw mode.       | None                                                                                                       | None                                                     |
            | `neonateHelper`        | Forks a child process to repeatedly print the most recent process ID from `/proc/sys/kernel/ns_last_pid`. The parent process waits for 'x' to be pressed to kill the child process. | Prints an error message if file operations or process creation fails.                                      | None                                                     |
            | `neonate`              | Executes the `neonate` command. If `time` is positive, it calls `neonateHelper`. Otherwise, it prints the most recent process ID. | Prints an error message if file operations fail.                                                           | None                                                     |
            ---
    - `neonate.h`: Header file for neonate functionalities.
        - *Contains the function declarations for neonate functionalities.*
        - *Macro Definations:*
        ---

        ### **Macros**

        | **Macro Name**    | **Definition** | **Description**                                            |
        |-------------------|-----------------|------------------------------------------------------------|
        | `NEONATE_H`       | `1`             | Prevents multiple inclusions of the header file (`neonate.h`). |
        ---
- **ping** : Handles ping functionalities.
    - `ping.c`: Implementation file for ping functionalities.
        - *Contains the implementation of ping functions.*
        - *functions Used:*
            ### File: `ping.c`
            ---
            ### **Function Table**

            | **Function Name** | **Description**                                                                                       | **Error Handling**                                                                                      | **Memory Management** |
            |-------------------|-------------------------------------------------------------------------------------------------------|----------------------------------------------------------------------------------------------------------|-----------------------|
            | `ping`            | Sends a signal to a process with a specified PID. Updates the process status based on the signal sent. | Prints an error message if the PID is invalid or the signal cannot be sent.                           | None                  |

            ---

    - `ping.h`: Header file for ping functionalities.
        - *Contains the function declarations for ping functionalities.*
        - *Macro Definations:*
        ---

        ### **Macros**

        | **Macro Name**    | **Definition** | **Description**                                            |
        |-------------------|-----------------|------------------------------------------------------------|
        | `PING_H`          | `1`             | Prevents multiple inclusions of the header file (`ping.h`). |
        ---
- **process**
    - `process.c`: Implementation file for process handling.
        - *Contains the implementation of process handling functions.*
        - *functions Used:*
            ### File: `process.c`
            | **Function Name**       | **Description**                                                                                                                                   | **Error Handling**                                                                                                                                                    | **Memory Management**                      |
            |-------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------|
            | `getProcessByPid`       | Retrieves a `Process` structure from the `ProcessList` by PID.                                                                                   | Returns `NULL` if the process with the specified PID is not found.                                                                                                  | None                                       |
            | `initProcessList`       | Initializes the `ProcessList` structure by setting the count to 0.                                                                              | Assumes `processList` is not `NULL`. (May need to handle the case where `*processList` is `NULL`.)                                                                   | None                                       |
            | `addProcess`            | Adds a new process to the `ProcessList`. If the list is full, discards half of the processes and terminates them.                                | Prints a warning if `command` is `NULL`.                                                                                                                             | None                                       |
            | `removeProcess`         | Removes a process from the `ProcessList` by PID and shifts remaining processes up.                                                               | None                                                                                                                                                                   | None                                       |
            | `printProcesses`        | Prints all processes in the `ProcessList` with their PID, command, and status.                                                                   | None                                                                                                                                                                   | None                                       |
            | `updateProcesses`       | Updates the status of all processes in the `ProcessList` based on their current status.                                                         | None                                                                                                                                                                   | None                                       |
            | `compareProcesses`      | Comparison function for sorting processes by their command name.                                                                                | None                                                                                                                                                                   | None                                       |
            | `activities`            | Sorts processes in the `ProcessList` by command name and prints the updated list.                                                                | None                                                                                                                                                                   | None                                       |
            | `bg`                    | Resumes a process in the background by sending it the `SIGCONT` signal. Ignores certain signals to prevent interruption.                           | Prints an error message if the process is not found.                                                                                                                  | None                                       |
            | `fg`                    | Stops a process and brings it to the foreground by sending it the `SIGSTOP` signal.                                                               | Prints an error message if the process is not found.                                                                                                                  | None                                       |
            | `updateSingleProcess`   | Updates the status of a single process by PID and removes it from the list if it has exited.                                                     | None                                                                                                                                                                   | None                                       |

    - `process.h`: Header file for process handling.
        - *Contains the function declarations for process handling.*
        - *Macro Definations:*
        ---
        ### Structure Table

        | **Structure Name** | **Field Name** | **Type**              | **Description**                                                  |
        |--------------------|----------------|-----------------------|------------------------------------------------------------------|
        | `Process`          | `command`       | `char[4096]`          | Command associated with the process.                             |
        |                    | `pid`           | `int`                 | Process ID.                                                      |
        |                    | `status`        | `int`                 | Current status of the process (`RUNNING` or `STOPPED`).           |
        | `ProcessList`      | `processes`     | `Process[MAX_PROCESSES]` | Array of `Process` structures.                                   |
        |                    | `count`         | `int`                 | Number of processes currently in the list.                       |
        ---
        ### Macros Table

        | **Macro Name**    | **Definition** | **Description**                                                |
        |-------------------|----------------|----------------------------------------------------------------|
        | `MAX_PROCESSES`   | `100`          | Maximum number of processes that can be stored in the `ProcessList`. |
        | `STOPPED`         | `1`            | Status indicating that the process is stopped.                |
        | `RUNNING`         | `0`            | Status indicating that the process is running.                |
        ---
- **redirection**: Handles redirection functionalities.
    - `redirection.c`: Implementation file for redirection functionalities.
        - *Contains the implementation of redirection functions.*
        - *functions Used:*
        ### Function Table
        | **Function Name**              | **Description**                                                                                           | **Error Handling**                                                      | **Memory Management**                         |
        |--------------------------------|-----------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------|----------------------------------------------|
        | `trimWhitespaces`              | Removes leading and trailing whitespaces from a string.                                                   | Checks if the input string is `NULL`.                                    | No dynamic memory allocation.                |
        | `makeAbsolutePath`             | Converts a relative or tilde path to an absolute path based on the user's home directory or current directory. | Handles memory allocation failure.                                      | Allocates memory for the absolute path, which should be freed by the caller. |
        | `getInputRedirectionFile`      | Extracts the input redirection file from a command string.                                                | No specific error handling for `NULL` input in command.                 | Allocates memory for the file name, which should be freed by the caller. |
        | `getOutputRedirectionFile`     | Extracts the output redirection file and determines if it should be appended or overwritten.               | No specific error handling for `NULL` input in command.                 | Allocates memory for the file name, which should be freed by the caller. |
        | `handleInputRedirection`       | Redirects standard input to a specified file.                                                              | Checks if the file descriptor is valid; does not handle file open errors directly. | No dynamic memory allocation.                |
        | `handleOutputRedirection`      | Redirects standard output to a specified file with support for append or overwrite modes.                  | Checks if the file descriptor is valid; does not handle file open errors directly. | No dynamic memory allocation.                |
        | `restoreRedirection`           | Restores original standard input and output from saved descriptors.                                        | No error handling for `dup2` failures.                                   | No dynamic memory allocation.                |
        | `handleRedirection`            | Manages input and output redirection, handling file existence checks and restoring original I/O.            | Checks if the input or output file does not exist.                       | Allocates memory for input and output file names, which should be freed by the caller. |
        | `removeRedirectionSymbols`     | Removes redirection symbols and their file arguments from a command string.                               | No specific error handling for `NULL` command.                           | No dynamic memory allocation.                |
        | `getArgs`                      | Reads additional arguments from stdin and returns them as a concatenated string.                           | No specific error handling for `scanf` or `malloc` failures.             | Allocates memory for the concatenated string, which should be freed by the caller. |
        | `handlePipes`                  | Handles piping between two commands, creating a pipe, forking processes, and managing redirection.         | Handles fork failures and pipe creation failures.                        | No dynamic memory allocation within the function. |
        ---
        ### Macro Table
        | **Macro Name**   | **Definition** | **Description**                                                   |
        |------------------|----------------|-------------------------------------------------------------------|
        | `RED`            | (Defined in `color.h`) | Text color for errors.                                            |
        | `RESET`          | (Defined in `color.h`) | Resets text color to default.                                     |
        ---
    - `redirection.h`: Header file for redirection functionalities.
         ### Header File Macro Table

        | **Macro Name**       | **Value/Description**                                        |
        |----------------------|--------------------------------------------------------------|
        | `REDIRECTION_H`      | `1` (Used to prevent multiple inclusions of this header file)|
        ---
- **.myshrc** : contains the aliases and custom functions
    - `alias` : short form of the commands
        - 'syntax' : `<alias_name> <command>`
    - `functions` : custom functions
        - `syntax` : 
        ``` 
        function <function_name>()
        { 
            <function_body> 
        }
        ```
        - supprts upto 1 argument `$1`
        - `function body` format
            - `command $1   # comment` : for single command
            - multiple commands should be separated by `\n`
            - supports single line comments starting with `#`
    - `example` :
        ```
        ll = ls -l # list all files in long format
        
        revealL = reveal -l # this is a comment
        revealA = reveal -a
        revealAL = reveal -a -l
        
       function mk_hop() 
        { 
            mkdir "$1" # Create the directory 
            hop "$1" # Change into the directory 
        }

        ```
    - *Any other format will lead to an error.*
    - *The file should be present in the home directory.*
    - *The file should be named `.myshrc`.*
    - *The file should be a hidden file.*
    - *The file should be a text file.*
    - *The file should contain aliases and functions only.*
    - *The file should not contain any other content.*
    - *The file should not contain any syntax errors.*

- **command**: 
    - `globals.h`: Contains global variables and macros used throughout the shell.
        ### **Global Variables**
        | **Variable Name**  | **Type**           | **Description**                                               |
        |--------------------|--------------------|---------------------------------------------------------------|
        | `globalProcessList`| `ProcessList**`    | Pointer to a global list of processes.                       |
        | `COMMAND`          | `char*`            | Pointer to a global command string.                          |
        | `foregroundPid`    | `int`              | PID of the foreground process.                               |
        | `PROMPT`           | `Prompt*`          | Pointer to a global `Prompt` structure.                       |
        | `shellPid`         | `int`              | PID of the shell process.                                   |
        ### **Macros**
        | **Macro Name** | **Value/Description**                                                                 |
        |----------------|---------------------------------------------------------------------------------------|
        | `GLOBALS_H`    | `1` (Used to prevent multiple inclusions of this header file)                         |
    - `globals.c`: Contains global variable definations only.
   
    - `signals.c`: Contains signal handling functions.
        ### Functions Table
        | **Function Name**           | **Description**                                                                                                   | **Error Handling**                                                                                           | **Memory Management**                  |
        |-----------------------------|-------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------|---------------------------------------|
        | `sendSignal(pid_t pid, int signal_number)` | Sends a signal to a specified process. Prints error messages if the signal cannot be sent.                          | Checks if the process exists and if the signal was successfully sent. Prints error messages on failure.    | No dynamic memory allocation.          |
        | `handleSigint(int signum)`            | Handles the SIGINT signal (Ctrl-C). Sends SIGINT to the foreground process, if any, and removes it from the process list. | Prints error message if sending SIGINT fails. No error handling for invalid foregroundPid.                | No dynamic memory allocation.          |
        | `backgroundProcessHandler(int signum)` | Handles background processes by waiting for them to change state and updating the process list accordingly.         | Prints error message if there are issues with waiting for child processes.                                | No dynamic memory allocation.          |
        | `handleSigtstp(int signum)`           | Handles the SIGTSTP signal (Ctrl-Z). Stops the foreground process, if any, and adds it to the background process list. | Prints error message if sending SIGTSTP fails. No error handling if the process cannot be found in the list. | No dynamic memory allocation.          |
        | `bgForegroundHandler(int signum)`     | Handles the SIGTSTP signal (Ctrl-Z) for the foreground process specifically, stopping it and adding it to the background list. | Prints error message if sending SIGTSTP fails. No error handling if the process cannot be found in the list. | No dynamic memory allocation.          |
        | `setupSignalForForeground()`          | Sets up the signal handler for SIGTSTP to handle stopping of foreground processes.                                  | No error handling is provided for signal setup failure.                                                    | No dynamic memory allocation.          |
        | `setupSignal()`                       | Sets up signal handlers for SIGCHLD, SIGTSTP, and SIGINT to manage background processes and interruptions.           | Prints error messages and exits the program if setting up signal handlers fails.                          | No dynamic memory allocation.          |

        ---


    - `signals.h`: Contains the function declarations for signal handling.

    ### Header File Macro Table

    | **Macro Name**       | **Value/Description**                                        |
    |----------------------|--------------------------------------------------------------|
    | `SIGNALS_H`          | `1` (Used to prevent multiple inclusions of this header file)|
    ---
### Execution Flow: `main.c`
- The main function initializes the shell and runs the shell loop.
- The shell loop reads the user input, processes the input, and executes the command.
- The command execution logic tokenizes the input command and determines whether to run the command in the foreground or background.
- The command execution logic then executes the command by forking a new process and using `execvp`.
- The directory hopping logic changes the current working directory based on the given path.
- The system display logic retrieves system information and displays the prompt to the user.
- The user interface logic initializes the prompt structure and prints the prompt to the terminal.
- The process handling logic retrieves process information and displays it to the user.
- The logging logic reads and writes log information to the `actual.log` file.
- The reveal logic reveals information about the system, user, and current directory.
- The search logic searches for files and directories based on the provided query.
- The alias logic manages aliases for commands.
- The function logic manages custom functions for the shell.
- The interactive manual logic fetches and displays manual pages for commands.
- The neonate logic displays the most recent process ID or continuously updates the process ID. 
- The ping logic sends signals to processes based on the provided PID.
- The redirection logic handles input and output redirection for commands.
- The signal handling logic manages signals for foreground and background processes.
- The global variable logic defines and initializes global variables used throughout the shell.
-  The command logic processes the user input and executes the corresponding command.


### Commands Supported: `⚙️`
- **hop**: Change the current working directory and prints the absolute path.
    - *Syntax*: `hop <directory>`
        - if `directory` is `"~"`, it changes to the home directory.
        - if `directory` is `"-"`, it changes to the last working directory.
        - otherwise, it changes to the specified directory.
        - in case of no arguments, it changes to the home directory.
        - muliple arguments leads to the final directory till no error and all paths are printed.
- **reveal**: Reveals information about the system, user, and current directory.
    - *Syntax*: `reveal <flag> <directory>`
        - if `flag` is `"-a"`, it reveals all files and directories.
        - if `flag` is `"-l"`, it reveals detailed information about the directory.
        - if `flag` is `"-a*l*"` or `"-l*a*"` or `any order of a and l (both inclusive)`, it reveals all files and directories with detailed information.
        - if `directory` is not provided, it reveals information about the current directory.
        - prints the executables in green, directories in blue, and other files in white.
        - prints the permissions of the files in symbolic format.
- **log**: Handles logging functionalities.
    - *Syntax*: `log`
        - displays the contents of the `actual.log` file.
    - *Syntax*: `log purge`
        - purges the contents of the `actual.log` file.
    - *Syntax*: `log execute <number>`
        - executes the last `number` commands from the `actual.log` file.
    - *Note*: The `log` does not logs the most recent command.
        - It logs all the commands (erreneous too) except the most recent one.
        - The input directly entered in the terminal is logged irrespective of the output.
- **proclore**: Handles process lore.
    - *Syntax*: `proclore <process ID>`
        - if `process ID` is provided, it prints the process information for the given process ID.
        - if no `process ID` is provided, it prints the process information for the current process (terminal).
        - prints the process information for the given process ID.
- **seek**: Handles search functionalities.
    - *Syntax*: `seek <flag> <search query> <directory>`
        - Given the flags are provided, in the form:
            `seek -d <search query> <directory>` or `seek -f <search query> <directory>` or `seek -e <search query> <directory>`
            `seek -d -f <search query> <directory>` or `seek -f -d <search query> <directory>`or `seek -d -e <search query> <directory>`
            `seek -e -d <search query> <directory>` or `seek -f -e <search query> <directory>` or `seek -e -f <search query> <directory>`
            `seek -e*f*d* -f*e*d* -d*f*e* <search query> <directory>` 
            i.e. at max 3 flags are allowed. 
        - if 'flag' is `"-d"`, it searches for only directories based on the search query.
        - if 'flag' is `"-f"`, it searches for only files based on the search query.
        - if both `"-d"` and `"-f"` are provided, leads to an error.
        - if no flag `-d` or `-f` is provided, it searches for both files and directories based on the search query.
        - if 'search query' is not provided, it throws an error.
        - if 'directory' is not provided, it searches in the current directory.
        - if 'directory' is provided, it searches in the specified directory.
        - prints the search results based on the flags and search query.
        - prints the relative path of the search results based on the base directory.
        - prints the search results in color-coded format (directories in blue, files in green).
        - if flag is `"-e"`, if search contains exactly one file (0 directories) it prints the content of the file.
        - if flag is `"-e"`, if search contains more than one file it just prints the names of the files.
        - if flag is `"-e"`, if search contains only one directory (0 files) it prints the exact path of the directory and hops to it.
        - if flag is `"-e"`, if search contains more than one directory it just prints the names of the directories.
- **q**: Quits the shell.
- **fg**: Brings the background process to the foreground.
    - *Syntax*: `fg <PID>`
        - if `PID` is provided, it brings the specified process to the foreground.
        - if no `PID` is provided, it throws an error.

- **bg**: Continues the stopped background process.
    - *Syntax*: `bg <PID>`
        - if `PID` is provided, it continues the specified process in the background.
        - if no `PID` is provided, it throws an error.
- **activities**: Displays the activities of the processes.
    - *Syntax*: `activities`
        - displays the activities of the processes.
- **ping**: Sends a signal to a process based on the provided PID.
    - *Syntax*: `ping <PID> <signal>`
        - if `PID` is provided, it sends the specified signal to the process with the given PID.
        - if no `PID` is provided, it throws an error.
        - if no `signal` is provided, it throws an error.
        - if the `PID` is not found, it throws an error.
        - if the `signal` is not found, it throws an error.
        - if the `signal` is not a number, it throws an error.
- **neonate**: Displays the most recent process ID or continuously updates the process ID.
    - *Syntax*: `neonate <time>`
        - if `time` is provided, it continuously updates the process ID every `time` seconds.
        - if no `time` is provided, it displays the most recent process ID.
        - press `x` to stop the continuous update for both cases.
        - if `time` is not a number, it throws an error.
- **iMan**: Displays the interactive manual for a given command.
    - *Syntax*: `iMan <command>`
        - if `command` is provided, it displays the interactive manual for the given command.
        - if no `command` is provided, it throws an error.

- **Other Commands**: Any other command is executed as a system command using `execvp`.
    - if the provided command is not found, it prints an error message.

- **Note**: if foreground command takes more than 2 seconds, it updates the `command2sec` in the prompt.
    - The prompt is updated with the current user, system, directory, and additional details.
    - The prompt is updated after each command execution.
    - if proclore shows the executable or readlink error of permission denied, then try with `sudo` or `chmod +x` to get the details.
    - if seek shows the permission denied error, then try with `sudo` to get the details. 
    - for the above two points, run the file with:
        ```shell
        sudo ./a.out
        ```


### Error Handling: `🚨`
- The shell handles errors by printing error messages to the standard output and exiting the program in case of critical errors.
- All error messages are printed in red color to distinguish them from regular output and are redirected to the standard error stream.
- Internal Errors such as fopen, fork, execvp, etc. are handled by printing an error message and continuing the shell loop.
- The shell handles invalid commands by printing an error message and continuing the shell loop.
- In case of erreneous pipes, same system for bash is followed.
- If the prompt is not initialized properly, the shell prints an error message and exits.
- Once the prompt is initialised properly, then the user can only exit when the user enters `q` or `ctrl+d`.
- The shell handles invalid commands by printing an error message and continuing the shell loop.
### Assumptions: `🧠`
- Max INPUT command length is 1000. // 4096
- Max number of arguments in the command is 100.
- Max number of files in the directory is 100. // 1000
- Max number of lines to display is 15.
- Max number of flags in seek is 3 i.e. [- - -] written in the query.
- Max length of the path is 100. // 1024
- Max length of the directory name is 100. // 4096
- Max length of the home directory is 100. // 4096
- Max length of the prompt is 100. //
- Max length of the command2sec is 100. //
- if user enters the command with '&' at the end, then it is considered as a background process.
- if user uses `hop -` then it changes to the last working directory. if last working directory is not present, then it throws an error.
- if reveal is used with file names, 
    - if `-l` then it prints only the details of the files.
    - if `-l` is missing then it prints only the names of the file.
    - irrespective of the flag `a` it prints the details of the files wheter hidden or not.
- `reveal -` throws an error if the directory is not present.
- `proclore` - In case some process is not present or permission denied, then it throws an error.
    - proclore prints the states used by the linux system. 
- Even with sudo command some of the files may not be accessed due to permission denied as present in the system.
- In `seek` we assume executables files may not be searched as there output may be large and uninterpretable in `e` flag.
- `-` is not considered as a search match or file in `seek` command, however, it is considered as a base directory for seeking.
- if the search query is not present in the directory, then it prints an error.
- if the search query is not present in the file, then it prints an error.

- vi & vim shows some exceptional or random behavior sometimes, so it is not considered as a bug. (Sometimes works fine, sometimes not)
- For testing `gedit` is used, so everything is tested with `gedit` and is considered as a standard for testing.
- The above point is supported by `ps` and `proclore` commands.
- pipings work fine along with input `redirection and output redirection`.
- Also they work fine for both `system and user commands`
- Pipings are not handled for background processes. (Shells supports for only specific cases)
- For Alias and Functions, the file should be present in the home directory and should be named `.myshrc`.
- The file should be a hidden file and should be a text file.
- The file should contain aliases and functions only.
- Comments are allowed in the file, but the format should be followed.(starts with `#`)
- Strictly the format should be followed for the file.
    - `alias` : short form of the commands
        - 'syntax' : `<alias_name> = <command>`
    - `functions` : custom functions
        - `syntax` : 
        ``` 
        function <function_name>()
        { 
            <function_body> 
        }
        ```
        - supprts upto 1 argument `$1`
        - `function body` format
            - `command $1   # comment` : for single command
            - multiple commands should be separated by `\n`
            - supports single line comments starting with `#`
- Also when the terminal is run it shows the mapping for the alias and functions available.
    ```
    Loading functions from .myshrc
    mk_hop
    hop_seek
    List of aliases:
    revealL -> reveal -l
    ```
- If a foreground command takes more than 2 seconds, then it updates the `command2sec` in the prompt.
    - The syntax is followed for every command except for the `fg` command
    ```
    <shreyasmehta@pop-os:~vi: 5sec> 
    ```
    - for `fg`
    ```
    <shreyasmehta@pop-os:~vi> 
    ```
- whenever `q` is entered, it exits the shell after cleaning up the background processes which takes some milliseconds.
- same for `ctrl+d`.
- whenever a background process is run, the shell prints a new line. So it seems like the shell is not in control but it is just entering a new line.
- Rest all functionalities considers bash implementation as the standard.
- The maximum number of background process is supported by this shell is 100.
- If the process exceeds 100, then it truncates the process list to 50 and kills the rest of the processes. 


### References: `📚`
- [Linux System Programming](https://www.geeksforgeeks.org/linux-system-program)
- [Stack Overflow](https://stackoverflow.com)
- [Man Pages](https://man7.org)
- [Geeks for Geeks](https://www.geeksforgeeks.org)
- [chatGPT](https://chatgpt.com/c/e6c2f463-27f6-494a-a631-529d469802f3)
- [chat-1](https://chatgpt.com/c/6cad8fbf-a024-45a1-81c7-ed152a1132d3)
- [chat-2](https://chatgpt.com/c/2d8a4395-553c-4caa-9465-4871818dbac2)
- [chat-3](https://chatgpt.com/c/2d8a4395-553c-4caa-9465-4871818dbac2)
- [chat-4](https://chatgpt.com/c/b5eac6d1-5b93-42b0-a6f0-ba36e7b85a82)
- Prompts pics are given in `image` folder.
- Tut Slides
- Funtions looked up in *man pages/online*:
    - uname
    - gethostname
    - signal
    - waitpid
    - getpid
    - kill
    - execvp
    - strtok
    - fork
    - getopt
    - readdir
    - opendir
    - readdir
    - closedir
    - getcwd
    - sleep
    - struct stat
    - struct dirent
    - /proc/interrupts
    - fopen
    - chdir
    - getopt
    - pwd.h (to obtain username)
    - /proc/loadavg
    - getpwuid
    - readlink
    - stat
    - read
    - write
    - open
    - close
    - getpgid
    - getuid
    - geteuid
    - getgid
    - getegid
    - termios
    

