/*
  7. Se citește un număr n (n<=10) și apoi n numere întregi. Se cere să se sorteze aceste numere astfel 
  încât numerele impare să fie înaintea celor pare.
*/

#include <stdio.h>

int main(){
    
    int n, v[10];
    ///Citire elemente vector
    scanf("%d", &n);
    for(int i = 0; i < n; i++){///citim n elemente in vector
        scanf("%d", &v[i]);
    }
    
    ///Prelucrae vector
    for(int i = 0, j = n-1; i < j;){/// parcurgem vectorul din extremitati spre mijloc
        if(v[i] % 2 == 0 && v[j] %2 == 1){///schimbam valorile pentru ca cele impare sa fie in fata si cele pare la urma
            int aux;
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
        }
        if(v[i] % 2 == 1) i++;/// nu am gasit valoare para in stanga
        if(v[j] % 2 == 0) j--;/// nu am gasit o valoare impara in dreapta
    }
    ///Afisare vector
    for(int i = 0; i < n; i++){/// afisam vectorul modificat
        printf("%d ", v[i]);
    }
    printf("\b\n");
    
    return 0;
    
    
}
