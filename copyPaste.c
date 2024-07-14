#include<stdio.h>
#include "macropad.h"

void copyPaste(void){


    system("xclip -out -selection primary | xclip -in -selection clip");
    system("xclip -o >>Stored_data.txt");
    FILE *file = fopen("Stored_data.txt","a");
    if (file != NULL){
    fputs("\n",file);
    
    }
    fclose(file);
}
