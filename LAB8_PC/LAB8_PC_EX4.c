/*
    4. Scrieți un program, folosind getchar() si putchar() care, primind la stdin un fișier text va tipari la iesirea standard
    acelasi fisier text dar va schimba literele mari intalnite in fisier in litere mici iar cele mici in litere mari.
*/

#include <stdio.h>

int main(){
    
    char ch;
    
    while((ch = getchar()) != EOF){
        if(ch >= 'a' && ch <= 'z'){
            ch = ch - ('a'-'A');
        }
        else if(ch >= 'A' && ch <= 'Z'){
            ch = ch + ('a'-'A');
        }
        putchar(ch);
    }
    
    return 0;
}
