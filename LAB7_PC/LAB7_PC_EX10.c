/*
    Se citesc n<=10 valori întregi. Folosind doar pointeri, fără niciun fel de indexare, să se
    afișeze toate valorile care au cel puțin un duplicat. (Inclusiv citirea se va face cu
    pointeri.)
    
    
    DISCLAIMER: CA MOD DE REZOLVARE AM CONSIDERAT VALORILE DUPLICATE CU 0 DECI CAZUL DE CATE 0
    - URI SUNT DUPLICATE SE NEGLIJEAZA, NU AM STITUT CE SA PUN IN LOC DE 0 CA VALOARE DE COMPA-
    RATIE. (ma gandisem initial la vectori de frecventa, dar nu stiu domeniul deci s-ar putea sa nu fie o aboradre ok)
 */

#include <stdio.h>
#include <stdlib.h>


void citire(int v[], int size){///functie de citire vector cu n elemente
    for(int i = 0; i < size; i++){
        scanf("%d", &*(v+i));/// citire fara indexare - v[i]
    }
}

void cate_nr_duplicate(int v[], int size, int *k){
        int ok = 0;/// consideram ca nu avem nici un duplicat
    for(int i = 0; i < size; i++){
        ok = 0;/// consideram ca nu sunt duplicate la iteratia i
        if(*(v+i) == 0) continue;
        for(int j = i+1; j < size; j++){
            ///printf("af 1 - %d %d %d\n", *(v+i), *(v+j), *k); ///debug - se igora aceasta linie
            if(*(v+i) == *(v+j)){///am gasit un duplicat
                ok = 1;/// marcam existenta sa
                *(v+j) = 0;/// il marcam ca duplicat
            ///printf("af 2 - %d %d %d\n", *(v+i), *(v+j), *k);   ///debug- se ignora aceasta linie
            }
            else if(*(v+j) == 0){/// fiind duplicat nu il luam in considerare peste
                continue;
            }
        }
        if(ok == 1) *k = *k + 1;///crestem contorul de numere care au duplicate
    }
}

int main(){
    
    int n, k = 0;
    int v[10];
    
    scanf("%d", &n);
    if(n < 0 && n > 11){
        printf("error");
        exit(1);
    }
    
    citire(v,n);/// aplelam functia citire
    cate_nr_duplicate(v,n,&k);/// verificam cate numere au duplicate
    
    printf("%d\n",k);
    
    return 0;
}
