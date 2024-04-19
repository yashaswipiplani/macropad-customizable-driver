#include<stdio.h>
void paste()
{
    system("xclip -o >>abc.txt");
    FILE *file = fopen("abc.txt","a");
    if(file!= NULL){
        fputs("\n",file);
        fclose(file);
    }
}    

int main(int argc, char *argv[]){
    paste();
}
