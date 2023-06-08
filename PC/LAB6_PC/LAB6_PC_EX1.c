#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int prelucreaza(const char *str){
    int k = 0;
    for(int i = 0; i < strlen(str) - 1; i++){
        ///printf("%d", k);
        if(str[i] != str[i+1]){
            k++;
        }
    }
    return k;
    
}

int main(){
    
    char v[32]="";
    int rez;
 
    if( fgets(v,32,stdin) == NULL){/// verificam daca se poate citi de la stdin
        printf("error");
        exit(1);
    }
    
    rez = prelucreaza(v);
    printf("%d\n", rez);
    
    
    
    
}
