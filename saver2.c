#include <stdio.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

Display *display;

// IMPORTANT: Link with X11 when compiling and creating an executable.
// gcc saver2.c -lX11

// Creating an event seems like the more 'appropriate' way to interact with application interfaces.
// Alternatively, XTestFakeKeyEvent can also be used for quick testing of other functions.

void sendSaveSignal(Window window) {
    XKeyEvent event;

    event.display = display;
    event.window = window;
    event.root = DefaultRootWindow(display);
    event.subwindow = None;
    event.time = CurrentTime;
    event.x = 1;
    event.y = 1;
    event.x_root = 1;
    event.y_root = 1;
    event.same_screen = True;
    event.keycode = XKeysymToKeycode(display, XK_S);  // Send 'S' key
    event.state = ControlMask;  // Add Ctrl key modifier

    // Send key press event
    event.type = KeyPress;
    XSendEvent(display, window, True, KeyPressMask, (XEvent *)&event);

    // Send key release event
    event.type = KeyRelease;
    XSendEvent(display, window, True, KeyReleaseMask, (XEvent *)&event);

    XFlush(display);
}


int main(){

    display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "Failed to open X display\n");
        return 1;
    }

    Window focusedWindow;
    int revert;

    printf("Waiting to focus window");

    sleep(2);
    // This sleep is to allow us to switch to an active window where Ctrl+S is a save hotkey.
    // Should only be needed for testing purposes.

    XGetInputFocus(display, &focusedWindow, &revert);

    if (focusedWindow == None) {
        fprintf(stderr, "No focused window found\n");
        return 1;
    }

    // Simulate "Save" signal
    sendSaveSignal(focusedWindow);

    XCloseDisplay(display);
    return 0;
}
