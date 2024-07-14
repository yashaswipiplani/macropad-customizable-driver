#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include "macropad.h"

void splitTerminal() {
    Display *display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "Unable to open display\n");
        exit(1);
    }

    XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Control_L), True, 0);
    XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Shift_L), True, 0);
    XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_5), True, 0);
    XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_5), False, 0);
    XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Shift_L), False, 0);
    XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Control_L), False, 0);

    XFlush(display);
    XSync(display, True);

    XCloseDisplay(display);
}

void signal_handler(int signum) {
    if (signum == SIGUSR2) {
        splitTerminal();
    }
}

int main() {
    signal(SIGUSR2, signal_handler);
    // Print a message before executing the shortcut
    printf("Executing Ctrl+Shift+5 keyboard shortcut...\n");
    
    // Execute Ctrl+Shift+5 keyboard shortcut without xdotool
    splitTerminal();

    // Print a message after executing the shortcut
    printf("Ctrl+Shift+5 keyboard shortcut executed.\n");
    while (1) {
        sleep(1); // Keep the program running
    }
    return 0;
}