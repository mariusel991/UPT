/*
11. Se citește un număr n<=10 și apoi n numere întregi. Se cere să se șteargă toate duplicatele (ori de câte ori apar acestea) 
din vector, păstrându-se ordinea elementelor.
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, v[9], n_initial;
    
    scanf("%d", &n);
    if(n > 10){/// verificare intiala pentru a nu corupe memoria prin citirea mau 
               ///multor elemente decat cele alocate
        printf("error\n");
        exit(1);
    }
    n_initial = n;
    
    for(int i = 0; i < n; i++){ /// citire elemente
        scanf("%d", &v[i]);
    }
    
    
    for(int i = 0; i < n-1; i++){/// prelucare vector - inserarea lui 0 inainte de val impara
        for(int j = i+1; j < n; j++){
            if (v[i] == v[j]){
                for(int k = j; k < n-1; k++){
                    v[k] = v[k+1];
                }
                i--;
                n--;
            }
        }
    }
    
    for(int i = n; i < n_initial; i++){/// resetam valorile intiale care nu se mai folosec
        v[i] = 0;
    }
    
    for(int i = 0; i < n; i++){///afisare vector
        printf("%d ", v[i]);
    }
    printf("\b\n");
    
    return 0;
    
}
