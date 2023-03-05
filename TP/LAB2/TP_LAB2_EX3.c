/*
    Aplicația 2.3: Se introduce un număr întreg n<10 și apoi n numere de tip float. Să se folosească funcția qsort
pentru a sorta aceste numere în mod crescător. Se va introduce apoi un număr x de tip float. Folosind funcția
bsearch, să se determine dacă x există în vectorul sortat. Se pot consulta paginile de manual pentru funcțiile qsort
și bsearch.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void citire_nr(uint8_t *nr){
    scanf("%hhu", nr);
}

void init_vector(float *v){
    for(uint8_t i = 0; i < 10; ++i){
        v[i] = 0;
    }
}

void citire_vector(float *v, const uint8_t size){
    for(uint8_t i = 0; i < size; ++i){
        scanf("%f", &v[i]);
    }
}

int compar_cresc(const void *a, const void *b){

    float *p1 = (float *)a;
    float *p2 = (float *)b;

    return *p1 - *p2;
}

void print_vector(const float *v, const uint8_t size){

    for(uint8_t i = 0; i < size; ++i){
        printf("%.2f ", v[i]);
    }
    printf("\b");
}

int main(){

    uint8_t n;
    float v[10];
    float x;
    float *sol = NULL;

    citire_nr(&n);

    if(n < 0 || n > 10){

        printf("Numar invalid\n");
        exit(EXIT_FAILURE);
    }

    init_vector(v);
    citire_vector(v,n);
    
    printf("Ce numar cautam in vector:");
    scanf("%f", &x);

    print_vector(v,n);
    printf("\n\n");

    qsort(v, n, sizeof(float), compar_cresc);
    //print_vector(v,n);
    printf("\n");
    sol = (float *)bsearch(&x, v, n, sizeof(float), compar_cresc);

    if(sol != NULL){
        printf("Numarul %.2f exista in vector\n", x);
    }
    else{
        printf("Numarul %.2f NU exista in vector\n", x);
    }

    return 0;
}
