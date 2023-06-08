/*
  2. Să se scrie un program care citește un număr n<10 iar apoi citește 2 vectori v1 și v2 de câte n elemente de tip int. 
  Pentru citirea elementelor unui vector se folosește o funcție citire(v,n). Se va implementa o funcție egal(v1,v2,n), 
  care testează dacă toate elementele din v1 sunt egale cu cele din v2 la poziții corespondente.
*/

#include <stdio.h>
#include <stdlib.h>

void citire(int v[], int size){
    for(int i = 0; i < size; i++){
        scanf("%d", &*(v+i));
    }
}

void egal(int v1[], int v2[], int size){
    for(int i = 0; i < size; i++){
        if(*(v1+i) != *(v2+i)){
            printf("Valorile din vector nu sunt egale!\n");
            return;
        }
    }
    printf("Valorile din vector sunt egale\n");
}

void afisare(int v[],  int size){
    for(int i = 0; i < size; i++){
        printf("%d ",  *(v+i));
    }
    printf("\b\n");
}

int main(){
    int n;
    int v1[9], v2[9];
    
    scanf("%d", &n);
    if(n < 0 && n > 10){
        printf("error");
        exit(1);
    }
    
    citire(v1, n);
    citire(v2, n);
    egal(v1, v2, n);
    
    
    return 0;
}
