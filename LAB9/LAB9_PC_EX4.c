/*
4. Se citește un text care este alcătuit doar din litere. Să se afișeze pentru fiecare literă de câte ori apare în text
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    
    char s[100]="";
    fgets(s, 99, stdin);
    
    for(int i = 'a'; i <= 'z'; i++){
        int k = 0;
        for(int j = 0; j < strlen(s); j++){
            if(*(s+j) == i) k++;
        }
        if(k != 0){
            printf("%c %d\n", i, k);  
        }
    }
    
    return 0;
    
}
