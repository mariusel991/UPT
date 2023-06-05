/*
Aplicația 2.1: Se cere un număr n și apoi un vector de n rezultate ale studenților la un examen. Fiecare rezultat
este definit prin (nume,nota). Se cere să se sorteze folosind qsort vectorul în ordinea notelor, notele cele mai mari
fiind primele. Dacă două note sunt identice, rezultatele respective se vor sorta în ordinea alfabetică a numelor.
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct elev{
    char nume[32];
    unsigned int nota;
}elev;

void Aloc(elev **p, int size){
    if(*p){
        perror("Not NULL Pointer\n");
        exit(errno);
    }

    *p = (elev *)malloc(size * sizeof(elev));
    if(!*p){
        perror("Error allocating memory\n");
        exit(errno);
    }
}

void Citeste_elevi(elev **p, int n){
    
    if(!*p){
        perror("NULL Pointer\n");
        exit(errno);
    }

    for(int i = 0; i < n; i++){
        printf("Elevul %d\n", i + 1);
        printf("Nume: "), scanf("%32s",(*p)[i].nume);
        printf("Nota: "), scanf("%u", &(*p)[i].nota);
        printf("\n");
    }
}

int compare(const void *a, const void *b){
    int *p1 = (int *)a;
    int *p2 = (int *)b;

    return *p1 - *p2;
}

void Afisare(elev *p, int size){
    for(int i = 0; i < size; i++){
        printf("Nume:%s\nNota:%d\n\n", p[i].nume, p[i].nota);
    }
}


int main(){
    int n;
    elev *elevi = NULL;

    printf("n = "), scanf("%d",&n);
    
    Aloc(&elevi, n);
    Citeste_elevi(&elevi, n);
    qsort(elevi, n, sizeof(elev), compare);
    Afisare(elevi, n);

    return 0;
}
