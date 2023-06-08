/*
    13. Se citește un număr n<=10 și apoi n perechi de numere întregi. Se cere să se insereze după 
    fiecare pereche din vectorul original suma și apoi produsul numerelor din pereche.
*/

#include <stdio.h>
#include <stdlib.h>


int main(){
    
    int v[36];
    int n,n_final,x,y;
    
    scanf("%d", &n);
    n_final = 0;
    
    if(n >= 0 && n > 10){/// verificam daca nu depasim capacitatea vectorului
        printf("error\n");
        exit(1);
    }
    
    for(int i = 0; i < n; i++){/// CITIRE VECTOR - prelucrare 2 in 1
        scanf("%d %d", &x, &y);
        v[n_final] = x;
        v[n_final+1] = y;
        v[n_final+2] = x+y;
        v[n_final+3] = x*y;
        n_final+= 4;
    }
    
    
    
    for(int i = 0; i < n_final; i++){///afisare vector nou
        printf("%d ", v[i]);
    }
    printf("\b\n");
    
    return 0;
}
