#include<stdio.h>
void paste()
{    //pastes contents of buffer to a text file
    system("xclip -o >>abc.txt");
    //adds a newline after pasting
    FILE *file = fopen("abc.txt","a");
    if(file!= NULL){
        fputs("\n",file);
    }
    fclose(file);
}    

int main(int argc, char *argv[]){
    paste();
}
