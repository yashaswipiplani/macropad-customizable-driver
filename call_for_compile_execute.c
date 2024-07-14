#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "macropad.h"

// this function essentially takes the input filename as the command-line argument and run the entered ".c" filename along the compile_execute.c
void callForCompileExecute()
{
    char filename[256]; // Buffer to store filename
    printf("Enter the filename of the C program to compile and run: ");
    scanf("%s", filename); // Takes the input filename

    char command[1024];                                 // Bufer to store the created command
    sprintf(command, "./compile_execute %s", filename); // Creating the command to run compile_exeute file and passing filename as the argument
    system(command);                                    // Compile and execute the specified file
}

void signal_handler(int signum)
{
    if (signum == SIGUSR1)
    {
        callForCompileExecute();
    }
}

int main()
{
    signal(SIGUSR1, signal_handler);
    while (1)
    {
        sleep(1); // Keep the program running
    }
        return 0;
}