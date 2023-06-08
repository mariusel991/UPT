/* 
 8. Sa se scrie o functie cu urmatorul antet:
 
uint32_t upper_sub_string(char *str, const char *substr);
    
Pentru fiecare aparitie a string-ului substr in string-ul str se va modifica ca acest string din str sa fie transpus in litere mari (upper-case) Functia va returna numarul de aparitii.

Exemplu:

char s1[] = "Acesta este un string si stringul este terminat cu 0x00";
char s1[] = "string";
int r = upper_sub_string(s1, s2);
s1 devine "Acesta este un STRING si STRINGul este terminat cu 0x00";
s2 ramane neschimbat
r devine 2

Se va testa cu string-uri citite de la tastatura.

*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>

uint32_t upper_sub_string(char *str, const char *substr){
    
    char* p = strstr(str,substr);
    
    if(p == NULL){
        return 0;
    }
    
    for(int i = 0; i < strlen(substr); i++){
        ///printf("%c ",*(p+i));
        if(*(p+i) >= 'a' && *(p+i) <= 'z'){
            *(p+i) = *(p+i) - ('a'-'A');
        }
        ///printf("%c ",*(p+i));
    }
    return 1 + upper_sub_string(str, substr);
}


int main(){
    
    char s1[] = "Acesta este un string si stringul este terminat cu 0x00";
    char s2[] = "string";
    int r = upper_sub_string(s1, s2);
    printf("%s\n", s1);
    printf("%d\n", r);
    
    return 0;
}
