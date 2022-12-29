#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    FILE *f;
    char ch;
    int v[255] = {};
    int caractere = 0;
    
    if((f = fopen("scrisoare.txt","r")) == NULL){
        perror("Error: ");
        exit(1);
    }
    
    while((ch = fgetc(f)) != EOF){
        if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
            v[(int)ch]++;
            caractere++;
        }
    }
    
    for(int i = 'a'; i <= 'z'; i++){
        if(v[i] != 0){
            printf("%c %2.2f%%\n", i,(float)(v[i]*100)/caractere);
        }
    }
    
    for(int i = 'A'; i <= 'Z'; i++){
        if(v[i] != 0){
            printf("%c %2.2f%%\n", i,(float)(v[i]*100)/caractere);
        }
    }
    
    fclose(f);
    
    return 0;
}
