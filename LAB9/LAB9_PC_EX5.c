/*
 5. #VARIANTA 1
 Se citește n din intervalul [3,10] și apoi n nume de persoane. Să se concateneze primele n-1 nume folosind „, ”, 
 ultimul nume cu „ si ”, iar apoi să se adauge „invata.”. Să se afișeze propoziția rezultată.

 Exemplu: n=3, numele: Ion Ana Maria
 Propoziție rezultata: Ion, Ana și Maria invata.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    
    char s[255]="", nume[27];/// presupunem ca un nume are max 26 caractere
    int n;
    
    scanf("%d", &n);
    if(n < 3 || n > 10){
        printf("error");
        exit(1);
    }
    
    ///getchar();/// - \n
    
    for(int i = 0; i < n; i++){
        strcpy(nume,"");/// initializam nume cu nul
        scanf("%26s", nume);
        
        if(i == n-1){
            s[strlen(s)-2] = 0;
            strcat(s," si ");
            strcat(s, nume);
            strcat(s, " invata");
            break;
        }
        
        strcat(s,nume);
        strcat(s,", ");
        
    }
    printf("%s\n", s);
    return 0;
}
