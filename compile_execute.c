#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_FILENAME_LENGTH 256

char currentFile[MAX_FILENAME_LENGTH];

void getCurrentFile();

void compileExecute(void){
    char command[MAX_COMMAND_LENGTH];
    // Get the current file name from the IDE
    getCurrentFile();

    // Check if a file is currently open
    if (currentFile[0] == '\0') {
        printf("No file is currently open in the IDE.\n");
        return 1;
    }

    // Construct the command to compile the C program
    sprintf(command, "gcc -o %s.out %s", currentFile, currentFile);

    // Execute the compilation command
    if (system(command) != 0) {
        printf("Compilation failed.\n");
        return 1;
    }

    // Construct the command to run the compiled program
    sprintf(command, "./%s.out", currentFile);

    // Execute the run command
    if (system(command) != 0) {
        printf("Program execution failed.\n");
        return 1;
    }
}

// Function to get the current file name from the IDE
void getCurrentFile() {
    // Assuming you're using Visual Studio Code, you can use the `code` command
    // to get the current file name from the terminal
    FILE* pipe = popen("code --file-info", "r");
    if (pipe == NULL) {
        fprintf(stderr, "Failed to run 'code --file-info'\n");
        return;
    }

    char buffer[MAX_FILENAME_LENGTH];
    fgets(buffer, MAX_FILENAME_LENGTH, pipe);
    pclose(pipe);

    // Extract the file name from the output
    char* token = strtok(buffer, " ");
    if (token != NULL) {
        strcpy(currentFile, token);
    } else {
        currentFile[0] = '\0';
    }
}
