/*
  12. Se citește un număr n<=10 și apoi n numere întregi. Se cere să se insereze după 
  fiecare valoare din vectorul original pătratul ei.
*/

#include <stdio.h>
#include <stdlib.h>


int main(){
    
    int v[18];
    int n;
    
    scanf("%d", &n);
    
    if(n >= 0 && n > 10){/// verificam daca nu depasim capacitatea vectorului
        printf("error\n");
        exit(1);
    }
    
    for(int i = 0; i < n; i++){///CITIRE VECTOR
        scanf("%d", &v[i]);
    }
    
    for(int i = 0; i < n; i++){/// prelucram vectorul
        for(int j = n; j >= i+2; j--){/// mutam cu o poz la dreapta toate elem din vector
            v[j] = v[j-1];
            if(j == i+2){///cand ajungem la poz i+2 creez un loc pentru patratul lui v[i] care se va pune pe poz i+1
             n++;/// dimensiunea noului vector
             v[i+1] = v[i]*v[i];/// patratul pe pozitia urmatoare
             i = i+1;
            }
        }
    }
    n++;
    v[n-1] = v[n-2] * v[n-2];///ultima valoare
    ///printf("%d\n", v[n-1]); /// debug
    
    for(int i = 0; i < n; i++){///afisare vector nou
        printf("%d ", v[i]);
    }
    printf("\b\n");
    
    return 0;
}
