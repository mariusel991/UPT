/*
   7.  Se citește un număr n (n<=10) și apoi n numere întregi. Se cere să se sorteze aceste
   numere în ordine descrescătoare utilizând pointeri, fără indecși. (Inclusiv citirea se va
   face cu pointeri.)
*/

#include <stdio.h>
#include <stdlib.h>

void citire(int v[], int n){
    for(int i = 0; i < n; i++){
        scanf("%d", &*(v+i));
    }
}

void sortare(int v[], int n){/// nu se cere sortare eficienta deci double for 2 go
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(*(v+i) < *(v+j)){/// interschimbare fara aux
                *(v+i) = *(v+i) + *(v+j);
                *(v+j) = *(v+i) - *(v+j);
                *(v+i) = *(v+i) - *(v+j);
            }
        }
    }
}

void afisare(int v[], int n){
    for(int i = 0; i < n; i++){
        printf("%d ", *(v+i));
    }
    printf("\b\n");
}

int main(){
    
    int v[9];
    int n;
    
    scanf("%d", &n);
    if(n <= 0 && n > 10){/// n nu este in intevalul (0,10];
        printf("error");
        exit(1);
    }
    
    citire(v,n);
    sortare(v,n);
    afisare(v,n);
    
    return 0;
}
