#include<stdio.h>

void paste(){


    system("xclip -out -selection primary | xclip -in -selection clip");
    system("xclip -o >>Stored_data.txt");
    FILE *file = fopen("Stored_data.txt","a");
    if (file != NULL){
    fputs("\n",file);
    
    }
    fclose(file);
}
int main(int argc, char *argv[]) {
    paste();
}
