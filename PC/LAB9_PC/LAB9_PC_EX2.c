#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    
    int n;
    int i = 0;
    char maxx[100]="", aux[100]="";
    scanf("%d", &n);
    getchar();/// trecem peste \n din stdin
    
    if(n <= 0 || n > 10){
        printf("error\n");
        exit(1);
    }
    
    while(i < n){
        fgets(aux, 100, stdin);
        if(strlen(aux) > strlen(maxx)){
            strcpy(maxx,aux);
        }
        i++;
    }
    
    printf("\n%s%ld\n", maxx, strlen(maxx)-1);
    return 0;
    
}
