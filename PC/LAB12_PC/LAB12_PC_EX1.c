#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void citire_siruri(char *str1, char *str2){
    
    fgets(str1,105,stdin);
    if(str1[strlen(str1) - 1] == '\n'){
        str1[strlen(str1) - 1] = 0;
    }
    fgets(str2,105,stdin);
}

int main(){
    
    char s1[105], s2[105];
    char *s = NULL;
    size_t lung = 0;
    
    citire_siruri(s1,s2);
    //printf("%s\n%s",s1,s2);
    
    lung = lung + strlen(s1) + strlen(s2) + 2;
    s = malloc(lung * sizeof(char));
    
    if(s == NULL){
        fprintf(stderr,"Error alocating memory!\n");
        exit(-1);
    }
    
    strcpy(s,s1);
    strcat(s, " ");
    strcat(s,s2);
    
    printf("%s", s);
    
    free(s);
    
}
