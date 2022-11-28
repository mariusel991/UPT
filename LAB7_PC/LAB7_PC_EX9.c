/*
    9. Se dă vectorul {7, -5, 4, 3, -9, 2, -8}. Să se insereze înainte de fiecare valoare din
    vectorul original negativul ei. Utilizați pointeri, fără indecși.
 */

#include <stdio.h>

int main(){
    
    int v[14] = {7, -5, 4, 3, -9, 2, -8};
    int n = 7;/// pt ca avem 7 elemente in vectorul de sus
    
    for(int i = 0; i < n; i++){
        for(int j = n; j >= i+1; j--){
            *(v+j) = *(v+(j-1));/// mutam toate elementele din vector cu o poz la dreapta
        }
        n++;/// dimensiunea noului vector
        *(v+i) = -1 * (*(v+(i+1)));/// inseram opusul inaintea valorii v[i]
        i++;/// urmatorul element pentru a nu creea un loop
    }
    
    for(int i = 0; i < n; i++){/// afisare vector nou
        printf("%d ", *(v+i));
    }
    printf("\b\n");
    
    return 0;
}
