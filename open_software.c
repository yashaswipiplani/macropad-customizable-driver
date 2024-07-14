#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "macropad.h"

#define EXECUTABLE_PATH "/D/Programs/BCUninstaller_5.7_portable/BCUnistaller"

void openSoftware(void) {
        printf("Executing software: %s\n", EXECUTABLE_PATH);
        // Simulate call to user mode helper
        system(EXECUTABLE_PATH);
}

void signal_handler(int signum) {
    if (signum == SIGUSR3) {
        openSoftware();
    }
}

int main() {
    signal(SIGUSR3, signal_handler);
    while (1) {
        sleep(1); // Keep the program running
    }
    return 0;
}