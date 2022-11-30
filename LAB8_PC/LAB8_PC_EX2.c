/*
 2. Scrieți un program, folosind getchar() și putchar(), care, primind la stdin redirectat un fișier ce conține un cod C, va printa
 la stdout același fișier dar fără comentarii. Practic, programul va elimina comentariile din fișierul C primit prin redirectare de
 stdin și va printa rezultatul la stdout
*/
#include <stdio.h>

int main(){
    char ch, aux, aux2;
    int ok = 1;
    
    while((ch = getchar()) != EOF){
        ///if(ch == '\n') continue;
        if(ch == '/'){
            aux = getchar();
            if(aux == '*') ok = 0;
            if(aux == '/'){
                while(aux2 = getchar()){
                    if(aux2=='\n') break;
                }
                continue;
            }
        }
        
        if(ok == 1){
            putchar(ch);
        }
        else{
            if(ch == '*'){
                aux = getchar();
                if(aux == '/') ok = 1;
            }
        }
    }
    
    return 0;
}
