void paste()
{
    system("xclip -o >abc.text");
}    

int main(int argc, char *argv[]){
    paste();
}
