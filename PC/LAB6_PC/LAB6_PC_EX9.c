#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, v[18];
    
    scanf("%d", &n);
    if(n > 10){/// verificare intiala pentru a nu corupe memoria prin citirea mau 
               ///multor elemente decat cele alocate
        printf("error\n");
        exit(1);
    }
    
    for(int i = 0; i < n; i++){ /// citire elemente
        scanf("%d", &v[i]);
    }
    
    
    for(int i = 0; i < n; i++){/// prelucare vector - inserarea lui 0 inainte de val impara
        if(v[i]%2 == 1){
            for(int j = n; j > i; j--){
                v[j] = v[j-1];
            }
            v[i] = 0;
            n++;///dimensiunea noului vector v
            i++;///parcurgem mai departe vectorul pentru a nu intra intr-un loop
        }
    }
    
    for(int i = 0; i < n; i++){///afisare vector
        printf("%d ", v[i]);
    }
    printf("\b\n");
    
    return 0;
    
}
