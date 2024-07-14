#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "macropad.h"

#define MAX_COMMAND_LENGTH 1024
#define MAX_FILENAME_LENGTH 256

// Actually compiles and executes the file
void compileExecute(const char *filename) {
    char compileCommand[MAX_COMMAND_LENGTH];
    char runCommand[MAX_COMMAND_LENGTH];

    // Check if filename is valid
    if (filename == NULL || filename[0] == '\0') {
        printf("No filename provided.\n");
        exit(1);
    }

    // Construct the command to compile the C program
    sprintf(compileCommand, "gcc -o %s.out %s", filename, filename);

    // Execute the compilation command
    if (system(compileCommand) != 0) {
        printf("Compilation failed.\n");
        exit(1);
    }

    // Construct the command to run the compiled program
    sprintf(runCommand, "./%s.out", filename);

    // Execute the run command
    if (system(runCommand) != 0) {
        printf("Program execution failed.\n");
        exit(1);
    }
}

// Main function needed as the filename is taken as a command line argument when this file is run by call_for_compile_execute
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    compileExecute(argv[1]);
    return 0;
}
