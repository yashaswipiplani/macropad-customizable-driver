#ifndef _BST_HEADER
#define _BST_HEADER

extern void openSoftware(void);
extern void sendSaveSignal(Window window);
extern void splitTerminal(void);
extern void callForCompileExecute(void);
extern void compileExecute(const char *filename);
extern void copyPaste(void);

#endif
